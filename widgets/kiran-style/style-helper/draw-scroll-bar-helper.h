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

        ///drawComplexControl - CC_ScrollBar
        bool drawScrollBarComplexControl(const Style* style,const QStyleOptionComplex* option,
                                         StyleDetailFetcher* fetcher,QPainter* painter,
                                         const QWidget* widget);

        //drawControl - CE_ScrollBarAddLine
        bool drawScrollBarAddLineControl(const Style *style, const QStyleOption *opt,QPainter *p,StyleDetailFetcher *fetcher,const QWidget *widget);

        //drawControl - CE_ScrollBarSubLine
        bool drawScrollBarSubLineControl(const Style *style, const QStyleOption *opt,QPainter *p,StyleDetailFetcher *fetcher,const QWidget *widget);

        //drawControl - CE_ScrollBarAddPage
        bool drawScrollBarAddPageControl(const Style *style, const QStyleOption *opt,QPainter *p,StyleDetailFetcher *fetcher,const QWidget *widget);

        //drawControl - CE_ScrollBarSubPage
        bool drawScrollBarSubPageControl(const Style *style, const QStyleOption *opt,QPainter *p,StyleDetailFetcher *fetcher,const QWidget *widget);

        //drawControl - CE_ScrollBarSlider
        bool drawScrollBarSliderControl(const Style *style, const QStyleOption *opt,QPainter *p,StyleDetailFetcher *fetcher,const QWidget *widget);

        //subControlRect
        //	    - SC_ScrollBarSubLine
        //	    - SC_ScrollBarAddLine
        //	    - SC_ScrollBarGroove
        //	    - SC_ScrollBarSlider
        //	    - SC_ScrollBarSubPage
        //	    - SC_ScrollBarAddPage
        QRect scrollBarSubControlRect(const Kiran::Style *style, const QStyleOptionComplex *opt,QStyle::SubControl subControl, const QWidget *w);

        ///drawPrimitive - drawScrollAreaCornerPrimitive ScrollArea 绘制垂直滚动条和水平滚动条都显示时的角落
        bool drawScrollAreaCornerPrimitive(const Style *style,const QStyleOption* option, QPainter * painter, StyleDetailFetcher * fetcher, const QWidget *w);

        //ScrollBar通过改方法获取点击到的控件
        QStyle::SubControl hitTestScrollBarComplexControl(const Style* style,const QStyleOptionComplex *opt,
                                                          const QPoint &pt,const QWidget *w);
    }
}

#endif //KIRANSTYLE_DRAW_SCROLL_BAR_HELPER_H
