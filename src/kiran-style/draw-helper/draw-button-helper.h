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
