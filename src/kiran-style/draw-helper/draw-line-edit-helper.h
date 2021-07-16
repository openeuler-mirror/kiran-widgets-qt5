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
