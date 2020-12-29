//
// Created by lxh on 2020/11/27.
//
#include "draw-frame-helper.h"
#include "draw-common-helper.h"
#include "style.h"

#include <QStyle>
#include <QDebug>

using namespace Kiran;

bool DrawFrameHelper::drawFramePrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                                StyleDetailFetcher *detaulFetcher, const QWidget *widget)
{
    if( widget->inherits("QScrollArea") ){
        return true;
    }

    const QRect &rect(opt->rect);
    const QStyle::State &state(opt->state);
    bool enabled(state & QStyle::State_Enabled);
    bool hasFocus(state & QStyle::State_HasFocus);

    if (!(state & (QStyle::State_Sunken | QStyle::State_Raised))) {
        return true;
    }

    ///NOTE:由于Frame聚焦会有Sunken状态会导致匹配Pressed样式，需指定特殊伪选择器
    quint64 specialPseudo = hasFocus ? QCss::PseudoClass_Focus : 0;

    QColor background = detaulFetcher->getColor(widget, opt, StyleDetailFetcher::Frame_Background, specialPseudo);
    QColor border = detaulFetcher->getColor(widget, opt, StyleDetailFetcher::Frame_BorderColor, specialPseudo);
    int borderWidth = detaulFetcher->getInt(widget, opt, StyleDetailFetcher::Frame_BorderWidth, specialPseudo);
    int radius = detaulFetcher->getInt(widget, opt, StyleDetailFetcher::Frame_Radius, specialPseudo);

    DrawCommonHelper::drawFrame(painter, rect,
                                radius,
                                borderWidth,
                                background, border);

    return true;
}
