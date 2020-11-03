#ifndef TITLEBARWINDOWUI_H
#define TITLEBARWINDOWUI_H

#include <QWidget>

#include <kiranwidgets-qt5/kiran-titlebar-window.h>
class TitlebarWindowCPP : public KiranTitlebarWindow
{
    Q_OBJECT

public:
    explicit TitlebarWindowCPP(QWidget *parent = nullptr);
    ~TitlebarWindowCPP();

private:
    void initUI();
};

#endif // TITLEBARWINDOWUI_H
