/*
 * @file   main.cpp
 * @brief　实例化使用KiranMessageBox例子
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
#include <QApplication>
#include <kiranwidgets-qt5/kiran-message-box.h>
#include <QPushButton>
#include <QDebug>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    KiranMessageBox box;
    box.setTitle("Information");
    box.setText("Just Example");

    QPushButton *btn = new QPushButton;
    btn->setText("conrfirm");
    btn->setFixedSize(box.buttonSize());

    QPushButton *btn_1 = new QPushButton;
    btn_1->setText("cancel");
    btn_1->setFixedSize(box.buttonSize());

    /* 添加按钮 */
    box.addButton(btn,QDialogButtonBox::AcceptRole);
    box.addButton(btn_1,QDialogButtonBox::RejectRole);

    box.exec();
    if( box.clickedButton() == btn ){
        qInfo() << "confrim";
    }else{
        qInfo() << "cancel";
    }

    return 0;
}