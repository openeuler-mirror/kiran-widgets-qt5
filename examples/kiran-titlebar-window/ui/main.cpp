#include <QApplication>

#include "titlebar-window-ui.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    TitlebarWindowUI window;
    window.setMinimumSize(640,480);
    window.show();

    return app.exec();
}
