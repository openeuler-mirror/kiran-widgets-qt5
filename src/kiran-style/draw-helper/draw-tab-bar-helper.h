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
 

#ifndef KIRANWIDGETS_QT5_DRAW_TAB_BAR_HELPER_H
#define KIRANWIDGETS_QT5_DRAW_TAB_BAR_HELPER_H

#include <QStyleOption>

class QWidget;
class QPainter;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制TabBar的相关方法
     */
    namespace DrawTabBarHelper{
        ///获取TabBar Tab大小
        QSize tabBarTabSizeFromContents(const Style *style, const QStyleOption *opt, const QSize &contentsSize,
                                        const QWidget *w, StyleDetailFetcher *fetcher);

        ///定位TabBar左侧控件绘制位置
        QRect tabBarTabLeftButtonElementRect(const Style *style, const QStyleOption *opt, const QWidget *w);
        //定位TabBar右侧控件绘制位置
        QRect tabBarTabRightButtonElementRect(const Style *style, const QStyleOption *opt, const QWidget *w);
        //定位TabBar文字绘制位置
        QRect tabBarTabTabTextElementRect(const Style *style, const QStyleOption *opt, const QWidget *w);
        ///NOTE:TearIndicator是啥?
        QRect tabBarTearIndicatorLeftRect(const Style *style, const QStyleOption *opt, const QWidget *w);
        QRect tabBarTearIndicatorRightRect(const Style *style,const QStyleOption *opt, const QWidget *w);
        ///TabBar过多时，显示左右移动TabBar显示Tab的按钮
        QRect tabBarScrollLeftButtonRect(const Style *style,const QStyleOption *opt, const QWidget *w);
        QRect tabBarScrollRightButtonRect(const Style *style,const QStyleOption *opt, const QWidget *w);

        ///绘制TabBar上的关闭按钮
        bool drawIndicatorTabClosePrimitive(const Style* style ,const QStyleOption* opt,QPainter* painter,StyleDetailFetcher* detaulFetcher,const QWidget* widget);
        bool drawIndicatorTabTearLeft(const Style* style ,const QStyleOption* opt,QPainter* painter,StyleDetailFetcher* detaulFetcher,const QWidget* widget);
        bool drawIndicatorTabTearRight(const Style* style ,const QStyleOption* opt,QPainter* painter,StyleDetailFetcher* detaulFetcher,const QWidget* widget);

        ///绘制TabBar Tab
        bool drawTabBarTabControl(const Style *style, const QStyleOption *opt,QPainter *p,StyleDetailFetcher *fetcher,const QWidget *widget);
        ///绘制Tab的形状
        bool drawTabBarTabLabelControl(const Style *style, const QStyleOption *opt, QPainter *p, StyleDetailFetcher *fetcher, const QWidget *widget);
        ///绘制Tab的文本和图片
        bool drawTabBarTabShapeControl(const Style *style, const QStyleOption *opt, QPainter *p, StyleDetailFetcher *fetcher, const QWidget *widget);
    }
}

#endif //KIRANWIDGETS_QT5_DRAW_TAB_BAR_HELPER_H
