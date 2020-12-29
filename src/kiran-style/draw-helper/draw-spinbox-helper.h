/*
 * @file   draw-spinbox-helper.h
 * @brief  绘制SpinBox
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANSTYLE_DRAW_SPINBOX_HELPER_H
#define KIRANSTYLE_DRAW_SPINBOX_HELPER_H

#include <QStyle>

class QStyleOptionComplex;
class QPainter;
class QWidget;

namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制SpinBox的相关方法
     */
    namespace DrawSpinboxHelper {
        QRect spinBoxSubControlRect(const Style*style,const QStyleOptionComplex* opt,
                                    QStyle::SubControl subControl,const QWidget* w);

        bool drawSpinBoxCompleControl(const Style* style,const QStyleOptionComplex *opt,
                                      StyleDetailFetcher* fetcher, QPainter *painter, const QWidget *widget);
    };
}


#endif //KIRANSTYLE_DRAW_SPINBOX_HELPER_H
