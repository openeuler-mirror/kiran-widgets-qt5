 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd. 
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */
 
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