//
// Created by lxh on 2021/4/6.
//

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
