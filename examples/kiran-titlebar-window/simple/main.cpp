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
 
#include <QApplication>
#include <QIcon>
#include <QLineEdit>
#include <QToolButton>
#include <QHBoxLayout>

#include <kiranwidgets-qt5/kiran-titlebar-window.h>
#include "titlebar-window-simple.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    KiranTitlebarWindow window;
    ///设置窗口标题栏
    window.setTitle("TitlebarWindowSimple");
    ///设置窗口图标
    window.setIcon(QIcon::fromTheme("window"));
    ///设置窗口按钮
    window.setButtonHints(KiranTitlebarWindow::TitlebarMinimizeButtonHint|KiranTitlebarWindow::TitlebarCloseButtonHint);
    ///设置是否允许窗口拖拽Resize
    window.setResizeable(false);
    ///标题栏添加自定义控件
    QLineEdit* edit = new QLineEdit;
    edit->setPlaceholderText("TitlebarWindowSimple");
    QToolButton* btn = new QToolButton;
    btn->setText("BUTTON");
    window.getTitlebarCustomLayout()->addWidget(edit);
    window.getTitlebarCustomLayout()->addWidget(btn);
    window.getTitlebarCustomLayout()->setSpacing(10);
    TitlebarWindowSimple simple;
    window.setWindowContentWidget(&simple);

    window.resize(640,480);
    window.show();
    return app.exec();
}
