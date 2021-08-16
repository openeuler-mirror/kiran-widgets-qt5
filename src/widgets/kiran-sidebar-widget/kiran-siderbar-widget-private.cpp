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
 
#include "kiran-siderbar-widget-private.h"
#include <QDebug>

KiranSidebarWidgetPrivate::KiranSidebarWidgetPrivate(QObject *parent)
    : QObject(parent)
{

}

KiranSidebarWidgetPrivate::~KiranSidebarWidgetPrivate()
{

}

void KiranSidebarWidgetPrivate::init(KiranSidebarWidget* ptr)
{
    q_ptr = ptr;
    qDebug() << __FUNCTION__  << "setSpacing";
    q_ptr->setSpacing(12);
    q_ptr->setSelectionBehavior(QListView::SelectRows);
    q_ptr->setSelectionMode(QListView::SingleSelection);
}
