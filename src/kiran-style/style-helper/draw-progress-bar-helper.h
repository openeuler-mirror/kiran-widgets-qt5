/*
 * @file   draw-progress-bar-helper.h
 * @brief  绘制进度条
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 

#ifndef KIRANWIDGETS_QT5_DRAW_PROGRESS_BAR_HELPER_H
#define KIRANWIDGETS_QT5_DRAW_PROGRESS_BAR_HELPER_H

#include <QRect>

class QStyleOption;

class QWidget;
class QPainter;
namespace Kiran {
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制进度条的相关方法
     */
    namespace DrawProgressBarHelper {
        //sizeFromContents
        QSize progressBarSizeFromContents(const Style *style, const QStyleOption *opt,
                                          const QSize &contentsSize, const QWidget *w,
                                          StyleDetailFetcher *fetcher);

        //subElementRect
        QRect progressBarGrooveRect(const Style *style, const QStyleOption *option, const QWidget *widget);
        QRect progressBarContentsRect(const Style *style, const QStyleOption *option, const QWidget *widget);
        QRect progressBarLabelRect(const Style *style, const QStyleOption *option, const QWidget *widget);

        //drawControl
        bool drawProgressBarControl(const Style* style, const QStyleOption* opt, QPainter* p, StyleDetailFetcher* fetcher, const QWidget* widget);
        bool drawProgressBarGrooveControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawProgressBarContentsControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        bool drawProgressBarLabelControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
    }
}

#endif //KIRANWIDGETS_QT5_DRAW_PROGRESS_BAR_HELPER_H
