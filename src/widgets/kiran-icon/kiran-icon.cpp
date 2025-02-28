/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiran-widgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     yuanxing <yuanxing@kylinsec.com.cn>
 */

#include "kiran-icon.h"
#include "kiran-icon-private.h"

#include <QPainter>
KiranIcon::KiranIcon(QWidget *parent)
    : QWidget(parent),
      d_ptr(new KiranIconPrivate(this))
{
}

void KiranIcon::setIcon(const QIcon &icon)
{
    d_ptr->m_icon = icon;
    update();
}

QIcon KiranIcon::icon()
{
    return d_ptr->m_icon;
}

void KiranIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    if (!d_ptr->m_icon.isNull())
    {
        d_ptr->m_icon.paint(&painter, rect());
    }
}
