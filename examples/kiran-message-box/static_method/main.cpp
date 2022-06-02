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
 * @brief  调用KiranMessageBox静态方法显示弹窗提示
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