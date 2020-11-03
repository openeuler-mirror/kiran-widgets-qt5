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

QHBoxLayout *KiranTitlebarWindow::getTitlebarCustomLayout()
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
    connect(qApp,&QApplication::focusChanged,[this](QWidget *old, QWidget *now){
        qInfo() << "old focus:" << ((old!=nullptr)?old->objectName():"nullptr");
        qInfo() << "new focus:" << ((now!= nullptr)?now->objectName():"nullptr");
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
    {
        d_func()->enableShadow(false);
        ///NOTE:获取缩放率x(阴影边框宽度+窗口边框)
        int shadowBorderWidth = (SHADOW_BORDER_WIDTH+1)*devicePixelRatio();
        break;
    }
    case QEvent::MouseButtonDblClick:
        d_func()->handlerMouseDoubleClickEvent(dynamic_cast<QMouseEvent*>(event));
        break;
    case QEvent::WindowStateChange:
        qInfo() << windowState();
        d_func()->enableShadow(windowState()& Qt::WindowFullScreen);
        break;
    case QEvent::ActivationChange:
        d_func()->updateShadowStyle(isActiveWindow());
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

#include <xcb/xcb_event.h>
#include <xcb/xcb.h>
bool KiranTitlebarWindow::nativeEvent(const QByteArray &eventType, void *message, long *result) {
    if( eventType != "xcb_generic_event_t" ){
        return QWidget::nativeEvent(eventType,message,result);
    }
    xcb_generic_event_t * xcb_event = (xcb_generic_event_t*) message;
    if( xcb_event->response_type == 35 ){
        return QWidget::nativeEvent(eventType,message,result);
    }
    if( xcb_event->response_type == 10 ){
        xcb_focus_out_event_t*  xcb_focus_out = (xcb_focus_out_event_t*)(xcb_event);
        qInfo() << "FocusOut:" << xcb_focus_out->event;
    }else if( xcb_event->response_type == 9 ) {
        xcb_focus_in_event_t* xcb_focus_in = (xcb_focus_in_event_t*)(xcb_event);
        qInfo() << "FocusIn:" << xcb_focus_in->event;
        qInfo() << "FocusObject:" << qApp->focusObject();
        qInfo() << "FocusWindow:" << qApp->focusWindow();
//        qInfo() << "focus object name" << (qApp->focusWidget()?qApp->focusWidget():"nullptr");
        qInfo() << "windowHasFocus:" <<  hasFocus();
        qInfo() << "isActiveWindow:" << isActiveWindow();
    }else{
        qInfo() << xcb_event->response_type <<  xcb_event_get_label(xcb_event->response_type);
    }

    return QWidget::nativeEvent(eventType,message,result);
}
