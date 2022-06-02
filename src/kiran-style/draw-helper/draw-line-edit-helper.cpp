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
 
#include "draw-line-edit-helper.h"
#include "draw-common-helper.h"
#include "style-detail-fetcher.h"
#include "style.h"
#include "kiran-style-private-defines.h"
#include "widget-private-property-helper.h"

#include <QRect>
#include <private/qcssparser_p.h>
#include <QWidget>
#include <QDebug>
#include <QLineEdit>

using namespace Kiran;

QSize
DrawLineEditHelper::lineEditSizeFromContents(const Style *style, const QStyleOption *option, const QSize &contentsSize,
                                             const QWidget *widget, StyleDetailFetcher *detailFetcher)
{
    // cast option and check
    const QStyleOptionFrame *frameOption(qstyleoption_cast<const QStyleOptionFrame *>(option));
    if (!frameOption) return contentsSize;

    int frameWidth(style->pixelMetric(QStyle::PM_DefaultFrameWidth, option, widget));

    bool isKiranSearchBox(widget->inherits("KiranSearchBox"));
    bool isKiranIconLineEdit(widget->inherits("KiranIconLineEdit"));
    bool flat(frameOption->lineWidth == 0);
    QSize size = contentsSize;
    if( !flat ){
        size = DrawCommonHelper::expandSize(size,frameWidth);
    }
    ///KiranSearchBox特殊处理，大小需加上高度，为画上搜索框图标
    if(isKiranSearchBox){
        size.rwidth()+=size.height();
    }
    if(isKiranIconLineEdit){
        const QLineEdit* lineEdit = qobject_cast<const QLineEdit*>(widget);
        QSize iconSize = WidgetPrivatePropertyHelper::getLineEditIconSize(lineEdit);
        IconLineEditIconPosition position = WidgetPrivatePropertyHelper::getLineEditIconPosition(lineEdit);
        if( iconSize.isValid() && position!=ICON_POSITION_NONE ){
            size.rwidth()+=iconSize.width();
        }
    }
    return size;
}

bool DrawLineEditHelper::drawFrameLineEditPrimitive(const Style *style,const QStyleOption *opt, QPainter *painter,
                                                    StyleDetailFetcher *detaulFetcher,const QWidget *widget)
{
    const QRect &rect = opt->rect;

    bool enabled = (opt->state & QStyle::State_Enabled);
    bool hasFocus = (opt->state & QStyle::State_HasFocus);

    if( widget && widget->parentWidget() && widget->parentWidget()->inherits("KiranSearchBox") ){
        return true;
    }

    ///NOTE:由于输入框聚焦会有Sunken状态会导致去匹配pressed的样式，所以需要指定特殊的伪选择器
    quint64 specialPseudo = hasFocus ? QCss::PseudoClass_Focus : 0;

    QColor background = detaulFetcher->getColor(widget, opt, StyleDetailFetcher::Frame_Background, specialPseudo);
    QColor border = detaulFetcher->getColor(widget, opt, StyleDetailFetcher::Frame_BorderColor, specialPseudo);
    int borderWidth = detaulFetcher->getInt(widget, opt, StyleDetailFetcher::Frame_BorderWidth, specialPseudo);
    int radius = detaulFetcher->getInt(widget, opt , StyleDetailFetcher::Frame_Radius, specialPseudo);

    DrawCommonHelper::drawFrame(painter, rect,
                                radius, borderWidth,
                                background, border);

    return true;
}

QRect DrawLineEditHelper::lineEditContentsRect(const Style *style, const QStyleOption *opt, const QWidget *widget)
{
    QRect rect(opt->rect);
    const auto frameOption(qstyleoption_cast<const QStyleOptionFrame *>(opt));
    if (!frameOption) {
        return opt->rect;
    }

    int frameWidth(style->pixelMetric(QStyle::PM_DefaultFrameWidth, opt, widget));
    bool isKiranSearchBox(widget->inherits("KiranSearchBox"));
    bool isKiranIconLineEdit(widget->inherits("KiranIconLineEdit"));

    QRect contentsRect = rect.adjusted(frameWidth,frameWidth,-frameWidth,-frameWidth);

    if(isKiranSearchBox){/* 预留出搜索框绘制搜索图标 */
        contentsRect.adjust(rect.size().height(),0,0,0);
    }else if(isKiranIconLineEdit){/* 带有图标的QLineEdit预留出图标位置 */
        const QLineEdit* lineEdit = qobject_cast<const QLineEdit*>(widget);
        QSize iconSize = WidgetPrivatePropertyHelper::getLineEditIconSize(lineEdit);
        IconLineEditIconPosition position = WidgetPrivatePropertyHelper::getLineEditIconPosition(lineEdit);
        if( !iconSize.isNull() ){
            switch (position) {
                case ICON_POSITION_NONE:
                    break;
                case ICON_POSITION_LEFT:
                    contentsRect.adjust(iconSize.width(),0,0,0);
                    break;
                case ICON_POSITION_RIGHT:
                    contentsRect.adjust(0,0,-iconSize.width(),0);
                    break;
            }
        }
    }

    return contentsRect;
}
