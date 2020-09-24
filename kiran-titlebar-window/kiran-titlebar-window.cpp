#include "kiran-titlebar-window.h"
#include "kiran-titlebar-window-private.h"
#include "global_define.h"
#include "xlib-helper.h"

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

    setTitle(qApp->applicationName());

    initConnect();
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

void KiranTitlebarWindow::setButtonsHint(TitlebarButtonHintFlags hints)
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

void KiranTitlebarWindow::setContentWrapperMarginBottom(int contentWrapperMarginBottom)
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    if(contentMargins.bottom()==contentWrapperMarginBottom){
        return;
    }
    contentMargins.setBottom(contentWrapperMarginBottom);
    d_func()->m_windowContentWidgetWrapper->setContentsMargins(contentMargins);
}

void KiranTitlebarWindow::setContentWrapperMarginRight(int contentWrapperMarginRight)
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    if(contentMargins.right()==contentWrapperMarginRight){
        return;
    }
    contentMargins.setRight(contentWrapperMarginRight);
    d_func()->m_windowContentWidgetWrapper->setContentsMargins(contentMargins);
}

void KiranTitlebarWindow::setContentWrapperMarginLeft(int contentWrapperMarginLeft)
{
    QMargins contentMargins = d_func()->m_windowContentWidgetWrapper->contentsMargins();
    if(contentMargins.left()==contentWrapperMarginLeft){
        return;
    }
    contentMargins.setLeft(contentWrapperMarginLeft);
    d_func()->m_windowContentWidgetWrapper->setContentsMargins(contentMargins);
}

QWidget *KiranTitlebarWindow::getWindowContentWidget()
{
    return d_func()->m_windowContentWidget;
}

QHBoxLayout *KiranTitlebarWindow::getTitleBarCustomLayout()
{
    return d_func()->m_customLayout;
}

void KiranTitlebarWindow::initConnect()
{
    connect(d_func()->m_btnMin,&QPushButton::clicked,[this](bool checked){
        Q_UNUSED(checked);
        showMinimized();
    });
    connect(d_func()->m_btnMax,&QPushButton::clicked,[this](bool checked){
        Q_UNUSED(checked);
        if(isMaximized()){
            showNormal();
        }else{
            showMaximized();
        }
    });
    connect(d_func()->m_btnClose,&QPushButton::clicked,[this](bool checked){
        Q_UNUSED(checked);
        close();
    });
}

bool KiranTitlebarWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverMove:
        d_func()->handlerHoverMoveEvent(dynamic_cast<QHoverEvent*>(event));
        break;
    case QEvent::Leave:
        d_func()->handlerLeaveEvent();
        break;
    case QEvent::MouseButtonPress:
        d_func()->handlerMouseButtonPressEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseButtonRelease:
        d_func()->handlerMouseButtonReleaseEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseMove:
        d_func()->handlerMouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::ShowToParent:
        d_func()->updateStyle(false);
        XLibHelper::SetShadowWidth(QX11Info::display(),winId(),SHADOW_BORDER_WIDTH,SHADOW_BORDER_WIDTH,SHADOW_BORDER_WIDTH,SHADOW_BORDER_WIDTH);
        break;
    case QEvent::MouseButtonDblClick:
        d_func()->handlerMouseDoubleClickEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::WindowStateChange:
        qInfo() << windowState();
        qInfo() << windowIcon();
        qInfo() << windowTitle();
        d_func()->updateStyle(windowState()==Qt::WindowFullScreen);
    default:
        break;
    }
    return QWidget::event(event);
}
