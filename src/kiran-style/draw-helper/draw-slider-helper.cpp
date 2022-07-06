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
 
#include "draw-slider-helper.h"
#include "draw-common-helper.h"
#include "kiran-style-private-defines.h"
#include "style.h"

#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>
#include <QPainterPath>

bool Kiran::DrawSliderHelper::drawSliderComplexControl(const Kiran::Style *       style,
                                                       const QStyleOptionComplex *opt,
                                                       Kiran::StyleDetailFetcher *fetcher,
                                                       QPainter *                 painter,
                                                       const QWidget *            widget)
{
    const QStyleOptionSlider *optionSlider(qstyleoption_cast<const QStyleOptionSlider *>(opt));
    if (!optionSlider)
    {
        return true;
    }

    const QRect &        rect(opt->rect);
    const QStyle::State &state(opt->state);
    bool                 enabled(state & QStyle::State_Enabled);
    bool                 windowActive(state & QStyle::State_Active);
    bool                 mouseOver((state & QStyle::State_Active) && enabled && (state & QStyle::State_MouseOver));
    bool                 hasFocus(enabled && (state & QStyle::State_HasFocus));
    bool                 horizontal(optionSlider->orientation == Qt::Horizontal);
    ///NOTE:通常滑块在向上(垂直滑块条)或向右(水平滑块条)移动时增加,upsideDown标志是不是和上面的逻辑相反，即向下或向左移动时为增加
    bool upsideDown(optionSlider->upsideDown);
    Side tickSide{SideNone};

    if (horizontal && optionSlider->tickPosition == QSlider::TicksAbove) tickSide = (Side)((int)tickSide | (int)SideTop);
    if (horizontal && optionSlider->tickPosition == QSlider::TicksBelow) tickSide = (Side)((int)tickSide | (int)SideBottom);
    if (!horizontal && optionSlider->tickPosition == QSlider::TicksLeft) tickSide = (Side)((int)tickSide | (int)SideLeft);
    if (!horizontal && optionSlider->tickPosition == QSlider::TicksRight) tickSide = (Side)((int)tickSide | (int)SideRight);

    ///绘制TickMark标尺
    if ((optionSlider->subControls & QStyle::SC_SliderTickmarks) && (Metrics::Slider_DrawTickMark))
    {
        int tickPosition(optionSlider->tickPosition);
        int available(style->pixelMetric(QStyle::PM_SliderSpaceAvailable, opt, widget));
        int interval = optionSlider->tickInterval;
        if (interval < 1) interval = optionSlider->pageStep;
        if (interval >= 1)
        {
            int          sliderLength = style->pixelMetric(QStyle::PM_SliderLength, opt, widget);
            QRect        grooveRect   = style->subControlRect(QStyle::CC_Slider, optionSlider, QStyle::SC_SliderGroove, widget);
            QList<QLine> tickLines;

            //根据Orientation(控件方向 垂直/水平)和TickPosition(tickmark相对滑动槽位置绘制位置)，生成tickmark绘制的位置
            if (horizontal)
            {
                if (tickPosition & QSlider::TicksAbove)
                {
                    ///添加tickMark line位于水平滑动槽的上方
                    auto line = QLine(rect.left(),
                                      grooveRect.top() - Metrics::Slider_TickMarginWidth,
                                      rect.left(),
                                      grooveRect.top() - Metrics::Slider_TickMarginWidth - Metrics::Slider_TickLength);
                    tickLines.append(line);
                }
                if (tickPosition & QSlider::TicksBelow)
                {
                    /////添加tickMark line位于水平滑动槽的下方
                    auto line = QLine(rect.left(),
                                      grooveRect.bottom() + Metrics::Slider_TickMarginWidth,
                                      rect.left(),
                                      grooveRect.bottom() + Metrics::Slider_TickMarginWidth + Metrics::Slider_TickLength);
                    tickLines.append(line);
                }
            }
            else
            {
                if (tickPosition & QSlider::TicksAbove)
                {
                    /////添加tickMark line位于垂直滑动槽的左边
                    auto line = QLine(grooveRect.left() - Metrics::Slider_TickMarginWidth,
                                      rect.top(),
                                      grooveRect.left() - Metrics::Slider_TickMarginWidth - Metrics::Slider_TickLength,
                                      rect.top());
                    tickLines.append(line);
                }
                if (tickPosition & QSlider::TicksBelow)
                {
                    /////添加tickMark line位于垂直滑动槽的右边
                    auto line = QLine(grooveRect.right() + Metrics::Slider_TickMarginWidth,
                                      rect.top(),
                                      grooveRect.right() + Metrics::Slider_TickMarginWidth + Metrics::Slider_TickLength,
                                      rect.top());
                    tickLines.append(line);
                }
            }

            int currentTickMark = optionSlider->minimum;
            while (currentTickMark <= optionSlider->maximum)
            {
                // NOTE:暂时不提供tickmark颜色变化
                // QColor color( (enabled && currentTickMark <= optionSlider->sliderPosition) ? "blue":"white" );
                QColor tickMarkColor = fetcher->getColor(widget, opt, StyleDetailFetcher::Slider_TickMarkColor);

                painter->setPen(tickMarkColor);
                ///NOTE:为什么计算TickMarkLine Position时需要加上 PM_SliderLength/2 ???
                int position(QStyle::sliderPositionFromValue(optionSlider->minimum, optionSlider->maximum, currentTickMark, available) + (sliderLength / 2));
                foreach (const QLine &tickLine, tickLines)
                {
                    ///水平滑块条 对TickMarkLine进行X轴平移,垂直滑块条 对TickMarkLine进行Y轴平移
                    if (horizontal)
                        painter->drawLine(tickLine.translated(upsideDown ? (rect.width() - position) : position, 0));
                    else
                        painter->drawLine(tickLine.translated(0, upsideDown ? (rect.height() - position) : position));
                }
                currentTickMark += interval;
            }
        }
    }

    ///绘制滑块条滑动槽
    if (optionSlider->subControls & QStyle::SC_SliderGroove)
    {
        if (hasFocus)
        {
            QRect                 focusRect = style->baseStyle()->subElementRect(QStyle::SE_SliderFocusRect, opt, widget);
            QStyleOptionFocusRect fropt;
            fropt.QStyleOption::  operator=(*opt);
            fropt.rect                    = focusRect;
            style->drawPrimitive(QStyle::PE_FrameFocusRect, &fropt, painter, widget);
        }

        QColor highlightColor = fetcher->getColor(widget, opt, StyleDetailFetcher::Slider_GrooveHighlightColor);
        QColor normalColor    = fetcher->getColor(widget, opt, StyleDetailFetcher::Slider_GrooveNormalColor);

        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        QRect grooveRect = style->subControlRect(QStyle::CC_Slider, opt, QStyle::SC_SliderGroove, widget);
        qreal percent    = ((qreal)(optionSlider->sliderPosition - optionSlider->minimum)) / (optionSlider->maximum - optionSlider->minimum);

        QRect hightlightRect, normalRect;
        hightlightRect = normalRect = grooveRect;

        if (horizontal)
        {
            if (upsideDown)
            {
                hightlightRect.setLeft(grooveRect.right() - (grooveRect.width() * percent));
                normalRect.setRight(hightlightRect.left());
            }
            else
            {
                hightlightRect.setRight(grooveRect.left() + (grooveRect.width() * percent));
                normalRect.setLeft(hightlightRect.right());
            }
        }
        else
        {
            if (upsideDown)
            {
                hightlightRect.setBottom(grooveRect.bottom() - (grooveRect.height() * percent));
                normalRect.setTop(hightlightRect.bottom());
            }
            else
            {
                hightlightRect.setTop(grooveRect.bottom() + (grooveRect.height() * percent));
                normalRect.setBottom(hightlightRect.top());
            }
        }
        painter->fillRect(hightlightRect, QColor(highlightColor));
        painter->fillRect(normalRect, QColor(normalColor));
    }

    ///绘制滑动条手柄
    if (optionSlider->subControls & QStyle::SC_SliderHandle)
    {
        QColor backgroundColor = fetcher->getColor(widget, opt, StyleDetailFetcher::Slider_HandleBackgroundColor);
        QColor borderColor     = fetcher->getColor(widget, opt, StyleDetailFetcher::Slider_HandleBorderColor);

        QRect handleRect = style->subControlRect(QStyle::CC_Slider, opt, QStyle::SC_SliderHandle, widget);
        QPainterPath fillPath, borderPath;
        fillPath.addEllipse(handleRect);
        borderPath.addEllipse(handleRect.adjusted(1, 1, -1, -1));

        painter->fillPath(fillPath, QColor(backgroundColor));

        QPen pen = painter->pen();
        pen.setColor(borderColor);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawPath(borderPath);
    }

    return true;
}

QSize Kiran::DrawSliderHelper::sliderSizeFromContent(const Kiran::Style *       style,
                                                     const QStyleOption *       opt,
                                                     const QSize &              contentsSize,
                                                     const QWidget *            w,
                                                     Kiran::StyleDetailFetcher *fetcher)
{
    // cast option and check
    const QStyleOptionSlider *sliderOption(qstyleoption_cast<const QStyleOptionSlider *>(opt));
    if (!sliderOption) return contentsSize;

    // store tick position and orientation
    const QSlider::TickPosition &tickPosition(sliderOption->tickPosition);
    bool                         horizontal(sliderOption->orientation == Qt::Horizontal);
    bool                         disableTicks(!Metrics::Slider_DrawTickMark);

    // do nothing if no ticks are requested
    if (tickPosition == QSlider::NoTicks) return contentsSize;

    /*
     * Qt adds its own tick length directly inside QSlider.
     * Take it out and replace by ours, if needed
     */
    const int tickLength(disableTicks ? 0 : (Metrics::Slider_TickLength + Metrics::Slider_TickMarginWidth + (Metrics::Slider_GrooveThickness - Metrics::Slider_ControlThickness) / 2));

    int builtInTickLength(5);

    QSize size(contentsSize);
    if (horizontal)
    {
        if (tickPosition & QSlider::TicksAbove) size.rheight() += tickLength - builtInTickLength;
        if (tickPosition & QSlider::TicksBelow) size.rheight() += tickLength - builtInTickLength;
    }
    else
    {
        if (tickPosition & QSlider::TicksAbove) size.rwidth() += tickLength - builtInTickLength;
        if (tickPosition & QSlider::TicksBelow) size.rwidth() += tickLength - builtInTickLength;
    }

    return size;
}

QRect Kiran::DrawSliderHelper::sliderSubControlRect(const Kiran::Style *       style,
                                                    const QStyleOptionComplex *opt,
                                                    QStyle::SubControl         subControl,
                                                    const QWidget *            w)
{
    const QStyleOptionSlider *sliderOption(qstyleoption_cast<const QStyleOptionSlider *>(opt));
    if (!sliderOption) return QRect();

    bool isHor(sliderOption->orientation == Qt::Horizontal);
    switch (subControl)
    {
    case QStyle::SC_SliderGroove:
    {
        QRect grooveRect = style->baseStyle()->subControlRect(QStyle::CC_Slider, opt, subControl, w);

        ///内容窗口边距距离PM_DefaultFrameWidth
        grooveRect = DrawCommonHelper::insideMargin(grooveRect, style->pixelMetric(QStyle::PM_DefaultFrameWidth, opt, w));

        //滑动槽厚度
        int grooveThickness = Metrics::Slider_GrooveThickness;

        //居中滑动槽绘制区域
        if (isHor)
        {
            grooveRect = DrawCommonHelper::centerRect(grooveRect, grooveRect.width(), Metrics::Slider_GrooveThickness);
        }
        else
        {
            grooveRect = DrawCommonHelper::centerRect(grooveRect, Metrics::Slider_GrooveThickness, grooveRect.height());
        }

        return grooveRect;
    }
    case QStyle::SC_SliderHandle:
    {
        QRect handleRect = style->baseStyle()->subControlRect(QStyle::CC_Slider,opt,QStyle::SC_SliderHandle,w);
        int   tickSize = style->pixelMetric(QStyle::PM_SliderTickmarkOffset, opt, w);

        if (sliderOption->orientation == Qt::Horizontal)
        {
            handleRect.setHeight(style->pixelMetric(QStyle::PM_SliderControlThickness));
            handleRect.setWidth(style->pixelMetric(QStyle::PM_SliderLength));
            int centerY = sliderOption->rect.center().y() - handleRect.height() / 2;
            if (sliderOption->tickPosition & QSlider::TicksAbove)
                centerY += tickSize;
            if (sliderOption->tickPosition & QSlider::TicksBelow)
                centerY -= tickSize;
            handleRect.moveTop(centerY);
        }
        else
        {
            handleRect.setWidth(style->pixelMetric(QStyle::PM_SliderThickness));
            handleRect.setHeight(style->pixelMetric(QStyle::PM_SliderLength));
            int centerX = sliderOption->rect.center().x() - handleRect.width() / 2;
            if (sliderOption->tickPosition & QSlider::TicksAbove)
                centerX += tickSize;
            if (sliderOption->tickPosition & QSlider::TicksBelow)
                centerX -= tickSize;
            handleRect.moveLeft(centerX);
        }
        return handleRect;
    }
    default:
        return style->baseStyle()->subControlRect(QStyle::CC_Slider, opt, subControl, w);
    }
    return QRect();
}
