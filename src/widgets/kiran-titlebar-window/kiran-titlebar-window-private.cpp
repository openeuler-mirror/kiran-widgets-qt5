/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 */

#include "kiran-titlebar-window-private.h"
#include "../../public/xlib-helper.h"
#include "drop-shadow-color.h"
#include "frameless-background-frame.h"
#include "global_define.h"
#include "title-bar-layout.h"

#include <xcb/xcb.h>
#include <QApplication>
#include <QColor>
#include <QCursor>
#include <QDebug>
#include <QEvent>
#include <QFile>
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QScreen>
#include <QStyle>
#include <QTimer>
#include <QToolButton>
#include <QWindow>
#include <QPainter>
#include <QPainterPath>


const int    KiranTitlebarWindowPrivate::radius = 8;

const int    KiranTitlebarWindowPrivate::shadowWidth = 15;
const int    KiranTitlebarWindowPrivate::shadowRadius = 15;
const QColor KiranTitlebarWindowPrivate::shadowActiveColor = QColor(0,0,0,150);
const QColor KiranTitlebarWindowPrivate::shadowInactiveColor = QColor(0,0,0,75);

extern void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);

using namespace Kiran;

KiranTitlebarWindowPrivate::KiranTitlebarWindowPrivate(KiranTitlebarWindow *ptr)
    : q_ptr(ptr),
      m_layout(nullptr),
      m_frame(nullptr),
      m_titlebarWidget(nullptr),
      m_titleIcon(nullptr),
      m_title(nullptr),
      m_customLayout(nullptr),
      m_buttonHints(KiranTitlebarWindow::TitlebarMinMaxCloseHints),
      m_btnMin(nullptr),
      m_btnMax(nullptr),
      m_btnClose(nullptr),
      m_windowContentWidgetWrapper(nullptr),
      m_windowContentWidget(nullptr),
      m_titlebarIsPressed(false),
      m_resizeable(true),
      m_isCompositingManagerRunning(false)
{
}

KiranTitlebarWindowPrivate::~KiranTitlebarWindowPrivate()
{
}

void KiranTitlebarWindowPrivate::init()
{
    //app调色盘改变可以认为主题风格产生变化，需重新拿取图标更新
    connect(qApp, &QApplication::paletteChanged, this,&KiranTitlebarWindowPrivate::updateTitlebarButtonIcon);

    initOtherWidget();

    /// 内容栏
    auto contentWidget = new QWidget;
    setWindowContentWidget(contentWidget);

    /// 初始化阴影边框
    m_isCompositingManagerRunning = QX11Info::isCompositingManagerRunning();
    
    if( m_isCompositingManagerRunning )
    {
        m_layout->setMargin(shadowWidth);
    }

    /// 处理窗口事件
    q_ptr->installEventFilter(this);
}

void KiranTitlebarWindowPrivate::setIcon(const QIcon &icon)
{
    m_titleIcon->setPixmap(icon.pixmap(16, 16));
}

void KiranTitlebarWindowPrivate::setTitle(const QString &title)
{
    m_title->setText(title);
}

void KiranTitlebarWindowPrivate::setButtonHints(KiranTitlebarWindow::TitlebarButtonHintFlags hints)
{
    m_buttonHints = hints;
    m_btnMax->setVisible((m_buttonHints & KiranTitlebarWindow::TitlebarMaximizeButtonHint));
    m_btnMin->setVisible((m_buttonHints & KiranTitlebarWindow::TitlebarMinimizeButtonHint));
    m_btnClose->setVisible((m_buttonHints & KiranTitlebarWindow::TitlebarCloseButtonHint));
}

void KiranTitlebarWindowPrivate::setWindowContentWidget(QWidget *widget)
{
    if (m_windowContentWidget != nullptr)
    {
        delete m_windowContentWidget;
        m_windowContentWidget = nullptr;
    }
    m_windowContentWidget = widget;
    m_windowContentWidget->setParent(m_windowContentWidgetWrapper);
    m_windowContentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_windowContentWidgetWrapper->layout()->addWidget(m_windowContentWidget);
}

void KiranTitlebarWindowPrivate::handlerHoverMoveEvent(QHoverEvent *ev)
{
    if (!m_resizeable)
    {
        return;
    }
    CursorPositionEnums postion = getCursorPosition(QCursor::pos());
    if (postion == CursorPosition_None || q_ptr->isMaximized())
    {
        q_func()->unsetCursor();
        return;
    }
    switch (postion)
    {
    case CursorPosition_LeftTop:
    case CursorPosition_RightBottom:
        q_func()->setCursor(Qt::SizeFDiagCursor);
        break;
    case CursorPosition_RightTop:
    case CursorPosition_LeftBottom:
        q_func()->setCursor(Qt::SizeBDiagCursor);
        break;
    case CursorPosition_Left:
    case CursorPosition_Right:
        q_func()->setCursor(Qt::SizeHorCursor);
        break;
    case CursorPosition_Top:
    case CursorPosition_Bottom:
        q_func()->setCursor(Qt::SizeVerCursor);
        break;
    default:
        break;
    }
}

void KiranTitlebarWindowPrivate::handlerLeaveEvent()
{
    q_func()->unsetCursor();
}

void KiranTitlebarWindowPrivate::handlerMouseButtonPressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
    {
        return;
    }

    if (m_resizeable && !q_func()->isMaximized())
    {
        CursorPositionEnums postion = getCursorPosition(ev->globalPos());
        if (postion != CursorPosition_None)
        {
            QPoint pos = QCursor::pos();
            pos *= q_func()->devicePixelRatio();
            XLibHelper::sendResizeEvent(QX11Info::display(),
                                        postion, q_ptr->winId(),
                                        pos.x(),
                                        pos.y());
            return;
        }
    }

#if 0
    qDebug() << "ev pos:    " << ev->pos();
    qDebug() << "rect:      " << q_ptr->rect();
    qDebug() << "frame rect:" << m_frame->geometry();
    qDebug() << "titlebar widget geometry:" << m_titlebarWidget->geometry();
    qDebug() << "titlebar widget frame geometry:" << m_titlebarWidget->frameGeometry();
    qDebug() << "titlebar frame contains:" << m_titlebarWidget->frameGeometry().contains(ev->pos());
#endif

    if (m_titlebarWidget->frameGeometry().contains(m_titlebarWidget->mapFrom(q_ptr,ev->pos())))
    {
        m_titlebarIsPressed = true;
    }
}

void KiranTitlebarWindowPrivate::handlerMouseButtonReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        if (m_titlebarIsPressed)
        {
            m_titlebarIsPressed = false;
        }
    }
}

void KiranTitlebarWindowPrivate::handlerMouseMoveEvent(QMouseEvent *ev)
{
    ///判断是否点击标题栏区域
    if (m_titlebarIsPressed)
    {
        QPoint pos = QCursor::pos();
        pos *= q_func()->devicePixelRatio();
        XLibHelper::sendWMMoveEvent(QX11Info::display(),
                                    q_func()->winId(),
                                    pos.x(),
                                    pos.y());
        ///NOTE:在此之后获取不到MouseRelease事件,需复位按钮按压
        m_titlebarIsPressed = false;
        return;
    }
}

void KiranTitlebarWindowPrivate::handlerMouseDoubleClickEvent(QMouseEvent *ev)
{
    if ((ev->button() != Qt::LeftButton) || !m_resizeable)
    {
        return;
    }

    if (m_titlebarWidget->frameGeometry().contains(ev->pos()))
    {
        if (q_func()->isMaximized())
        {
            q_func()->showNormal();
        }
        else
        {
            q_func()->showMaximized();
        }
    }
}

void KiranTitlebarWindowPrivate::initOtherWidget()
{
    ///主布局
    m_layout = new QVBoxLayout(q_ptr);
    m_layout->setObjectName("KiranTitlebarMainLayout");
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    ///背景
    m_frame = new FramelessBackgroundFrame(q_ptr);
    m_frame->setRadius(radius);
    m_frame->setAttribute(Qt::WA_Hover);
    m_layout->addWidget(m_frame);
    m_frame->setObjectName("KiranTitlebarFrame");
    m_frameLayout = new QVBoxLayout(m_frame);
    m_frameLayout->setMargin(0);
    m_frameLayout->setSpacing(0);

    ///标题栏
    m_titlebarWidget = new QWidget(m_frame);
    m_titlebarWidget->setFocusPolicy(Qt::NoFocus);
    m_titlebarWidget->setObjectName("KiranTitlebarWidget");
    m_titlebarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_titlebarWidget->setFixedHeight(30);
    m_frameLayout->addWidget(m_titlebarWidget);
    m_titleBarLayout = new TitlebarLayout(m_titlebarWidget);
    m_titleBarLayout->setMargin(0);
    m_titleBarLayout->setSpacing(0);
    m_titleBarLayout->setObjectName("KiranTitlebarLayout");

    ///标题栏居左部分
    //标题栏图标
    m_titleIcon = new QLabel(m_titlebarWidget);
    m_titleIcon->setObjectName("KiranTitlebarIcon");
    m_titleIcon->setFixedSize(24, 24);
    m_titleBarLayout->setTitleBarIconLabel(m_titleIcon);
    m_titleBarLayout->setTitleBarIconMargin(QMargins(12, 0, 0, 0));

    //标题
    m_title = new QLabel(m_titlebarWidget);
    m_title->setFont(QFontDatabase::systemFont(QFontDatabase::TitleFont));
    m_title->setObjectName("KiranTitlebarTitle");
    m_title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_title->installEventFilter(this);
    m_titleBarLayout->setTitleBarTitleLabel(m_title);

    ///标题栏居中部分
    //自定义控件区域
    m_titlebarCenterWidget = new QWidget(m_titlebarWidget);
    m_titlebarCenterWidget->setObjectName("KiranTitlebarCenterWidget");
    m_titlebarCenterWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_titleBarLayout->setTitleBarCustomWidget(m_titlebarCenterWidget);
    m_customLayout = new QHBoxLayout(m_titlebarCenterWidget);
    m_customLayout->setMargin(0);
    m_customLayout->setSpacing(0);
    m_customLayout->setObjectName("KiranTitlebarCustomLayout");

    ///标题栏居右部分
    m_titlebarRirghtWidget = new QWidget(m_titlebarWidget);
    m_titlebarRirghtWidget->setObjectName("KiranTitlebarRightWidget");
    m_titlebarRirghtWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_titleBarLayout->setTitleBarRightWidget(m_titlebarRirghtWidget);
    m_titleBarLayout->setTitleBarRightWidgetMargin(QMargins(0, 0, 4, 0));
    QHBoxLayout *titlebarRightlayout = new QHBoxLayout(m_titlebarRirghtWidget);
    titlebarRightlayout->setSpacing(0);
    titlebarRightlayout->setMargin(0);

    //占位
    QSpacerItem *spacerItem = new QSpacerItem(0, 20, QSizePolicy::Expanding);
    titlebarRightlayout->addItem(spacerItem);

    //最小化
    m_btnMin = new QPushButton(m_titlebarWidget);
    m_btnMin->setObjectName("KiranTitlebarMinButton");
    m_btnMin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_btnMin->setVisible(false);
    m_btnMin->setFocusPolicy(Qt::NoFocus);
    m_btnMin->setFlat(true);
    connect(m_btnMin, &QPushButton::clicked, [this](bool checked)
            {
                Q_UNUSED(checked);
                q_ptr->showMinimized();
            });
    titlebarRightlayout->addWidget(m_btnMin, 0, Qt::AlignVCenter);

    //最大化
    m_btnMax = new QPushButton(m_titlebarWidget);
    m_btnMax->setObjectName("KiranTitlebarMaxButton");
    m_btnMax->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_btnMax->setVisible(false);
    m_btnMax->setFocusPolicy(Qt::NoFocus);
    m_btnMax->setFlat(true);
    connect(m_btnMax, &QPushButton::clicked, [this](bool checked)
            {
                Q_UNUSED(checked);
                if (q_ptr->isMaximized())
                {
                    q_ptr->showNormal();
                }
                else
                {
                    q_ptr->showMaximized();
                }
            });
    titlebarRightlayout->addWidget(m_btnMax, 0, Qt::AlignVCenter);

    //关闭
    m_btnClose = new QPushButton(m_titlebarWidget);
    m_btnClose->setObjectName("KiranTitlebarCloseButton");
    m_btnClose->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_btnClose->setVisible(false);
    m_btnClose->setFocusPolicy(Qt::NoFocus);
    m_btnClose->setFlat(true);
    connect(m_btnClose, &QPushButton::clicked, [this](bool checked)
            {
                Q_UNUSED(checked);
                q_ptr->close();
            });
    titlebarRightlayout->addWidget(m_btnClose, 0, Qt::AlignVCenter);

    setButtonHints(m_buttonHints);

    ///分割线
    QFrame *spliteLine = new QFrame(m_frame);
    spliteLine->setFixedHeight(1);
    m_frameLayout->addWidget(spliteLine);
    spliteLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    spliteLine->setFrameShape(QFrame::HLine);
    spliteLine->setFrameShadow(QFrame::Sunken);

    ///内容窗口包装
    m_windowContentWidgetWrapper = new QWidget(m_frame);
    m_windowContentWidgetWrapper->setObjectName("KiranTitlebarContentWrapper");
    m_frameLayout->addWidget(m_windowContentWidgetWrapper);
    m_windowContentWidgetWrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *windowContentWidgetWrapperLayout = new QHBoxLayout(m_windowContentWidgetWrapper);
    windowContentWidgetWrapperLayout->setSpacing(0);
    windowContentWidgetWrapperLayout->setMargin(0);

    updateTitlebarButtonIcon();
}

CursorPositionEnums KiranTitlebarWindowPrivate::getCursorPosition(QPoint pos)
{
    QPoint frameLeftTop = m_frame->mapToGlobal(QPoint(0, 0));
    int frameX = frameLeftTop.x(), frameY = frameLeftTop.y();
    int frameWidth = m_frame->width(), frameHeight = m_frame->height();
    static int borderWidth = 5;

    QRect topBorderRect(frameX, frameY, frameWidth, borderWidth);
    QRect bottomBorderRect(frameX, frameY + frameHeight - borderWidth, frameWidth, borderWidth);
    QRect leftBorderRect(frameX, frameY, borderWidth, frameHeight);
    QRect rightBorderRect(frameX + frameWidth - borderWidth, frameY, borderWidth, frameHeight);

    CursorPositionEnums positions = CursorPosition_None;
    if (topBorderRect.contains(pos))
    {
        positions |= CursorPosition_Top;
    }
    if (bottomBorderRect.contains(pos))
    {
        positions |= CursorPosition_Bottom;
    }
    if (leftBorderRect.contains(pos))
    {
        positions |= CursorPosition_Left;
    }
    if (rightBorderRect.contains(pos))
    {
        positions |= CursorPosition_Right;
    }

    return positions;
}

void KiranTitlebarWindowPrivate::ensureShadowPixmapUpdated()
{
    if( !m_isCompositingManagerRunning )
    {
        return;
    }
    
    bool isActiveWindow = q_ptr->isActiveWindow();
    auto windowSize = q_ptr->size();
    auto windowRect = q_ptr->rect();

    if( ( isActiveWindow && (m_shadowActivePix.size() == windowSize) ) || 
        ( !isActiveWindow && (m_shadowPix.size() == windowSize) ) )
    {
        //不需更新
        return;
    }

    qDebug() << "update shadow pixmap..." << isActiveWindow << windowSize;

    QPainterPath innerPath,outerPath;
    innerPath.addRoundedRect(windowRect.adjusted(shadowWidth,shadowWidth,-shadowWidth,-shadowWidth),radius,radius);
    outerPath.addRoundedRect(windowRect,radius,radius);

    QImage img(windowSize,QImage::Format_ARGB32_Premultiplied);
    img.fill(0);

    QPainter imgPainter(&img);
    imgPainter.setCompositionMode(QPainter::CompositionMode_Source);
    imgPainter.fillPath(innerPath,QBrush(Qt::white));
    imgPainter.end();

    QImage blurredImg(img.size(),img.format());
    blurredImg.fill(0);
    QPainter blurPainter(&blurredImg);
    qt_blurImage(&blurPainter,img,shadowRadius,false,true);
    blurPainter.end();

    img = std::move(blurredImg);

    imgPainter.begin(&img);
    imgPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    imgPainter.fillRect(img.rect(),isActiveWindow?shadowActiveColor:shadowInactiveColor);
    imgPainter.end();

    QPixmap pixmap(img.size());
    pixmap.fill(Qt::transparent);

    QPainterPath clipPath;
    clipPath.addPath(innerPath);
    clipPath.addPath(outerPath);

    QPainter outputPainter(&pixmap);
    outputPainter.setClipPath(clipPath);
    outputPainter.drawImage(img.rect(),img);
    outputPainter.end();

    if( isActiveWindow )
    {
        m_shadowActivePix = pixmap;
    }
    else
    {
        m_shadowPix = pixmap;
    }
}

void KiranTitlebarWindowPrivate::updateTitleFont(QFont font)
{
}

bool KiranTitlebarWindowPrivate::eventFilter(QObject *obj, QEvent *event)
{
    //NOTE:用户标题栏暂时需要使用窗口管理器单独设置的字体，不和程序字体通用
    if (obj == m_title && event->type() == QEvent::ApplicationFontChange)
    {
        return true;
    }

    // 对窗口事件进行处理
    if (obj == q_ptr)
    {
        switch (event->type())
        {
        case QEvent::ShowToParent:
            // 若在初始化时 createWinId 再调用下列方法设置属性，设置属性成功，但窗口管理器未能成功识别
            // 在接近显示时进行处理设置_GTK_FRAME_EXTENTS属性
            if( m_isCompositingManagerRunning )
            {
                XLibHelper::SetShadowWidth(QX11Info::display(),q_ptr->winId(),shadowWidth,shadowWidth,shadowWidth,shadowWidth);
            }
            break;
        case QEvent::HoverMove:
            handlerHoverMoveEvent(dynamic_cast<QHoverEvent *>(event));
            break;
        case QEvent::Leave:
            handlerLeaveEvent();
            break;
        case QEvent::MouseButtonPress:
            handlerMouseButtonPressEvent(dynamic_cast<QMouseEvent *>(event));
            break;
        case QEvent::MouseButtonRelease:
            handlerMouseButtonReleaseEvent(dynamic_cast<QMouseEvent *>(event));
            break;
        case QEvent::MouseMove:
            handlerMouseMoveEvent(dynamic_cast<QMouseEvent *>(event));
            break;
        case QEvent::MouseButtonDblClick:
            handlerMouseDoubleClickEvent(dynamic_cast<QMouseEvent *>(event));
            break;
        case QEvent::ActivationChange:
            q_ptr->update();
            break;
        case QEvent::StyleChange:
            updateTitlebarButtonIcon();
            break;
        case QEvent::WindowStateChange: 
            if( q_ptr->windowState() == Qt::WindowMaximized )
            {
                m_frame->setRadius(0);
            }
            else
            {
                m_frame->setRadius(radius);
            }
            break;
        default:
            break;
        }
    }

    return QObject::eventFilter(obj, event);
}

void KiranTitlebarWindowPrivate::updateTitlebarButtonIcon()
{
    QIcon icon;
    QSize defaultIconSize = QSize(16, 16);

    icon = q_ptr->style()->standardIcon(QStyle::SP_TitleBarMinButton);
    m_btnMin->setIcon(icon);
    m_btnMin->setIconSize(defaultIconSize);

    QStyle::StandardPixmap sp = QStyle::SP_TitleBarMaxButton;
    if (q_ptr->window()->isMaximized())
    {
        sp = QStyle::SP_TitleBarNormalButton;
    }
    icon = q_ptr->style()->standardIcon(sp);
    m_btnMax->setIcon(icon);
    m_btnMax->setIconSize(defaultIconSize);

    icon = q_ptr->style()->standardIcon(QStyle::SP_TitleBarCloseButton);
    m_btnClose->setIcon(icon);
    m_btnClose->setIconSize(defaultIconSize);
}
