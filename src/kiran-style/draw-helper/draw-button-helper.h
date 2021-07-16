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
 
#ifndef KIRANSTYLE_DRAW_BUTTON_HELPER_H
#define KIRANSTYLE_DRAW_BUTTON_HELPER_H

class QStyleOption;
class QWidget;
class QPainter;

namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制Button的相关方法
     */
    namespace DrawButtonHelper {
        /* pushbutton */
        bool drawPushButtonControl(const Style* style,const QStyleOption* opt,
                                   QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawPushButtonBevelControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawPushButtonLabelControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);

        /* toolbutton */
        bool drawToolButtonComplexControl(const Style* style,const QStyleOptionComplex* opt,
                                          StyleDetailFetcher* fetcher,QPainter *p,const QWidget* widget);
        bool drawToolButtonLabelControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawPanelButtonToolPrimitive(const Style* style , const QStyleOption* opt,
                                          QPainter* p, StyleDetailFetcher* fetcher, const QWidget* widget);

        /* checkbox,radiobutton */
        QSize checkBoxSizeFromContents(const Style *style, const QStyleOption *opt,
                                       const QSize &contentsSize,const QWidget *w,
                                       StyleDetailFetcher *detailFetcher);
        QRect checkBoxContentsRect(const Style* style,const QStyleOption* opt,const QWidget* w);
        bool drawCheckBoxLabelControl(const Style* style,const QStyleOption* opt,
                                      QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawIndicatorCheckBox(const Style* style,const QStyleOption* opt,
                                   QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawIndicatorRadioButton(const Style* style,const QStyleOption* opt,
                                      QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);

        /* switchbutton */
        QSize switchButtonSizeFromContents(const Style* style,const QStyleOption* opt,
                                           const QSize& contentSize,const QWidget*w);
        QRect switchButtonContetnsRect(const Style* style,const QStyleOption* opt,const QWidget* w);
        QRect switchButtonIndicatorRect(const Style* style,const QStyleOption* opt,const QWidget* w);
        bool drawSwitchButtonControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawSwitchButtonIndicatorPrimitive(const Style* style,const QStyleOption* opt,
                                                QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);
    };
}

#endif //KIRANSTYLE_DRAW_BUTTON_HELPER_H
