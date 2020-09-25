#ifndef TITLEBARWINDOWUI_H
#define TITLEBARWINDOWUI_H

#include <QWidget>

#include <kiranwidgets-qt5/kiran-titlebar-window.h>
namespace Ui {
class TitlebarWindowUI;
}

class TitlebarWindowUI : public KiranTitlebarWindow
{
    Q_OBJECT

public:
    explicit TitlebarWindowUI(QWidget *parent = nullptr);
    ~TitlebarWindowUI();

private:
    Ui::TitlebarWindowUI *ui;
};

#endif // TITLEBARWINDOWUI_H
