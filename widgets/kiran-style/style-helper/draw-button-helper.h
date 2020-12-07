//
// Created by lxh on 2020/11/27.
//

#ifndef KIRANSTYLE_DRAW_BUTTON_HELPER_H
#define KIRANSTYLE_DRAW_BUTTON_HELPER_H

class QStyleOption;
class QWidget;
class QPainter;

namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    namespace DrawButtonHelper {
        ///pushbutton
        bool drawPushButtonControl(const Style* style,const QStyleOption* opt,
                                   QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawPushButtonBevelControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawPushButtonLabelControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);

        ///toolbutton
        bool drawToolButtonComplexControl(const Style* style,const QStyleOptionComplex* opt,
                                          StyleDetailFetcher* fetcher,QPainter *p,const QWidget* widget);
        bool drawToolButtonLabelControl(const Style* style,const QStyleOption* opt,
                                        QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawPanelButtonToolPrimitive(const Style* style , const QStyleOption* opt,
                                          QPainter* p, StyleDetailFetcher* fetcher, const QWidget* widget);

        ///checkbox,radiobutton
        QSize checkBoxSizeFromContents(const Style*  style,const QStyleOption* opt,
                                       const QSize& contentsSize, const QWidget*w);
        QRect checkBoxContentsRect(const Style* style,const QStyleOption* opt,const QWidget* w);
        bool drawCheckBoxLabelControl(const Style* style,const QStyleOption* opt,
                                      QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawIndicatorCheckBox(const Style* style,const QStyleOption* opt,
                                   QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawIndicatorRadioButton(const Style* style,const QStyleOption* opt,
                                      QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);

        ///switchbutton
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
