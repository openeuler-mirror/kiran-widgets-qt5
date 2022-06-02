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
 
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "kiran-titlebar-window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public KiranTitlebarWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void initTabBar();
    void initPushButtonTab();
    void initSwitchButtonTab();
    void initComboBoxTab();
    void initSearchBox();
    void initProgressBar();
    void initIconLineEdit();
    void initKiranImageSelector();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
