//
// Created by lxh on 2020/11/27.
//

#ifndef KIRANSTYLE_DRAW_SPINBOX_HELPER_H
#define KIRANSTYLE_DRAW_SPINBOX_HELPER_H

#include <QStyle>

class QStyleOptionComplex;
class QPainter;
class QWidget;

namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    namespace DrawSpinboxHelper {
        QRect spinBoxSubControlRect(const Style*style,const QStyleOptionComplex* opt,
                                    QStyle::SubControl subControl,const QWidget* w);

        bool drawSpinBoxCompleControl(const Style* style,const QStyleOptionComplex *opt,
                                      StyleDetailFetcher* fetcher, QPainter *painter, const QWidget *widget);
    };
}


#endif //KIRANSTYLE_DRAW_SPINBOX_HELPER_H
