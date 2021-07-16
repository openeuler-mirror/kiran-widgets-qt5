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
 
#ifndef KIRANSTYLE_DRAW_COMMON_HELPER_H
#define KIRANSTYLE_DRAW_COMMON_HELPER_H

#include <QPainter>
#include <QStyle>
#include <QSpinBox>
#include <QStyle>

#include "kiran-style-private-defines.h"

namespace Kiran {
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制通用细节的相关方法
     */
    namespace DrawCommonHelper {
        /* 基于QX11Info获取窗口管理器混成开关 */
        bool isCompositingManagerRuning();

        /* 通过指定宽高获取矩形中的居中区域 */
        QRect centerRect(const QRect &rect, int width, int height);
        /* 通过指定大小获取矩形中的居中区域 */
        QRect centerRect(const QRect &rect, const QSize &size);

        /* 使用给定的边距调整矩形 */
        QRect insideMargin(const QRect &r, int margin);
        /* 使用给定的边距调整矩形 */
        QRect insideMargin(const QRect &r, int marginWidth, int marginHeight);

        /* 使用给定的边距调整大小 */
        QSize expandSize(const QSize &size, int margin);
        /* 使用给定的边距调整大小 */
        QSize expandSize(const QSize &size, int marginWidth, int marginHeight);

        /* 获取绘制圆角矩形路径 */
        QPainterPath getRoundedRectanglePath(const QRect &rect, int tlRadius,
                                             int trRadius, int blRadius, int brRadius);

        /* 绘制Frame */
        void drawFrame(QPainter *painter, const QRect &rect, int radius,
                       int outlineWidth, const QColor &bgColor, const QColor &outline);

        /* 绘制Spinbox类别的增减按钮 */
        void drawSpinboxArrow(QPainter *painter, const QRect &rect, const QRect &spinboxRect,
                              int spinboxRadius, QColor bgColor, QColor signColor, bool isUp = true);

        /* 绘制单选按钮的指示器 */
        void drawRadioButtonIndicator(QPainter *painter, const QRect &rect,
                                      const QColor &IndicatorColor, bool isOn);

        /* 绘制复选按钮的指示器 */
        void drawCheckBoxIndicator(QPainter *painter, const QRect &rect,
                                   const QColor &border, const QColor &bgColor,
                                   const QColor &indicatorColor, CheckBoxIndicatorState indicatorState);

        /* 绘制分割器 */
        void drawSeparator(QPainter *painter, const QRect &rect, QColor color, bool vertical = false);

        /* 绘制菜单勾选指示器 */
        void drawMenuCheckedIndicator(QPainter *painter, const QRect &rect, QColor bgColor, QColor signColor);

        /* PE_IndicatorArrowUp的绘制 */
        bool drawIndicatorArrowUpPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                           StyleDetailFetcher *detailFetcher, const QWidget *widget);
        /* PE_IndicatorArrowDown的绘制 */
        bool drawIndicatorArrowDownPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                             StyleDetailFetcher *detailFetcher, const QWidget *widget);
        /* PE_IndicatorArrowLeft的绘制 */
        bool drawIndicatorArrowLeftPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                             StyleDetailFetcher *detailFetcher, const QWidget *widget);
        /* PE_IndicatorArrowRight的绘制 */
        bool drawIndicatorArrowRightPrimitive(const Style *style, const QStyleOption *opt, QPainter *painter,
                                              StyleDetailFetcher *detailFetcher, const QWidget *widget);

        /* KiranSidebarWidget选中标志箭头,ComboBox下拉箭头标示 */
        void drawArrow(StyleDetailFetcher *fetcher, QPainter *painter,
                       const QStyleOption *option, const QWidget *widget,
                       ArrowOrientation orientation,int renderSize = 0);

        /* 绘制标题栏按钮图标 */
        void drawDecorationButton(QPainter *painter, const QRect &rect,const QColor &color, TitleBarButtonType buttonType);

        /* 绘制进度条繁忙滑块 */
        void renderProgressBarBusyContents(QPainter *painter, const QRect &rect,const QColor &color,const QColor &outline,bool horizontal,bool reverse,int progress);

        /* 绘制进度条滑块槽 */
        void renderProgressBarGroove(QPainter* painter, const QRect& rect,const QColor& color , const QColor& outline);
    };
}

#endif //KIRANSTYLE_DRAW_COMMON_HELPER_H
