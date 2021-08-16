 /**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 */
 
/*
 * @file   main.cpp
 * @brief　实例化使用KiranMessageBox例子
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