#include "kiran-titlebar-window-private.h"
#include "xlib-helper.h"
#include "global_define.h"

#include <QDebug>
#include <QCursor>
#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QWindow>
#include <QFile>

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
      m_shadowEffect(nullptr),
      m_isCompositingManagerRunning(false)
{
    m_isCompositingManagerRunning = QX11Info::isCompositingManagerRunning();

    m_shadowEffect = new QGraphicsDropShadowEffect(q_ptr);
    m_shadowEffect->setOffset(0, 0);
    m_shadowEffect->setColor(QColor("#444444"));
    m_shadowEffect->setBlurRadius(15);

    q_func()->setGraphicsEffect(m_shadowEffect);
}

KiranTitlebarWindowPrivate::~KiranTitlebarWindowPrivate()
{

}

void KiranTitlebarWindowPrivate::init()
{
    if(m_frame!=nullptr){
        delete m_frame;
    }

    if(m_layout!=nullptr){
        delete m_layout;
    }
    m_layout = nullptr;
    m_frame = nullptr;
    m_frameLayout = nullptr;
    m_titlebarWidget = nullptr;
    m_titleIcon = nullptr;
    m_title = nullptr;
    m_customLayout = nullptr;
    m_btnMin = nullptr;
    m_btnMax = nullptr;
    m_btnClose = nullptr;
    m_windowContentWidgetWrapper = nullptr;
    m_windowContentWidget = nullptr;

    initOtherWidget();

    ///内容栏
    QWidget*contentWidget = new QWidget;
    setWindowContentWidget(contentWidget);

    ///加载样式表
    QFile file(":/themes/black_theme.qss");
    if( file.open(QIODevice::ReadOnly) ){
        QString titlebarStyle = file.readAll();
        q_func()->setStyleSheet(q_func()->styleSheet()+titlebarStyle);
    }
}

void KiranTitlebarWindowPrivate::setIcon(const QIcon &icon)
{
    m_titleIcon->setPixmap(icon.pixmap(16,16));
}

void KiranTitlebarWindowPrivate::setTitle(const QString &title)
{
    m_title->setText(title);
}

void KiranTitlebarWindowPrivate::setButtonHints(KiranTitlebarWindow::TitlebarButtonHintFlags hints)
{
    m_buttonHints = hints;
    m_btnMax->setVisible( (m_buttonHints & KiranTitlebarWindow::TitlebarMaximizeButtonHint) );
    m_btnMin->setVisible( (m_buttonHints & KiranTitlebarWindow::TitlebarMinimizeButtonHint) );
    m_btnClose->setVisible( (m_buttonHints & KiranTitlebarWindow::TitlebarCloseButtonHint) );
}

void KiranTitlebarWindowPrivate::setWindowContentWidget(QWidget *widget)
{
    if( m_windowContentWidget!=nullptr ){
        delete m_windowContentWidget;
        m_windowContentWidget = nullptr;
    }
    m_windowContentWidget = widget;
    m_windowContentWidget->setParent(m_windowContentWidgetWrapper);
    m_windowContentWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_windowContentWidgetWrapper->layout()->addWidget(m_windowContentWidget);
}

void KiranTitlebarWindowPrivate::handlerHoverMoveEvent(QHoverEvent *ev)
{
    if(!m_resizeable){
        return;
    }
    CursorPositionEnums postion = getCursorPosition(QCursor::pos());
    if(postion==CursorPosition_None||q_ptr->isMaximized()){
        q_func()->unsetCursor();
        return;
    }
    switch (postion) {
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
    if( ev->button()!=Qt::LeftButton ){
        return;
    }

    if( m_resizeable && !q_func()->isMaximized() ){
        CursorPositionEnums postion = getCursorPosition(ev->globalPos());
        if( postion!=CursorPosition_None ){
            QPoint pos = QCursor::pos();
            pos *= q_func()->devicePixelRatio();
            XLibHelper::sendResizeEvent(QX11Info::display(),
                                        postion,q_ptr->winId(),
                                        pos.x(),
                                        pos.y());
            return;
        }
    }

    if( m_titlebarWidget->frameGeometry().contains(ev->pos()) ){
        qDebug() << "mouse button press titlebar";
        m_titlebarIsPressed = true;
    }
}

void KiranTitlebarWindowPrivate::handlerMouseButtonReleaseEvent(QMouseEvent *ev)
{
    if(  ev->button() == Qt::LeftButton ){
        qDebug() << "mouse button release";
        if(m_titlebarIsPressed){
            m_titlebarIsPressed = false;
        }
    }
}

void KiranTitlebarWindowPrivate::handlerMouseMoveEvent(QMouseEvent *ev)
{
    ///判断是否点击标题栏区域
    if( m_titlebarIsPressed ){
        QPoint pos = QCursor::pos();
        pos *= q_func()->devicePixelRatio();
        XLibHelper::sendWMMoveEvent(QX11Info::display(),
                                    q_func()->winId(),
                                    pos.x(),
                                    pos.y());
        ///NOTE:在此之后获取不到MouseRelease事件,需复位按钮按压
        m_titlebarIsPressed = false;
        ev->accept();
        return;
    }
}

void KiranTitlebarWindowPrivate::handlerMouseDoubleClickEvent(QMouseEvent *ev)
{
    if( ev->button()!=Qt::LeftButton ){
        return;
    }

    if( m_titlebarWidget->frameGeometry().contains(ev->pos()) ){
        if( q_func()->isMaximized() ){
            q_func()->showNormal();
        }else{
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
    m_frame =  new QFrame(q_ptr);
    m_layout->addWidget(m_frame);
    m_frame->setObjectName("KiranTitlebarFrame");
    m_frameLayout = new QVBoxLayout(m_frame);
    m_frameLayout->setMargin(0);
    m_frameLayout->setSpacing(0);

    ///标题栏
    m_titlebarWidget = new QWidget(m_frame);
    m_titlebarWidget->setObjectName("KiranTitlebarWidget");
    m_titlebarWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_titlebarWidget->setFixedHeight(60);
    m_frameLayout->addWidget(m_titlebarWidget);
    QHBoxLayout* titlebarLayout = new QHBoxLayout(m_titlebarWidget);
    titlebarLayout->setMargin(0);
    titlebarLayout->setSpacing(0);
    titlebarLayout->setObjectName("KiranTitlebarLayout");

    ///标题栏居左部分
    QWidget* titlebarLeftWidget = new QWidget(m_titlebarWidget);
    titlebarLeftWidget->setObjectName("KiranTitlebarLeftWidget");
    titlebarLeftWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    titlebarLayout->addWidget(titlebarLeftWidget,1,Qt::AlignVCenter);
    QHBoxLayout* titlebarLeftLayout = new QHBoxLayout(titlebarLeftWidget);
    titlebarLeftLayout->setContentsMargins(20,-1,-1,-1);
    titlebarLeftLayout->setSpacing(12);

    //标题栏图标
    m_titleIcon = new QLabel;
    m_titleIcon->setObjectName("KiranTitlebarIcon");
    m_titleIcon->setFixedSize(24,24);
    titlebarLeftLayout->addWidget(m_titleIcon,0,Qt::AlignLeft|Qt::AlignVCenter);

    //标题
    m_title = new QLabel;
    m_title->setObjectName("KiranTitlebarTitle");
    m_title->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_title->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    titlebarLeftLayout->addWidget(m_title,0,Qt::AlignLeft|Qt::AlignVCenter);

    //占位
    QSpacerItem* spacerItem_1 = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    titlebarLeftLayout->addItem(spacerItem_1);

    ///标题栏居中部分

    //自定义控件区域
    QWidget* titlebarCenterWidget = new QWidget(m_titlebarWidget);
    titlebarCenterWidget->setObjectName("KiranTitlebarCenterWidget");
    titlebarCenterWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    titlebarLayout->addWidget(titlebarCenterWidget,2,Qt::AlignVCenter);
    m_customLayout = new QHBoxLayout(titlebarCenterWidget);
    m_customLayout->setMargin(0);
    m_customLayout->setSpacing(0);
    m_customLayout->setObjectName("KiranTitlebarCustomLayout");

    ///标题栏居右部分
    QWidget* titlebarRightWidget = new QWidget(m_titlebarWidget);
    titlebarRightWidget->setObjectName("KiranTitlebarRightWidget");
    titlebarRightWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    titlebarLayout->addWidget(titlebarRightWidget,1,Qt::AlignVCenter);
    QHBoxLayout* titlebarRightlayout = new QHBoxLayout(titlebarRightWidget);
    titlebarRightlayout->setContentsMargins(-1,-1,24,-1);
    titlebarRightlayout->setSpacing(16);

    //占位
    QSpacerItem* spacerItem_2 = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    titlebarRightlayout->addItem(spacerItem_2);

    //最小化
    m_btnMin = new QPushButton(m_titlebarWidget);
    m_btnMin->setObjectName("KiranTitlebarMinButton");
    m_btnMin->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_btnMin->setVisible(false);
    titlebarRightlayout->addWidget(m_btnMin,0,Qt::AlignVCenter);

    //最大化
    m_btnMax = new QPushButton(m_titlebarWidget);
    m_btnMax->setObjectName("KiranTitlebarMaxButton");
    m_btnMax->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_btnMax->setVisible(false);
    titlebarRightlayout->addWidget(m_btnMax,0,Qt::AlignVCenter);

    //关闭
    m_btnClose = new QPushButton(m_titlebarWidget);
    m_btnClose->setObjectName("KiranTitlebarCloseButton");
    m_btnClose->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_btnClose->setVisible(false);
    titlebarRightlayout->addWidget(m_btnClose,0,Qt::AlignVCenter);
    setButtonHints(m_buttonHints);

    ///内容窗口包装
    m_windowContentWidgetWrapper = new QWidget(m_frame);
    m_windowContentWidgetWrapper->setObjectName("KiranTitlebarContentWrapper");
    m_frameLayout->addWidget(m_windowContentWidgetWrapper);
    m_windowContentWidgetWrapper->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QHBoxLayout* windowContentWidgetWrapperLayout = new QHBoxLayout(m_windowContentWidgetWrapper);
    windowContentWidgetWrapperLayout->setSpacing(0);
    windowContentWidgetWrapperLayout->setMargin(0);
}

void KiranTitlebarWindowPrivate::updateStyle(bool fullScreen)
{
    bool showShadow = m_isCompositingManagerRunning && (!fullScreen);

    if( m_shadowEffect ){
        m_shadowEffect->setEnabled( showShadow );
    }

    if( m_layout ){
        m_layout->setMargin(showShadow?SHADOW_BORDER_WIDTH:0);
    }
}

CursorPositionEnums KiranTitlebarWindowPrivate::getCursorPosition(QPoint pos)
{
    QPoint frameLeftTop = m_frame->mapToGlobal(QPoint(0,0));
    int frameX = frameLeftTop.x(),frameY = frameLeftTop.y();
    int frameWidth = m_frame->width(),frameHeight = m_frame->height();
    static int borderWidth = 5;

    QRect topBorderRect(frameX,frameY,frameWidth,borderWidth);
    QRect bottomBorderRect(frameX,frameY+frameHeight-borderWidth,frameWidth,borderWidth);
    QRect leftBorderRect(frameX,frameY,borderWidth,frameHeight);
    QRect rightBorderRect(frameX+frameWidth-borderWidth,frameY,borderWidth,frameHeight);

    CursorPositionEnums positions = CursorPosition_None;
    if(topBorderRect.contains(pos)){
        positions |= CursorPosition_Top;
    }
    if(bottomBorderRect.contains(pos)){
        positions |= CursorPosition_Bottom;
    }
    if(leftBorderRect.contains(pos)){
        positions |= CursorPosition_Left;
    }
    if(rightBorderRect.contains(pos)){
        positions |= CursorPosition_Right;
    }

    return positions;
}
