//
// Created by lxh on 2020/11/19.
//

#ifndef KIRANSTYLE_DRAW_COMMON_HELPER_H
#define KIRANSTYLE_DRAW_COMMON_HELPER_H

#include <QPainter>
#include <QStyle>
#include <QSpinBox>
#include <QStyle>

#include "kiran-private-defines.h"

namespace Kiran {
    class Style;

    class StyleDetailFetcher;
    namespace DrawCommonHelper {

        bool isCompositingManagerRuning();

        QRect centerRect(const QRect &rect, int width, int height);

        QRect centerRect(const QRect &rect, const QSize &size);

        //* adjust rect based on provided margins
        QRect insideMargin(const QRect &r, int margin);

        //* adjust rect based on provided margins
        QRect insideMargin(const QRect &r, int marginWidth, int marginHeight);

        //* expand size based on margins
        QSize expandSize(const QSize &size, int margin);

        //* expand size based on margins
        QSize expandSize(const QSize &size, int marginWidth, int marginHeight);

        QPainterPath getRoundedRectanglePath(const QRect &rect, int tlRadius,
                                             int trRadius, int blRadius, int brRadius);

        void drawFrame(QPainter *painter, const QRect &rect, int radius,
                       int outlineWidth, const QColor &bgColor, const QColor &outline);

        void drawSpinboxArrow(QPainter *painter, const QRect &rect, const QRect &spinboxRect,
                              int spinboxRadius, QColor bgColor, QColor signColor, bool isUp = true);

        void drawRadioButtonIndicator(QPainter *painter, const QRect &rect,
                                      const QColor &IndicatorColor, bool isOn);

        void drawCheckBoxIndicator(QPainter *painter, const QRect &rect,
                                   const QColor &border, const QColor &bgColor,
                                   const QColor &indicatorColor, CheckBoxIndicatorState indicatorState);

        void drawSeparator(QPainter *painter, const QRect &rect, QColor color, bool vertical = false);

        void drawMenuCheckedIndicator(QPainter *painter, const QRect &rect, QColor bgColor, QColor signColor);

        bool drawIndicatorArrowUpPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                           StyleDetailFetcher *detaulFetcher, const QWidget *widget);

        bool drawIndicatorArrowDownPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                             StyleDetailFetcher *detaulFetcher, const QWidget *widget);

        bool drawIndicatorArrowLeftPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                             StyleDetailFetcher *detaulFetcher, const QWidget *widget);

        bool drawIndicatorArrowRightPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                              StyleDetailFetcher *detaulFetcher, const QWidget *widget);

        void drawArrow(StyleDetailFetcher *fetcher, QPainter *painter,
                       const QStyleOption *option, const QWidget *widget,
                       ArrowOrientation orientation);

        void drawDecorationButton(QPainter *painter, const QRect &rect,
                                  const QColor &color, TitleBarButtonType buttonType);

        void renderProgressBarBusyContents(QPainter *painter, const QRect &rect,const QColor &color,const QColor &outline,bool horizontal,bool reverse,int progress);

        void renderProgressBarGroove(QPainter* painter, const QRect& rect,const QColor& color , const QColor& outline);
    };
}

#endif //KIRANSTYLE_DRAW_COMMON_HELPER_H
