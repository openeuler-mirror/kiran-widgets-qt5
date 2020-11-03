#include <QApplication>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QFile>
#include <QLineEdit>

#include "kiran-titlebar-window/kiran-titlebar-window.h"
#include "kiran-message-box/kiran-message-box.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
#if 1
    KiranTitlebarWindow window;
    window.setObjectName("KiranTitlebarWindow");
    window.setTitle("Test");
    window.setMinimumSize(640,480);

    QLineEdit *edit = new QLineEdit(window.getWindowContentWidget());
    window.show();
#else
    KiranMessageBox::infomation(nullptr,"Warning","test",KiranMessageBox::Yes|KiranMessageBox::No);
#endif
    return app.exec();
}
