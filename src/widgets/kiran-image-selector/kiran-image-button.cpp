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

#include "kiran-image-button.h"
#include "widget-draw-helper.h"

#include <palette.h>
#include <QEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QStyleOption>

using namespace Kiran::Theme;

KiranImageButton::KiranImageButton(QWidget *parent, bool leftSide)
    : QPushButton(parent),
      m_anchorParentLeftSide(leftSide)
{
    parent->installEventFilter(this);
}

KiranImageButton::~KiranImageButton()
{
}

bool KiranImageButton::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Resize:
    {
        QSize size = dynamic_cast<QResizeEvent *>(event)->size();
        this->setFixedHeight(size.height());
        this->move(m_anchorParentLeftSide ? QPoint(0, 0) : QPoint(size.width() - rect().width(), 0));
        break;
    }
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}

void KiranImageButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QStyleOption option;
    option.initFrom(this);

    option.state &= ~QStyle::State_Active;
    if (isDown())
    {
        option.state |= QStyle::State_Active;
    }
    else if (underMouse())
    {
        option.state |= QStyle::State_MouseOver;
    }

    bool isAnchorLeft = mapToParent(QPoint(0, 0)).x() == 0;
    QPainterPath painterPath = WidgetDrawHelper::getRoundedRectanglePath(option.rect.adjusted(0.5, 0.5, -0.5, -0.5),
                                                                         isAnchorLeft ? 4 : 0,
                                                                         isAnchorLeft ? 0 : 4,
                                                                         isAnchorLeft ? 4 : 0,
                                                                         isAnchorLeft ? 0 : 4);
    auto background = DEFAULT_PALETTE()->getColor(Palette::ColorGroup::ACTIVE, Palette::ColorRole::WIDGET);
    background.setAlphaF(0.48);
    painter.fillPath(painterPath, background);

    style()->drawPrimitive(isAnchorLeft ? QStyle::PE_IndicatorArrowLeft : QStyle::PE_IndicatorArrowRight, &option, &painter, this);
}

bool KiranImageButton::anchorParentLeftSide()
{
    return m_anchorParentLeftSide;
}
