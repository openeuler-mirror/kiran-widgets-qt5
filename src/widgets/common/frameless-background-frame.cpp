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

#include "frameless-background-frame.h"
#include <QApplication>
#include <QBitmap>
#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QRegion>

FramelessBackgroundFrame::FramelessBackgroundFrame(QWidget *parent, Qt::WindowFlags f)
    : QFrame(parent, f),
      m_radius(8)
{
    updateMask();
}

FramelessBackgroundFrame::~FramelessBackgroundFrame()
{
}

int FramelessBackgroundFrame::getRadius() const
{
    return m_radius;
}

void FramelessBackgroundFrame::setRadius(int radius)
{
    if (m_radius != radius)
    {
        m_radius = radius;
        updateMask();
        update();
    }
}

void FramelessBackgroundFrame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPalette qPalette = qApp->palette();
    QColor background, border;

    painter.setRenderHint(QPainter::Antialiasing);
    border = QColor("#484848");

    if (!isEnabled())
    {
        background = qPalette.color(QPalette::Disabled, QPalette::Window);
    }
    else
    {
        background = qPalette.color(QPalette::Normal, QPalette::Window);
    }

    QPainterPath painterPath;
    painterPath.addRoundedRect(rect(), m_radius, m_radius);

    painter.fillPath(painterPath, background);
    if (m_drawBorder)
    {
        painter.setPen(border);
        painter.drawPath(painterPath);
    }
}

void FramelessBackgroundFrame::resizeEvent(QResizeEvent *event)
{
    updateMask();
    QWidget::resizeEvent(event);
}

void FramelessBackgroundFrame::updateMask()
{
    if (m_radius)
    {
        clearMask();
        return;
    }

    QBitmap maskBitMap(this->width(), this->height());
    QPainter bitMapPainter(&maskBitMap);
    QPainterPath painterPath;
    bitMapPainter.setRenderHint(QPainter::Antialiasing);
    painterPath.addRoundedRect(rect(), m_radius, m_radius);
    bitMapPainter.fillPath(painterPath, Qt::black);
    setMask(maskBitMap);
}

bool FramelessBackgroundFrame::getDrawBorder()
{
    return m_drawBorder;
}

void FramelessBackgroundFrame::setDrawBorder(bool drawBorder)
{
    if (m_drawBorder != drawBorder)
    {
        m_drawBorder = drawBorder;
        update();
    }
}