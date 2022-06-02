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
