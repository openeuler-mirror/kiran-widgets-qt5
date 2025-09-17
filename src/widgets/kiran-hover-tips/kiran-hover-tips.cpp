/**
 * Copyright (c) 2021 ~ 2022 KylinSec Co., Ltd.
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

#include "kiran-hover-tips.h"
#include "common/logging-category.h"
#include "kiran-hover-tips-private.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>

static const int KiranWidgetHoverTipsHeight = 36;

KiranHoverTips::KiranHoverTips(QWidget *parent)
    : QWidget(parent),
      d_ptr(new KiranHoverTipsPrivate(this))
{
    d_ptr->init();
}

KiranHoverTips::~KiranHoverTips()
{
}

void KiranHoverTips::showTips(HoverTipsTypeEnum typeEnum, const QString &msg)
{
    auto iter = d_ptr->m_tipsTypeIconMap.find(typeEnum);
    if (iter == d_ptr->m_tipsTypeIconMap.end())
    {
        qWarning(kiranWidgets) << "invalid type enum";
        return;
    }

    if (isVisible())
    {
        hide();
    }

    QString pixmapPath = iter.value();
    d_ptr->m_iconLabel->setPixmap(pixmapPath);
    d_ptr->m_textLabel->setText(msg);

    QWidget::raise();
    QWidget::show();

    d_ptr->startHideTimer();
}

void KiranHoverTips::setIcon(KiranHoverTips::HoverTipsTypeEnum typeEnum, const QString &icon)
{
    QPixmap pixmap;
    if (!pixmap.load(icon) || pixmap.isNull())
    {
        qWarning(kiranWidgets) << "load icon failed.";
        return;
    }
    d_ptr->m_tipsTypeIconMap[typeEnum] = icon;
}

void KiranHoverTips::paintEvent(QPaintEvent *event)
{
    QStyleOption styleOption;
    styleOption.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}

void KiranHoverTips::setTimeout(quint32 ms)
{
    if (d_ptr->m_hideTimeout == ms)
    {
        return;
    }

    if (ms == 0)
    {
        d_ptr->stopHideTimer();
        return;
    }

    d_ptr->m_hideTimeout = ms;
}

KiranHoverTipsPrivate::KiranHoverTipsPrivate(KiranHoverTips *ptr) : QObject(ptr)
{
    q_ptr = ptr;
    m_iconLabel = nullptr;
    m_textLabel = nullptr;
}

KiranHoverTipsPrivate::~KiranHoverTipsPrivate()
{
}

void KiranHoverTipsPrivate::init()
{
    auto *mainLayout = new QHBoxLayout(q_ptr);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(12, -1, 12, -1);

    m_iconLabel = new QLabel(q_ptr);
    m_iconLabel->setObjectName("label_icon");
    m_iconLabel->setFixedSize(16, 16);
    mainLayout->addWidget(m_iconLabel);

    m_textLabel = new QLabel(q_ptr);
    m_textLabel->setObjectName("label_text");
    m_textLabel->setScaledContents(false);
    mainLayout->addWidget(m_textLabel);

    q_ptr->setVisible(false);
    q_ptr->setFixedHeight(KiranWidgetHoverTipsHeight);
    q_ptr->installEventFilter(this);
}

bool KiranHoverTipsPrivate::event(QEvent *event)
{
    if (event->type() == QEvent::Timer)
    {
        auto timerEvent = dynamic_cast<QTimerEvent *>(event);
        if (timerEvent->timerId() == m_hideTimerID)
        {
            q_ptr->QWidget::hide();
            stopHideTimer();
        }
    }
    return QObject::event(event);
}

bool KiranHoverTipsPrivate::eventFilter(QObject *watched, QEvent *event)
{
    QEvent::Type eventType = event->type();
    if (watched == q_ptr)
    {
        switch (eventType)
        {
        case QEvent::ShowToParent:
        {
            q_ptr->adjustSize();
            updatePosition();
            break;
        }
        case QEvent::MouseButtonPress:
        {
            q_ptr->QWidget::hide();
            stopHideTimer();
            break;
        }
        default:
            break;
        }
    }
    else if (watched == q_ptr->parentWidget())
    {
        switch (eventType)
        {
        case QEvent::Resize:
            updatePosition();
            break;
        case QEvent::Move:
            updatePosition();
            break;
        default:
            break;
        }
    }
    return QObject::eventFilter(watched, event);
}

void KiranHoverTipsPrivate::updatePosition()
{
    if (q_ptr->parentWidget() == nullptr)
    {
        qWarning(kiranWidgets) << "hover tips parnetwidget is null";
        return;
    }

    QPoint leftTop;
    QSize parentWidgetSize = q_ptr->parentWidget()->size();
    leftTop.setX((parentWidgetSize.width() - q_ptr->width()) / 2);
    leftTop.setY((parentWidgetSize.height() - q_ptr->height()) / 2);

    q_ptr->move(leftTop);
}

void KiranHoverTipsPrivate::startHideTimer()
{
    if (m_hideTimeout == 0)
    {
        return;
    }
    stopHideTimer();
    m_hideTimerID = startTimer(m_hideTimeout);
}

void KiranHoverTipsPrivate::stopHideTimer()
{
    if (m_hideTimerID == -1)
    {
        return;
    }
    killTimer(m_hideTimerID);
    m_hideTimerID = -1;
}
