/**
 * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
 *
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http: //www.gnu.org/licenses/>.
 */

#include "kiran-tips.h"
#include <QBoxLayout>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QTimerEvent>
#include "kiran-tips-private.h"

/// tips离显示控件的间距
#define TIPS_SPACING 3
/// 背景矩形圆角
#define TIPS_RECT_RND 5
/// 布局margin
#define MARGIN 5
/// 三角形边长
#define TRIANGLE_SIDE_LENGTH 8

KiranTips::KiranTips(QWidget *parent)
    : QWidget(parent),
      d_ptr(new KiranTipsPrivate(this))
{
    d_ptr->init();
}

KiranTips::~KiranTips()
{
}

void KiranTips::setShowPosition(KiranTips::ShowPostionHint positionHint)
{
    if (d_ptr->m_showPostion == positionHint)
    {
        return;
    }

    d_ptr->m_showPostion = positionHint;
    d_ptr->updateContentsMargin();

    if (isVisible())
    {
        hide();
        showTipAroundWidget(d_ptr->m_showAroudWidget);
    }
}

void KiranTips::setText(const QString &text)
{
    d_ptr->m_labelText->setText(text);
}

void KiranTips::setHideTimeout(int ms)
{
    if (ms == 0 && d_ptr->m_fadeOutTimer.isActive())
    {
        d_ptr->m_fadeOutTimer.stop();
        d_ptr->m_fadeOutTimer.setInterval(0);
    }
    else if (d_ptr->m_fadeOutTimer.interval() != ms)
    {
        d_ptr->m_fadeOutTimer.setInterval(ms);
    }
}

void KiranTips::setHideOnClickedEnable(bool enable)
{
    if (d_ptr->m_hideOnClicked == enable)
    {
        return;
    }
    d_ptr->m_hideOnClicked = enable;
}

void KiranTips::showTipAroundWidget(QWidget *widget)
{
    Q_ASSERT(widget != nullptr);

    d_ptr->m_showAroudWidget = widget;

    if (isVisible())
    {
        setVisible(false);
    }

    if (d_ptr->m_animationEnable)
    {
        d_ptr->m_EnterAnimation->setEndValue(getRightSize());
        d_ptr->m_EnterAnimation->setDirection(QPropertyAnimation::Forward);
        d_ptr->m_EnterAnimation->stop();
        d_ptr->m_EnterAnimation->start();
    }
    else
    {
        resize(getRightSize());
    }

    this->raise();
    this->show();

    if (d_ptr->m_fadeOutTimer.interval() != 0)
    {
        d_ptr->m_fadeOutTimer.start();
    }
}

void KiranTips::setAnimationEnable(bool enable)
{
    if (d_ptr->m_animationEnable == enable)
    {
        return;
    }

    d_ptr->m_animationEnable = enable;
}

void KiranTips::setBackgroundColor(QColor color)
{
    if (d_ptr->m_bgColor == color)
    {
        return;
    }
    d_ptr->m_bgColor = color;
}

void KiranTips::hideTip()
{
    if (d_ptr->m_animationEnable)
    {
        d_ptr->m_EnterAnimation->setDirection(QPropertyAnimation::Backward);
        d_ptr->m_EnterAnimation->start();
    }
    else
    {
        hide();
    }
}

void KiranTips::drawUpArrowBackground(QPainter *painter)
{
    QPainterPath trianglesPath;
    ///三角形顶点X
    int vertexX = 10;
    trianglesPath.moveTo(vertexX, 0);
    trianglesPath.lineTo(vertexX - 4, TRIANGLE_SIDE_LENGTH);
    trianglesPath.lineTo(vertexX + 4, TRIANGLE_SIDE_LENGTH);
    trianglesPath.lineTo(vertexX, 0);
    painter->fillPath(trianglesPath, d_ptr->m_bgColor);

    QPainterPath rectPath;
    rectPath.addRoundedRect(0, TRIANGLE_SIDE_LENGTH,
                            width(), height() - TRIANGLE_SIDE_LENGTH,
                            TIPS_RECT_RND, TIPS_RECT_RND);
    painter->fillPath(rectPath, d_ptr->m_bgColor);
}

void KiranTips::drawDownArrowBackground(QPainter *painter)
{
    QPainterPath trianglesPath;
    ///三角形顶点X
    int vertexX = 10;
    trianglesPath.moveTo(vertexX, height());
    trianglesPath.lineTo(vertexX - TRIANGLE_SIDE_LENGTH / 2, height() - TRIANGLE_SIDE_LENGTH);
    trianglesPath.lineTo(vertexX + TRIANGLE_SIDE_LENGTH / 2, height() - TRIANGLE_SIDE_LENGTH);
    trianglesPath.lineTo(vertexX, height());
    painter->fillPath(trianglesPath, d_ptr->m_bgColor);

    QPainterPath rectPath;
    rectPath.addRoundedRect(0, 0,
                            width(), height() - TRIANGLE_SIDE_LENGTH,
                            TIPS_RECT_RND, TIPS_RECT_RND);
    painter->fillPath(rectPath, d_ptr->m_bgColor);
}

void KiranTips::drawLeftArrowBackground(QPainter *painter)
{
    QPainterPath trianglesPath;
    trianglesPath.moveTo(0, height() / 2);
    trianglesPath.lineTo(TRIANGLE_SIDE_LENGTH,
                         height() / 2 - TRIANGLE_SIDE_LENGTH / 2);
    trianglesPath.lineTo(TRIANGLE_SIDE_LENGTH,
                         height() / 2 + TRIANGLE_SIDE_LENGTH / 2);
    trianglesPath.lineTo(0, height() / 2);
    painter->fillPath(trianglesPath, d_ptr->m_bgColor);

    QPainterPath rectPath;
    rectPath.addRoundedRect(TRIANGLE_SIDE_LENGTH, 0,
                            width() - TRIANGLE_SIDE_LENGTH, height(),
                            TIPS_RECT_RND, TIPS_RECT_RND);
    painter->fillPath(rectPath, d_ptr->m_bgColor);
}

void KiranTips::drawRightArrowBackground(QPainter *painter)
{
    QPainterPath trianglesPath;
    trianglesPath.moveTo(width(), height() / 2);
    trianglesPath.lineTo(width() - TRIANGLE_SIDE_LENGTH, height() / 2 - TRIANGLE_SIDE_LENGTH / 2);
    trianglesPath.lineTo(width() - TRIANGLE_SIDE_LENGTH, height() / 2 + TRIANGLE_SIDE_LENGTH / 2);
    trianglesPath.lineTo(width(), height() / 2);
    painter->fillPath(trianglesPath, d_ptr->m_bgColor);

    QPainterPath rectPath;
    rectPath.addRoundedRect(0, 0, width() - TRIANGLE_SIDE_LENGTH, height(), TIPS_RECT_RND, TIPS_RECT_RND);
    painter->fillPath(rectPath, d_ptr->m_bgColor);
}

QSize KiranTips::getRightSize() const
{
    QFont font = d_ptr->m_labelText->font();
    QFontMetrics fontMetrics(font);
    QMargins layoutContentMargins = this->layout()->contentsMargins();

    d_ptr->m_labelText->setFixedWidth(fontMetrics.horizontalAdvance(d_ptr->m_labelText->text()) + 10);
    d_ptr->m_labelText->setFixedHeight(fontMetrics.height());

    QSize size;
    size.setWidth(d_ptr->m_labelText->width() + layoutContentMargins.left() + layoutContentMargins.right());
    size.setHeight(d_ptr->m_labelText->height() + layoutContentMargins.top() + layoutContentMargins.bottom());

    return size;
}

void KiranTips::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);

    QStyleOption option;
    option.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

    if (d_ptr->m_showPostion == POSITION_RIGHT)
    {
        drawLeftArrowBackground(&painter);
    }
    else if (d_ptr->m_showPostion == POSITION_LEFT)
    {
        drawRightArrowBackground(&painter);
    }
    else if (d_ptr->m_showPostion == POSITION_TOP)
    {
        drawDownArrowBackground(&painter);
    }
    else if (d_ptr->m_showPostion == POSITION_BOTTM)
    {
        drawUpArrowBackground(&painter);
    }
}

void KiranTips::mousePressEvent(QMouseEvent *event)
{
    this->hideTip();
    QWidget::mousePressEvent(event);
}

void KiranTips::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (d_ptr->m_showAroudWidget == nullptr)
    {
        return;
    }

    QPoint widgetLeftPoint = d_ptr->m_showAroudWidget->mapToGlobal(QPoint(0, 0));
    QSize widgetSize = d_ptr->m_showAroudWidget->size();
    int yCenter = widgetLeftPoint.y() + widgetSize.height() / 2;
    QPoint tipLeftTop;
    switch (d_ptr->m_showPostion)
    {
    case POSITION_LEFT:
        tipLeftTop.setX(widgetLeftPoint.x() - width() - TIPS_SPACING);
        tipLeftTop.setY(yCenter - (height() / 2));
        break;
    case POSITION_RIGHT:
        tipLeftTop.setX(widgetLeftPoint.x() + widgetSize.width() + TIPS_SPACING);
        tipLeftTop.setY(yCenter - (height() / 2));
        break;
    case POSITION_TOP:
        tipLeftTop.setX(widgetLeftPoint.x() + 5);
        tipLeftTop.setY(widgetLeftPoint.y() - height() - TIPS_SPACING);
        break;
    case POSITION_BOTTM:
        tipLeftTop.setX(widgetLeftPoint.x() + 5);
        tipLeftTop.setY(widgetLeftPoint.y() + widgetSize.height() + TIPS_SPACING);
        break;
    }
    tipLeftTop = parentWidget()->mapFromGlobal(tipLeftTop);
    this->move(tipLeftTop);
}

KiranTipsPrivate::KiranTipsPrivate(KiranTips *ptr)
    : QObject(ptr),
      q_ptr(ptr)
{
}

KiranTipsPrivate::~KiranTipsPrivate()
{
}

void KiranTipsPrivate::init()
{
    auto mainLayout = new QVBoxLayout(q_ptr);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(MARGIN, MARGIN, MARGIN + TRIANGLE_SIDE_LENGTH, MARGIN);

    m_labelText = new QLabel(q_ptr);
    m_labelText->setObjectName("label_text");
    m_labelText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_labelText->setAutoFillBackground(false);
    m_labelText->setAlignment(Qt::AlignCenter);
    m_labelText->setTextInteractionFlags(Qt::NoTextInteraction);

    mainLayout->addWidget(m_labelText);

    q_ptr->setAttribute(Qt::WA_TranslucentBackground);
    q_ptr->setAttribute(Qt::WA_AlwaysStackOnTop);
    q_ptr->setWindowFlag(Qt::FramelessWindowHint);
    m_labelText->setAttribute(Qt::WA_TranslucentBackground);

    // QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(q_ptr);
    // shadowEffect->setBlurRadius(7);
    // shadowEffect->setOffset(0, 0);
    // q_ptr->setGraphicsEffect(shadowEffect);

    m_fadeOutTimer.setSingleShot(true);

    m_EnterAnimation = new QPropertyAnimation(this);
    m_EnterAnimation->setTargetObject(q_ptr);
    m_EnterAnimation->setPropertyName("size");
    m_EnterAnimation->setStartValue(QSize(0, 0));
    m_EnterAnimation->setDuration(220);
    m_EnterAnimation->setEasingCurve(QEasingCurve::OutQuad);

    // clang-format off
    connect(&m_fadeOutTimer, &QTimer::timeout, [this](){ 
        q_ptr->hideTip();
    });
    connect(m_EnterAnimation, &QPropertyAnimation::finished, [this](){
        if (m_EnterAnimation->direction() == QPropertyAnimation::Backward)
        {
            q_ptr->setVisible(false);
        }
    });
    // clang-format on

    updateContentsMargin();
    q_ptr->setVisible(false);
    q_ptr->setHideTimeout(3000);
}

void KiranTipsPrivate::updateContentsMargin()
{
    QMargins margins(MARGIN, MARGIN, MARGIN, MARGIN);
    switch (m_showPostion)
    {
    case KiranTips::POSITION_LEFT:
        margins.setRight(MARGIN + TRIANGLE_SIDE_LENGTH);
        break;
    case KiranTips::POSITION_RIGHT:
        margins.setLeft(MARGIN + TRIANGLE_SIDE_LENGTH);
        break;
    case KiranTips::POSITION_TOP:
        margins.setBottom(MARGIN + TRIANGLE_SIDE_LENGTH);
        break;
    case KiranTips::POSITION_BOTTM:
        margins.setTop(MARGIN + TRIANGLE_SIDE_LENGTH);
        break;
    }
    q_ptr->layout()->setContentsMargins(margins);
}

bool KiranTipsPrivate::eventFilter(QObject *watched, QEvent *event)
{
    return QObject::eventFilter(watched, event);
}