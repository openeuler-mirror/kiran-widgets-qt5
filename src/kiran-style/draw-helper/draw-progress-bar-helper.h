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
