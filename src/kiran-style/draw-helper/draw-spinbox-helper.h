 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
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
