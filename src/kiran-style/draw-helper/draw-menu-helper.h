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
