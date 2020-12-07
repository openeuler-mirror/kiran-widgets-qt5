//
// Created by lxh on 2020/12/4.
//

#ifndef KIRANSTYLE_DRAW_SCROLL_BAR_HELPER_H
#define KIRANSTYLE_DRAW_SCROLL_BAR_HELPER_H

#include <QStyle>
#include <QRect>

///drawComplexControl
//  CC_ScrollBar
//
///drawControl
//	CE_ScrollBarAddLine
//	CE_ScrollBarSubLine
//	CE_ScrollBarAddPage empty
//	CE_ScrollBarSubPage empy
//	CE_ScrollBarSlider
//
//subControlRect
//	SC_ScrollBarSubLine empty
//	SC_ScrollBarAddLine empty
//	SC_ScrollBarGroove
//	SC_ScrollBarSlider
//	SC_ScrollBarSubPage
//	SC_ScrollBarAddPage

class QStyleOptionComplex;
class QPainter;
class QWidget;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    namespace DrawScrollBarHelper{
        bool drawScrollBarComplexControl(const Style* style,const QStyleOptionComplex* option,StyleDetailFetcher* fetcher,QPainter* painter,const QWidget* widget);
        QRect scrollBarSubControlRect(const Kiran::Style *style, const QStyleOptionComplex *opt,QStyle::SubControl subControl, const QWidget *w);
    }
}

#endif //KIRANSTYLE_DRAW_SCROLL_BAR_HELPER_H
