/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
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
