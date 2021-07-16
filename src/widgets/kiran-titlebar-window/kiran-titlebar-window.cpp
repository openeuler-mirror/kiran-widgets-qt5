 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd. 
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */
 
#include "kiran-titlebar-window.h"
#include "kiran-titlebar-window-private.h"
#include "global_define.h"
#include "../../public/xlib-helper.h"

#include <QDebug>
#include <QMouseEvent>
#include <QWindow>
#include <QApplication>

KiranTitlebarWindow::KiranTitlebarWindow()
    : QWidget(nullptr),
      d_ptr(new KiranTitlebarWindowPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_Hover);

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

bool KiranTitlebarWindow::titlebarCustomLayoutAlignHCenter() {
    return d_ptr->m_titleBarLayout->customWidgetCenter();
}

void KiranTitlebarWindow::setTitlebarCustomLayoutAlignHCenter(bool center) {
    d_ptr->m_titleBarLayout->setCustomWidgetCenter(center);
}

QSize KiranTitlebarWindow::sizeHint() const
{
    QSize sizeHint = QWidget::sizeHint();
    if(d_ptr->m_isCompositingManagerRunning)
    {
        sizeHint.setWidth(2*SHADOW_BORDER_WIDTH+sizeHint.width());
        sizeHint.setHeight(2*SHADOW_BORDER_WIDTH+sizeHint.height());
    }
    return sizeHint;
}
