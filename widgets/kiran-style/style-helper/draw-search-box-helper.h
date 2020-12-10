//
// Created by lxh on 2020/12/9.
//

#ifndef KIRANWIDGETS_QT5_DRAW_SEARCH_BOX_HELPER_H
#define KIRANWIDGETS_QT5_DRAW_SEARCH_BOX_HELPER_H

class QStyleOption;
class QWidget;
class QPainter;
namespace Kiran {
    class Style;
    class StyleDetailFetcher;
    namespace DrawSearchBoxHelper {
        bool drawSearchBoxFramePrimitive(const Style *style, const QStyleOption *opt, QPainter *p,
                                         StyleDetailFetcher *fetcher, const QWidget *widget);

        bool drawSearchBoxIndicatorPrimitive(const Style *style, const QStyleOption *opt, QPainter *p,
                                             StyleDetailFetcher *fetcher, const QWidget *widget);
    };
}


#endif //KIRANWIDGETS_QT5_DRAW_SEARCH_BOX_HELPER_H
