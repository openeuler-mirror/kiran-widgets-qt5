#include "widget.h"

#include "kiran-application.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    KiranApplication a(argc, argv);

    Widget w;
    w.show();

    return qApp->exec();
}
