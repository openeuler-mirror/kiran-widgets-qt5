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
 * @file   titlebar-window-ui.h
 * @brief  通过派生使用ui创建控件的方法来使用KiranTitlebarWindow自定义标题栏窗口的例子
 */
 
#ifndef TITLEBARWINDOWUI_H
#define TITLEBARWINDOWUI_H

#include <QWidget>

#include <kiranwidgets-qt5/kiran-titlebar-window.h>
namespace Ui {
class TitlebarWindowUI;
}

class TitlebarWindowUI : public KiranTitlebarWindow
{
    Q_OBJECT

public:
    explicit TitlebarWindowUI(QWidget *parent = nullptr);
    ~TitlebarWindowUI();

private:
    Ui::TitlebarWindowUI *ui;
};

#endif // TITLEBARWINDOWUI_H
