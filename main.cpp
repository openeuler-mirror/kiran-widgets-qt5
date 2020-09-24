#include <QApplication>

#include "kiran-titlebar-window/kiran-titlebar-window.h"


int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    KiranTitlebarWindow window;
    window.setTitle("Test");
    window.setMinimumSize(640,480);
    window.show();
    return app.exec();
}
