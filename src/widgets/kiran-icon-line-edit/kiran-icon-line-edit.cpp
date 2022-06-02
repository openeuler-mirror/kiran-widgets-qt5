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

#include "kiran-icon-line-edit.h"
#include "kiran-icon-line-edit-private.h"
#include "widget-private-property-helper.h"

#include <QPainter>
#include <QStyle>

using namespace Kiran;

KiranIconLineEdit::KiranIconLineEdit(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new KiranIconLineEditPrivate(this))
{
    d_ptr->init(this);
}

KiranIconLineEdit::KiranIconLineEdit(const QString &text, QWidget *parent)
    : QLineEdit(text, parent),
      d_ptr(new KiranIconLineEditPrivate(this))
{
    d_ptr->init(this);
}

KiranIconLineEdit::~KiranIconLineEdit()
{
}

void KiranIconLineEdit::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

QIcon KiranIconLineEdit::icon()
{
    return m_icon;
}

void KiranIconLineEdit::setIconSize(QSize iconSize)
{
    WidgetPrivatePropertyHelper::setLineEditIconSize(this, iconSize);
}

QSize KiranIconLineEdit::iconSize()
{
    return WidgetPrivatePropertyHelper::getLineEditIconSize(this);
}

void KiranIconLineEdit::setIconPosition(IconLineEditIconPosition position)
{
    return WidgetPrivatePropertyHelper::setLineEditIconPosition(this, position);
}

Kiran::IconLineEditIconPosition KiranIconLineEdit::iconPosition()
{
    return WidgetPrivatePropertyHelper::getLineEditIconPosition(this);
}

void KiranIconLineEdit::paintEvent(QPaintEvent *ev)
{
    QLineEdit::paintEvent(ev);

    auto size     = iconSize();
    auto position = iconPosition();
    if (m_icon.isNull() || size.isNull() || position == Kiran::ICON_POSITION_NONE)
    {
        return;
    }

    QRect  widgetRect         = this->rect();
    int    lineEditFrameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, nullptr, this);
    QPoint topLeft;
    switch (position)
    {
    case ICON_POSITION_LEFT:
        topLeft.setX(widgetRect.left() + lineEditFrameWidth);
        break;
    case ICON_POSITION_RIGHT:
        topLeft.setX(widgetRect.right() - lineEditFrameWidth - size.width());
        break;
    case ICON_POSITION_NONE:
        return;
    }
    topLeft.setY(widgetRect.top() + (widgetRect.height() - size.height()) / 2);
    QRect iconRect(topLeft, size);

    QPainter    painter(this);
    QIcon::Mode iconMode = QIcon::Normal;
    if (!this->isEnabled())
    {
        iconMode = QIcon::Disabled;
    }

    m_icon.paint(&painter, iconRect, Qt::AlignCenter, iconMode);
}
