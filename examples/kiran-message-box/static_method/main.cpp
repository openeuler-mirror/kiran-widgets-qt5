/*
 * @file   main.cpp
 * @brief  调用KiranMessageBox静态方法显示弹窗提示
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#include <QApplication>
#include <kiranwidgets-qt5/kiran-message-box.h>
#include <QDebug>

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    /* 调用KiranMessageBox静态方法 */
    KiranMessageBox::KiranStandardButton button = KiranMessageBox::message(nullptr,"Warning","Just Test",KiranMessageBox::Yes|KiranMessageBox::No);
    if(button == KiranMessageBox::Yes){
        qInfo() << "yes";
    }else{
        qInfo() << "No";
    }
    return 0;
}