/*
 * @file   draw-search-box-helper.h
 * @brief  绘制搜索框
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANWIDGETS_QT5_DRAW_SEARCH_BOX_HELPER_H
#define KIRANWIDGETS_QT5_DRAW_SEARCH_BOX_HELPER_H

class QStyleOption;
class QWidget;
class QPainter;
namespace Kiran {
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制搜索框的相关方法
     */
    namespace DrawSearchBoxHelper {
        bool drawSearchBoxIndicatorPrimitive(const Style *style, const QStyleOption *opt, QPainter *p,
                                             StyleDetailFetcher *fetcher, const QWidget *widget);
    };
}


#endif //KIRANWIDGETS_QT5_DRAW_SEARCH_BOX_HELPER_H
