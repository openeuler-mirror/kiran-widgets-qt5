/*
 * @file   draw-menu-helper.h
 * @brief  绘制Menu
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANSTYLE_DRAW_MENU_HELPER_H
#define KIRANSTYLE_DRAW_MENU_HELPER_H

#include <QSize>

class QStyleOption;
class QWidget;
class QPainter;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制Menu相关方法
     */
    namespace DrawMenuHelper{
        /// Menu
        /// 绘制QComboBox下拉框、绘制QMenu框架
        bool drawPanelMenuPrimitive(const Style* style,const QStyleOption* opt,QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);
        ///drawControl-CE_MenuBarEmptyArea
        bool drawMenuBarEmptryAreaControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        ///drawControl-CE_MenuBarItem
        bool drawMenuBarItemControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher *fetcher,const QWidget* widget);
        ///drawControl-CE_MenuEmptryArea
        bool drawMenuEmptryAreaControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        ///drawControl-CE_MenuItem
        bool drawMenuItemControl(const Style* style,const QStyleOption* opt,QPainter* p, StyleDetailFetcher* fetcher,const QWidget* widget);
        QSize menuItemSizeFromContents(const Style *style, const QStyleOption *option, const QSize &contentsSize,
                                       const QWidget *widget, StyleDetailFetcher *fetcher);

        /// QComboBox
        bool drawComboboxItem(const Style* style,const QStyleOption* opt,QPainter* p,StyleDetailFetcher* fetcher,const QWidget* widget);
    }
}


#endif //KIRANSTYLE_DRAW_MENU_HELPER_H
