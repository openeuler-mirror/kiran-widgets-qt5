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
 
#include "window-demo.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qevent.h>
#include <qdebug.h>
#include <qapplication.h>

WindowDemo::WindowDemo()
        : KiranTitlebarWindow()
{
    initUI();
}

WindowDemo::~WindowDemo()
{

}

void WindowDemo::initUI()
{
    QWidget *windowContentWidget = getWindowContentWidget();
    auto vboxLayout = new QVBoxLayout(windowContentWidget);

    /* 使用全局字体的普通Label */
    m_normalLabel = new QLabel("Normal Label", this);
    vboxLayout->addWidget(m_normalLabel);

    /* 使用特殊字体的特殊label */
    m_specialLabel = new QLabel("Font Special Label", this);
    /* 给需要特殊字号或特殊字体的控件安装事件过滤 */
    m_specialLabel->installEventFilter(this);
    vboxLayout->addWidget(m_specialLabel);
    
    /* 给需要特殊字号的控件设置字体 */
    updateSpecialFont();
}

/* 过滤控件事件 */
bool WindowDemo::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_specialLabel
        && event->type() == QEvent::ApplicationFontChange) {
        /* 更新特殊字号字体 */
        updateSpecialFont();
        return true;
    }
    return QObject::eventFilter(watched, event);
}

void WindowDemo::updateSpecialFont()
{
    /* 取出当前桌面环境应用程序字体，根据字体需求设置字体进控件 */
    QFont font = QApplication::font();
    /* 可以设置控件固定大小字体或以普通字体作为基准更新控件字体 */
}
