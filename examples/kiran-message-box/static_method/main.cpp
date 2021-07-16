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