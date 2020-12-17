/*
 * @file   draw-line-edit-helper.h
 * @brief  输入框绘制
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H
#define KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H

#include <QRect>

class QStyle;
class QStyleOption;
class QPainter;
class QWidget;
class QStyleOptionFrame;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制输入框的相关方法
     */
    namespace DrawLineEditHelper {
        QSize lineEditSizeFromContents(const Style *style, const QStyleOption *option, const QSize &contentsSize,
                                       const QWidget *widget, StyleDetailFetcher *detailFetcher);
        QRect lineEditContentsRect(const Style* style,const QStyleOption* opt,const QWidget* widget);
        bool drawFrameLineEditPrimitive(const Style* style ,const QStyleOption* opt,QPainter* painter,
                                        StyleDetailFetcher* detaulFetcher,const QWidget* widget);
    };
}

#endif //KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H
