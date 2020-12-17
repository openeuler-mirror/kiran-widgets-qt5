#include "widget.h"

#include "kiran-application.h"
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    KiranApplication a(argc, argv);

//    qApp->setStyle(QStyleFactory::create("adwaita-dark"));

    Widget w;
    w.show();

    return KiranApplication::exec();
}
