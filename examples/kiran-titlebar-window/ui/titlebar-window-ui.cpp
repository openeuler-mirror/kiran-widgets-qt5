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
 
#include "titlebar-window-ui.h"
#include "ui_titlebar-window-ui.h"

#include <QIcon>
#include <QLineEdit>
#include <QToolButton>
TitlebarWindowUI::TitlebarWindowUI(QWidget *parent) :
    KiranTitlebarWindow(),
    ui(new Ui::TitlebarWindowUI)
{
    setFocusPolicy(Qt::StrongFocus);
    ///设置窗口标题栏
    setTitle("TitlebarWindowUI");
    ///设置窗口图标
    setIcon(QIcon::fromTheme("window"));
    ///设置窗口按钮
    setButtonHints(KiranTitlebarWindow::TitlebarMinimizeButtonHint|KiranTitlebarWindow::TitlebarCloseButtonHint);
    ///设置是否允许窗口拖拽Resize
    setResizeable(false);
    ///标题栏添加自定义控件
    QLineEdit* edit = new QLineEdit;
    edit->setPlaceholderText("KiranTitlebarWindowUI");
    QToolButton* btn = new QToolButton;
    btn->setStyleSheet("QToolButton:hover{background:pink;}");
    btn->setText("BUTTON");
    getTitlebarCustomLayout()->addWidget(edit);
    getTitlebarCustomLayout()->addWidget(btn);
    getTitlebarCustomLayout()->setSpacing(10);
    ///WARNING:因为传入setupUI的参数为KiranTitlebarWindow创建的自定义窗口控件，而不是this
    ///1.导致在ui文件中添加的信号和槽的连接将异常
    ///2.不能通过右键控件“转到槽”来添加槽函数。
    ///若需要通过2的方式添加槽函数的话，需要在setupUI之后调用QMetaObject::connectSlotsByName(this)
    ///才能正确通过槽函数名称连接相应控件的信号
    ui->setupUi(getWindowContentWidget());
    setContentWrapperMarginBottom(0);
}

TitlebarWindowUI::~TitlebarWindowUI()
{
    delete ui;
}
