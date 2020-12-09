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