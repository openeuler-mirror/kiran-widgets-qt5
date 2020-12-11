//
// Created by lxh on 2020/11/27.
//

#include "draw-line-edit-helper.h"
#include "draw-common-helper.h"
#include "style-data/style-detail-fetcher.h"
#include "style.h"

#include <QRect>
#include <private/qcssparser_p.h>
#include <QWidget>

using namespace Kiran;

QSize DrawLineEditHelper::lineEditSizeFromContents(const Style* style,const QStyleOption *option,
                               const QSize &contentsSize, const QWidget *widget)
{
    // cast option and check
    const QStyleOptionFrame *frameOption(qstyleoption_cast<const QStyleOptionFrame *>(option));
    if (!frameOption) return contentsSize;

    int frameWidth(style->pixelMetric(QStyle::PM_DefaultFrameWidth, option, widget));

    bool isKiranSearchBox(widget->inherits("KiranSearchBox"));

    QSize size = DrawCommonHelper::expandSize(contentsSize,frameWidth);
    ///KiranSearchBox特殊处理，大小需加上高度，为画上搜索框图标
    if(isKiranSearchBox){
        size.rwidth()+=size.height();
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
    QRect contentsRect = rect.adjusted(frameWidth,frameWidth,-frameWidth,-frameWidth);

    //预留出搜索框绘制搜索图标
    if(isKiranSearchBox){
        contentsRect.adjust(rect.size().height(),0,0,0);
    }

    return contentsRect;
}
