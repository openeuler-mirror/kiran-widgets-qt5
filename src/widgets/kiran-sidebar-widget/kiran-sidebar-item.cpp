/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */

#include "kiran-sidebar-item.h"
#include "kiran-sidebar-define.h"

KiranSidebarItem::KiranSidebarItem(QListWidget *view, int type) : QListWidgetItem(view, type)
{
}

KiranSidebarItem::KiranSidebarItem(const QString &text, QListWidget *view, int type) : QListWidgetItem(text, view, type)
{
}

KiranSidebarItem::KiranSidebarItem(const QIcon &icon, const QString &text, QListWidget *view, int type) : QListWidgetItem(icon, text, view, type)
{
}

KiranSidebarItem::KiranSidebarItem(const QListWidgetItem &other) : QListWidgetItem(other)
{
}

KiranSidebarItem::~KiranSidebarItem()
{
}

void KiranSidebarItem::setStatusDesc(const QString &desc, const QColor &color)
{
    setData(ItemStatus_Role, desc);
    setData(ItemStatusColor_Role, color);
}

void KiranSidebarItem::getStatusDesc(QString &desc, QColor &color)
{
    QVariant statusRoleVar = data(ItemStatus_Role);
    QVariant colorRoleVar = data(ItemStatusColor_Role);

    if (statusRoleVar.isValid() && !statusRoleVar.isNull() && statusRoleVar.type() == QVariant::String &&
        colorRoleVar.isValid() && !colorRoleVar.isNull() && colorRoleVar.type() == QVariant::Color)
    {
        desc = statusRoleVar.toString();
        color = qvariant_cast<QColor>(colorRoleVar);
    }
}
