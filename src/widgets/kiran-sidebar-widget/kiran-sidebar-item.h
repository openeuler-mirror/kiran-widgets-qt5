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

#pragma once

#include <QListWidgetItem>

class KiranSidebarItem : public QListWidgetItem
{
public:
    explicit KiranSidebarItem(QListWidget *view = nullptr, int type = Type);
    explicit KiranSidebarItem(const QString &text, QListWidget *view = nullptr, int type = Type);
    explicit KiranSidebarItem(const QIcon &icon, const QString &text,
                              QListWidget *view = nullptr, int type = Type);
    KiranSidebarItem(const QListWidgetItem &other);
    virtual ~KiranSidebarItem();

    void setStatusDesc(const QString &desc, const QColor &color);
    void getStatusDesc(QString &desc, QColor &color);
};