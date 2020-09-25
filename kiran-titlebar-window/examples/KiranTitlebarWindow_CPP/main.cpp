#include <QApplication>

#include "titlebar-window-cpp.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    TitlebarWindowCPP window;
    window.setMinimumSize(640,480);
    window.show();

    return app.exec();
}
