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

    ///NOTE:由于Frame聚焦会有Sunken状态会导致匹配Pressed样式，需指定特殊伪选择器
    quint64 specialPseudo = hasFocus ? QCss::PseudoClass_Focus : 0;

    QColor backgroundColor,borderColor;
    int borderWidth,radius;

    backgroundColor = detaulFetcher->getColor(widget, opt, StyleDetailFetcher::Frame_Background, specialPseudo);
    borderColor = detaulFetcher->getColor(widget, opt, StyleDetailFetcher::Frame_BorderColor, specialPseudo);
    borderWidth = detaulFetcher->getInt(widget, opt, StyleDetailFetcher::Frame_BorderWidth, specialPseudo);
    radius = detaulFetcher->getInt(widget, opt, StyleDetailFetcher::Frame_Radius, specialPseudo);

    DrawCommonHelper::drawFrame(painter, rect,
                                radius,
                                borderWidth,
                                backgroundColor, borderColor);

    return true;
}
bool DrawFrameHelper::drawFrameFocusRectPrimitive(const Style *style,
                                                  const QStyleOption *opt,
                                                  QPainter *painter,
                                                  StyleDetailFetcher *detaulFetcher,
                                                  const QWidget *widget)
{
    const QStyle::State& state( opt->state );
    QRectF rect( QRectF(opt->rect).adjusted( 0, 0, -1, -1 ) );
    const QPalette& palette( opt->palette );

    if( rect.width() < 10 ) return true;

    QColor outlineColor = detaulFetcher->getColor(widget,opt,StyleDetailFetcher::FocusRect_BorderColor);

    QPen pen(outlineColor, 1);
//    pen.setStyle( Qt::CustomDashLine );
//    pen.setDashPattern(QVector<qreal>() << 2 << 1);
    pen.setStyle(Qt::DashLine);

    painter->setRenderHint( QPainter::Antialiasing, false );

    painter->setPen( pen );
    painter->drawRoundedRect( rect, 2, 2 );

    return true;

}
