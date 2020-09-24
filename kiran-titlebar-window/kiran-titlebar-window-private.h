#ifndef KIRANTITLEBARWINDOWPRIVATE_H
#define KIRANTITLEBARWINDOWPRIVATE_H

#include <QObject>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

#include "global_define.h"
#include "kiran-titlebar-window.h"

class QGraphicsDropShadowEffect;

class KiranTitlebarWindowPrivate
{
    Q_DECLARE_PUBLIC(KiranTitlebarWindow);
public:
    KiranTitlebarWindowPrivate(KiranTitlebarWindow* ptr);
    ~KiranTitlebarWindowPrivate();

private:
    void init();
    void setIcon(const QIcon& icon);
    void setTitle(const QString& title);
    void setButtonHints(KiranTitlebarWindow::TitlebarButtonHintFlags hints);
    void setWindowContentWidget(QWidget *widget);

private:
    void handlerHoverMoveEvent(QHoverEvent* ev);
    void handlerLeaveEvent();
    void handlerMouseButtonPressEvent(QMouseEvent* ev);
    void handlerMouseButtonReleaseEvent(QMouseEvent* ev);
    void handlerMouseMoveEvent(QMouseEvent* ev);
    void handlerMouseDoubleClickEvent(QMouseEvent *ev);

protected:
    void initOtherWidget();
    void updateStyle(bool fullScreen = false);

    Kiran::CursorPositionEnums getCursorPosition(QPoint pos);

private:
    KiranTitlebarWindow* q_ptr;
    QLayout* m_layout;
    QFrame*  m_frame;
    QLayout* m_frameLayout;
    QWidget* m_titlebarWidget;
    QLabel*  m_titleIcon;
    QLabel*  m_title;
    QHBoxLayout* m_customLayout;
    KiranTitlebarWindow::TitlebarButtonHintFlags m_buttonHints;
    QPushButton* m_btnMin;
    QPushButton* m_btnMax;
    QPushButton* m_btnClose;
    QWidget* m_windowContentWidgetWrapper;
    QWidget* m_windowContentWidget;

    bool m_titlebarIsPressed;
    bool m_resizeable;

    QGraphicsDropShadowEffect* m_shadowEffect;
    bool m_isCompositingManagerRunning;
};

#endif // KIRANTITLEBARWINDOWPRIVATE_H
