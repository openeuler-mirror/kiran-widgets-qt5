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
