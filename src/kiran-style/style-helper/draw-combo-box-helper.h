//
// Created by lxh on 2020/11/30.
//

#ifndef KIRANSTYLE_DRAW_COMBO_BOX_HELPER_H
#define KIRANSTYLE_DRAW_COMBO_BOX_HELPER_H

#include <QStyle>

class QStyleOptionComplex;
class QPainter;
class QWidget;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    namespace DrawComboBoxHelper{
        bool drawComboBoxComplexControl(const Style* style, const QStyleOptionComplex* opt,StyleDetailFetcher* fetcher, QPainter* p, const QWidget* w);
        bool drawComboBoxMenuItem(const Style *style, const QStyleOption *opt,QPainter *p, StyleDetailFetcher *fetcher, const QWidget *widget);
        QRect comboBoxSubControlRect(const Style *style,const QStyleOptionComplex *opt, QStyle::SubControl subControl,const QWidget *w);
    }
}


#endif //KIRANSTYLE_DRAW_COMBO_BOX_HELPER_H
