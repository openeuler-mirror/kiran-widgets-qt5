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
#pragma once

#include "kiran-sidebar-widget.h"
#include "kiran-siderbar-delegate.h"

class KiranSidebarWidgetPrivate : QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranSidebarWidget)
public:
    KiranSidebarWidgetPrivate(QObject* parent = nullptr);
    ~KiranSidebarWidgetPrivate();

    void init(KiranSidebarWidget* ptr);

private:
    KiranSidebarWidget* q_ptr;
    KiranSiderbarDelegate* m_delegate;
};