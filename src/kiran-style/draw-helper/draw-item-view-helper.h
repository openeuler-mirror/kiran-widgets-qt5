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
#ifndef KIRANWIDGETS_QT5_DRAW_ITEM_VIEW_HELPER_H
#define KIRANWIDGETS_QT5_DRAW_ITEM_VIEW_HELPER_H

#include <QRect>

class QStyleOption;
class QSize;
class QWidget;
class QPainter;
namespace Kiran {
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制ItemView的相关方法
     */
    namespace DrawItemViewHelper {
        //eg: ListView::updateGeometries->ListViewPrivate::itemSize->Delegate::sizeHint->delegate::sizeHint->Style::sizeFromContents
        QSize kiranSidebarItemSizeFromContent(const Style *style, const QStyleOption *opt,
                                              const QSize &contentsSize, const QWidget *w,
                                              StyleDetailFetcher *fetcher);

        QRect kiranSidebarItemCheckIndicatorRect(const Style *style,
                                                 const QStyleOption *opt,
                                                 const QWidget *w);

        QRect kiranSiderbarItemDecorationRect(const Style *style,
                                              const QStyleOption *opt,
                                              const QWidget *w);

        QRect kiranSiderbarItemTextRect(const Style *style,
                                        const QStyleOption *opt,
                                        const QWidget *w);

        bool drawPanelKianSidebarItem(const Style *style,
                                      const QStyleOption *opt,
                                      QPainter *p,
                                      StyleDetailFetcher *fetcher,
                                      const QWidget *widget);

        bool drawIndicatorKiranSidebarItemCheck(const Style *style,
                                                const QStyleOption *opt,
                                                QPainter *p,
                                                StyleDetailFetcher *fetcher,
                                                const QWidget *widget);

    }
}
#endif //KIRANWIDGETS_QT5_DRAW_ITEM_VIEW_HELPER_H
