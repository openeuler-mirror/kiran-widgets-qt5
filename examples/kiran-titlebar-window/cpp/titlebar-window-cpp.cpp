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
 
#include "titlebar-window-cpp.h"
#include <QIcon>
#include <QLineEdit>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
TitlebarWindowCPP::TitlebarWindowCPP(QWidget *parent) :
    KiranTitlebarWindow()
{
    ///设置窗口标题栏
    setTitle("KiranTitlebarWindowCPP");
    ///设置窗口图标
    setIcon(QIcon::fromTheme("window"));
    ///设置窗口按钮
    setButtonHints(KiranTitlebarWindow::TitlebarMinimizeButtonHint|KiranTitlebarWindow::TitlebarCloseButtonHint);
    ///设置是否允许窗口拖拽Resize
    setResizeable(false);
    ///标题栏添加自定义控件
    QLineEdit* edit = new QLineEdit;
    edit->setPlaceholderText("KiranTitlebarWindowCPP");
    QToolButton* btn = new QToolButton;
    btn->setText("BUTTON");
    getTitlebarCustomLayout()->addWidget(edit);
    getTitlebarCustomLayout()->addWidget(btn);
    getTitlebarCustomLayout()->setSpacing(10);

    ///初始化自定义标题栏窗口内容
    initUI();
}

TitlebarWindowCPP::~TitlebarWindowCPP()
{

}

void TitlebarWindowCPP::initUI()
{
    QWidget* windowContentWidget = getWindowContentWidget();
    QVBoxLayout* vLayout = new QVBoxLayout(windowContentWidget);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    QLabel* label = new QLabel(windowContentWidget);
    label->setAlignment(Qt::AlignCenter);
    label->setText("KiranTitlebarWindowCPP");
    label->setStyleSheet("QLabel{color:pink;font:40px;}");
    vLayout->addWidget(label);


}
