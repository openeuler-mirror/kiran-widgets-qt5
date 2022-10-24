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
 
#include "kiran-titlebar-window.h"
#include "kiran-titlebar-window-private.h"
#include "global_define.h"
#include "../../public/xlib-helper.h"

#include <QDebug>
#include <QMouseEvent>
#include <QWindow>
#include <QApplication>
#include <QPainter>

KiranTitlebarWindow::KiranTitlebarWindow()
    : QWidget(nullptr),
      d_ptr(new KiranTitlebarWindowPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_Hover);
    setAccessibleName("KiranTitlebarWindow");

    d_func()->init();
    QWidget::ensurePolished();
    setTitle(qApp->applicationName());
    setIcon(QIcon::fromTheme("window"));
}

KiranTitlebarWindow::KiranTitlebarWindow(QWidget *parent, Qt::WindowFlags windowFlags)
    : QWidget(parent),
    d_ptr(new KiranTitlebarWindowPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_Hover);

    d_func()->init();
    QWidget::ensurePolished();
    setTitle(qApp->applicationName());
}

KiranTitlebarWindow::~KiranTitlebarWindow()
{
    delete d_ptr;
}

void KiranTitlebarWindow::setWindowContentWidget(QWidget *widget)
{
    d_func()->setWindowContentWidget(widget);
}

void KiranTitlebarWindow::setIcon(const QIcon &icon)
{
    setWindowIcon(icon);
    d_func()->setIcon(icon);
}

void KiranTitlebarWindow::setTitle(const QString &text)
{
    setWindowTitle(text);
    d_func()->setTitle(text);
    /* NOTE:由于标题栏标题文本需要收缩以获取更大的大小分配，所以保存完整的标题文本，用作每次省略压缩显示的参考 */
    d_func()->m_titleBarLayout->setTitleBarCompleteTitle(text);
}

void KiranTitlebarWindow::setButtonHints(TitlebarButtonHintFlags hints)
{
    d_func()->setButtonHints(hints);
}

void KiranTitlebarWindow::setResizeable(bool resizeable)
{
    d_func()->m_resizeable = resizeable;
}

int KiranTitlebarWindow::contentWrapperMarginBottom() const
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    return contentMargins.bottom();
}

int KiranTitlebarWindow::contentWrapperMarginRight() const
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    return contentMargins.right();
}

int KiranTitlebarWindow::contentWrapperMarginLeft() const
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    return contentMargins.left();
}

bool KiranTitlebarWindow::compositingRunning() const
{
    return d_func()->m_isCompositingManagerRunning;
}

void KiranTitlebarWindow::setContentWrapperMarginBottom(int margin)
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    if(contentMargins.bottom() == margin){
        return;
    }
    contentMargins.setBottom(margin);
    d_func()->m_windowContentWidgetWrapper->setContentsMargins(contentMargins);
}

void KiranTitlebarWindow::setContentWrapperMarginRight(int margin)
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    if(contentMargins.right() == margin){
        return;
    }
    contentMargins.setRight(margin);
    d_func()->m_windowContentWidgetWrapper->setContentsMargins(contentMargins);
}

void KiranTitlebarWindow::setContentWrapperMarginLeft(int margin)
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    if(contentMargins.left() == margin){
        return;
    }
    contentMargins.setLeft(margin);
    d_func()->m_windowContentWidgetWrapper->setContentsMargins(contentMargins);
}

QWidget *KiranTitlebarWindow::getWindowContentWidget()
{
    return d_func()->m_windowContentWidget;
}

QHBoxLayout *KiranTitlebarWindow::getTitlebarCustomLayout()
{
    return d_func()->m_customLayout;
}

bool KiranTitlebarWindow::event(QEvent *event)
{
    return QWidget::event(event);
}

void KiranTitlebarWindow::paintEvent(QPaintEvent *event)
{
    if( d_ptr->m_isCompositingManagerRunning )
    {
        QPainter p(this);
        d_ptr->ensureShadowPixmapUpdated();
        p.drawPixmap(rect(),isActiveWindow()?d_ptr->m_shadowActivePix:d_ptr->m_shadowPix);
        p.end();
    }

#if 0
    qDebug() << "paint event:" << size() << "pixmap size:" << (isActiveWindow()?d_ptr->m_shadowActivePix.size():d_ptr->m_shadowPix.size());
#endif

    QWidget::paintEvent(event);
}

bool KiranTitlebarWindow::titlebarCustomLayoutAlignHCenter() {
    return d_ptr->m_titleBarLayout->customWidgetCenter();
}

void KiranTitlebarWindow::setTitlebarCustomLayoutAlignHCenter(bool center) {
    d_ptr->m_titleBarLayout->setCustomWidgetCenter(center);
}

QSize KiranTitlebarWindow::sizeHint() const
{
#if 0
    QSize sizeHint = QWidget::sizeHint();
    if(d_ptr->m_isCompositingManagerRunning)
    {
        sizeHint.setWidth(2*SHADOW_BORDER_WIDTH+sizeHint.width());
        sizeHint.setHeight(2*SHADOW_BORDER_WIDTH+sizeHint.height());
    }
    return sizeHint;
#endif
    return QWidget::sizeHint();
}

void KiranTitlebarWindow::setTitleBarHeight(int height)
{
    d_ptr->m_titlebarWidget->setFixedHeight(height);
}

int KiranTitlebarWindow::titleBarHeight()
{
    return d_ptr->m_titlebarWidget->height();
}

int KiranTitlebarWindow::transparentWidth()
{
    return d_ptr->m_layout->margin();
}

void KiranTitlebarWindow::setTitlebarColorBlockEnable(bool enable)
{
    d_func()->setTitlebarColorBlockEnable(enable);
}

bool KiranTitlebarWindow::getTitlebarColorBlockEnable()
{
    return d_func()->m_colorBlockEnable;
}