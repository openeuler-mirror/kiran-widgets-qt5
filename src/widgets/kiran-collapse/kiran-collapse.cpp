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
 * Author:     youzhengcai <youzhengcai@kylinsec.com.cn>
 */

#include "kiran-collapse.h"
#include "ui_kiran-collapse.h"

#include <palette.h>
#include <QDebug>
#include <QEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QMargins>

using namespace Kiran::Theme;

// 私有类实现
class KiranCollapse::KiranCollapsePrivate
{
public:
    KiranCollapsePrivate(KiranCollapse* q)
        : q_ptr(q)
    {
    }

    ~KiranCollapsePrivate()
    {
    }

    void init()
    {
        q_ptr->ui->expansionSpace->setAttribute(Qt::WA_StyledBackground);
        q_ptr->ui->expansionSpaceContainer->setSpacing(12);
        q_ptr->ui->expansionSpaceContainer->setContentsMargins(m_expansionMarginLeft,
                                                      m_expansionMarginTop,
                                                      m_expansionMarginRight,
                                                      m_expansionMarginBottom);
        q_ptr->ui->topBar->setTitle(m_topBarTitle);
        // 若为扩展区控件为空，则不添加
        if (m_esWidget)
        {
            q_ptr->ui->expansionSpaceContainer->addWidget(m_esWidget);
        }
        m_animationForES = new QPropertyAnimation(q_ptr->ui->expansionSpace, "maximumHeight", q_ptr);
        m_animationForES->setDuration(100);
        QObject::connect(q_ptr->ui->topBar, &TopBar::clickedBar, q_ptr, [this]() { changeExpansionState(); });

        adjustFixMaxExpansionHeight();
        q_ptr->ui->topBar->refreshFlagIcon(m_isExpanded);
    }

    void updateFixMaxExpansionHeight(int height)
    {
        if( height == m_fixMaxExpansionHeight )
            return;

        m_fixMaxExpansionHeight = height;
        adjustFixMaxExpansionHeight();
    }

    void adjustFixMaxExpansionHeight()
    {
        // 根据展开/折叠设置最大高度
        if (m_fixMaxExpansionHeight != -1)
        {
            q_ptr->ui->expansionSpace->setMaximumHeight(m_isExpanded ? m_fixMaxExpansionHeight : 0);
        }
        else
        {
            qInfo() << "update maximum height:" << q_ptr->ui->expansionSpace->sizeHint().height();
            q_ptr->ui->expansionSpace->setMaximumHeight(m_isExpanded ? q_ptr->ui->expansionSpace->sizeHint().height() : 0);
        }

    }

    void expand()
    {
        if (m_isExpanded || m_animationForES->state() == QAbstractAnimation::Running)
        {
            return;
        }
        m_animationForES->setEasingCurve(QEasingCurve::InCubic);
        m_animationForES->setStartValue(q_ptr->ui->expansionSpace->height());

        // 未设置最大高度，根据实际情况展开
        if (m_fixMaxExpansionHeight == -1)
        {
            m_animationForES->setEndValue(q_ptr->ui->expansionSpace->sizeHint().height());
        }
        else
        {
            m_animationForES->setEndValue(m_fixMaxExpansionHeight);
        }
        m_animationForES->start();

        m_isExpanded = true;
        q_ptr->ui->topBar->refreshFlagIcon(m_isExpanded);
        Q_EMIT q_ptr->expandSpaceExpanded();
    }

    void collapse()
    {
        if (!m_isExpanded || m_animationForES->state() == QAbstractAnimation::Running)
        {
            return;
        }
        m_animationForES->setEasingCurve(QEasingCurve::InCubic);
        m_animationForES->setStartValue(q_ptr->ui->expansionSpace->height());
        m_animationForES->setEndValue(0);
        m_animationForES->start();
        m_isExpanded = false;
        q_ptr->ui->topBar->refreshFlagIcon(m_isExpanded);
        Q_EMIT q_ptr->expandSpaceCollapsed();
    }

    void changeExpansionState()
    {
        if (m_isExpanded)
        {
            collapse();
        }
        else
        {
            expand();
        }
    }

    KiranCollapse* q_ptr;

    // 是否展开
    bool m_isExpanded = false;

    // 展开最大高度,为-1时，高度为内容高度
    int m_fixMaxExpansionHeight = -1;

    // 扩展区内边距 (默认12)
    int m_expansionMarginLeft = 12;
    int m_expansionMarginTop = 12;
    int m_expansionMarginRight = 12;
    int m_expansionMarginBottom = 12;

    // 外部圆角
    int m_radius = 6;
    bool m_drawBackground = true;

    // 扩展区展开搜索动画
    QPropertyAnimation* m_animationForES{};

    // 顶栏标题
    QString m_topBarTitle;
    
    // 扩展区控件
    QWidget* m_esWidget = nullptr;
};

// KiranCollapse实现
KiranCollapse::KiranCollapse(QWidget *parent)
    : QWidget(parent), d(new KiranCollapsePrivate(this)), ui(new Ui::KiranCollapse)
{
    ui->setupUi(this);
    d->init();
}

KiranCollapse::KiranCollapse(bool defaultIsExpand, const QString &title,
                             QWidget *expansionSpaceWidget, QWidget *parent)
    : QWidget(parent), d(new KiranCollapsePrivate(this)), ui(new Ui::KiranCollapse)
{
    ui->setupUi(this);
    d->m_isExpanded = defaultIsExpand;
    d->m_topBarTitle = title;
    d->m_esWidget = expansionSpaceWidget;
    d->init();
}

KiranCollapse::~KiranCollapse()
{
    delete d;
    delete ui;
}

void KiranCollapse::addExpansionSpaceWidget(QWidget *widget)
{
    ui->expansionSpaceContainer->addWidget(widget);
}

void KiranCollapse::delExpansionSpaceWidget(int index)
{
    if (ui->expansionSpaceContainer->count() == 0)
    {
        return;
    }
    
    auto item = ui->expansionSpaceContainer->takeAt(index);
    if (item)
    {
        QWidget *widget = item->widget();
        delete widget;
        delete item;
    }
}

void KiranCollapse::delExpansionSpaceWidget(const QString &widgetName)
{
    // 通过对象名称查找和删除指定的widget
    QList<QWidget *> widgetsToRemove = ui->expansionSpaceContainer->findChildren<QWidget *>(widgetName);
    for (QWidget *widget : widgetsToRemove)
    {
        delExpansionSpaceWidget(ui->expansionSpaceContainer->indexOf(widget));
    }
}

void KiranCollapse::delAllExpansionSpaceWidget()
{
    while (ui->expansionSpaceContainer->count() != 0)
    {
        QLayoutItem *item = ui->expansionSpaceContainer->takeAt(0);
        if (item)
        {
            delete item->widget();
            delete item;
        }
    }
}

bool KiranCollapse::event(QEvent *event)
{
    // 已展开，未设定固定最大展开高度
    // 收到LayoutRequest布局更新请求时，更新expansionSpace最大高度
    const bool isLayoutRequest = (event->type() == QEvent::LayoutRequest);
    const bool notSpecifyMaxHeight = (d->m_fixMaxExpansionHeight == -1);
    const bool inAnimation = (d->m_animationForES && d->m_animationForES->state() == QAbstractAnimation::Running);

    if (isLayoutRequest && d->m_isExpanded &&
        notSpecifyMaxHeight && !inAnimation)
    {
        d->adjustFixMaxExpansionHeight();
    }

    return QWidget::event(event);
}

void KiranCollapse::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    QStyle::State state;

    opt.initFrom(this);
    state = opt.state;

    QPainterPath painterPath;
    QRectF qRect = opt.rect;
    qRect.adjust(0.5, 0.5, -0.5, -0.5);
    painterPath.addRoundedRect(qRect, d->m_radius, d->m_radius);

    using namespace Kiran::Theme;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto kiranPalette = DEFAULT_PALETTE();
    state &= ~QStyle::State_MouseOver;

    if (d->m_drawBackground)
    {
        QColor backgroundColor;
        backgroundColor = kiranPalette->getColor(state, Palette::WIDGET);
        painter.fillPath(painterPath, backgroundColor);
    }

    QWidget::paintEvent(event);
}

bool KiranCollapse::getIsExpand() const
{
    return d->m_isExpanded;
}

void KiranCollapse::setIsExpand(bool isExpanded)
{
    d->m_isExpanded = isExpanded;
    d->adjustFixMaxExpansionHeight();
    ui->topBar->refreshFlagIcon(isExpanded);
}

void KiranCollapse::addTopBarWidget(QWidget *widget)
{
    ui->topBar->addWidget(widget);
}

void KiranCollapse::setTitle(const QString &title)
{
    ui->topBar->setTitle(title);
}

void KiranCollapse::setTopBarFixedHeight(int height)
{
    ui->topBar->setFixedHeight(height);
}

void KiranCollapse::setFixMaxExpansionHeight(int maxExpandHeight)
{
    d->updateFixMaxExpansionHeight(maxExpandHeight);
}

void KiranCollapse::setExpansionMargin(int left, int top, int right, int bottom)
{
    d->m_expansionMarginLeft = left;
    d->m_expansionMarginTop = top;
    d->m_expansionMarginRight = right;
    d->m_expansionMarginBottom = bottom;
    ui->expansionSpaceContainer->setContentsMargins(left, top, right, bottom);
}

QMargins KiranCollapse::expansionMargin()
{
    return QMargins(d->m_expansionMarginLeft,
                   d->m_expansionMarginTop,
                   d->m_expansionMarginRight,
                   d->m_expansionMarginBottom);
}

void KiranCollapse::setTopBarMargin(int left, int top, int right, int bottom)
{
    ui->topBar->setTopBarMargin(left, top, right, bottom);
}

void KiranCollapse::setTopBarSpacing(int spacing)
{
    ui->topBar->setTopBarSpacing(spacing);
}

void KiranCollapse::setExpand()
{
    d->expand();
}

void KiranCollapse::setCollapse()
{
    d->collapse();
}
