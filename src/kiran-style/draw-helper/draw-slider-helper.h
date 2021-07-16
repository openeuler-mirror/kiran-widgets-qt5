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
 
#ifndef KIRANWIDGETS_QT5_SRC_KIRAN_STYLE_DRAW_HELPER_DRAW_SLIDER_HELPER_H_
#define KIRANWIDGETS_QT5_SRC_KIRAN_STYLE_DRAW_HELPER_DRAW_SLIDER_HELPER_H_

#include <QStyle>

namespace Kiran
{
class Style;
class StyleDetailFetcher;
namespace DrawSliderHelper
{
bool  drawSliderComplexControl(const Style *style, const QStyleOptionComplex *opt,
                               StyleDetailFetcher *fetcher, QPainter *painter, const QWidget *widget);
QSize sliderSizeFromContent(const Style *style, const QStyleOption *opt,
                            const QSize &contentsSize, const QWidget *w,
                            StyleDetailFetcher *fetcher);
QRect sliderSubControlRect(const Kiran::Style *style, const QStyleOptionComplex *opt,
                           QStyle::SubControl subControl, const QWidget *w);
}  // namespace DrawSliderHelper
}  // namespace Kiran

#endif  //KIRANWIDGETS_QT5_SRC_KIRAN_STYLE_DRAW_HELPER_DRAW_SLIDER_HELPER_H_
