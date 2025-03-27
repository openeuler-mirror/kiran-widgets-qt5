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
#include "kiran-siderbar-delegate.h"

KiranSidebarWidgetPrivate::KiranSidebarWidgetPrivate(QObject* parent)
    : QObject(parent),
      q_ptr(nullptr),
      m_delegate(nullptr)
{
}

KiranSidebarWidgetPrivate::~KiranSidebarWidgetPrivate()
{
}

void KiranSidebarWidgetPrivate::init(KiranSidebarWidget* ptr)
{
    q_ptr = ptr;
    q_ptr->setSpacing(8);
    q_ptr->setViewportMargins(8, 8, 8, 8);
    q_ptr->setSelectionBehavior(QListView::SelectRows);
    q_ptr->setSelectionMode(QListView::SingleSelection);
    q_ptr->setAlternatingRowColors(false);

    m_delegate = new KiranSiderbarDelegate(q_ptr);
    q_ptr->setItemDelegate(m_delegate);
}
