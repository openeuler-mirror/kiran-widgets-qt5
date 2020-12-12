#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "kiran-titlebar-window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public KiranTitlebarWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void initTabBar();
    void initPushButtonTab();
    void initSwitchButtonTab();
    void initComboBoxTab();
    void initSearchBox();
    void initProgressBar();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
