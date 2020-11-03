//
// Created by lxh on 2020/11/3.
//

#include <QApplication>
#include <kiranwidgets-qt5/kiran-message-box.h>
#include <QDebug>

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    KiranMessageBox::KiranStandardButton button = KiranMessageBox::message(nullptr,"Warning","Just Test",KiranMessageBox::Yes|KiranMessageBox::No);
    if(button == KiranMessageBox::Yes){
        qInfo() << "yes";
    }else{
        qInfo() << "No";
    }
    return 0;
}