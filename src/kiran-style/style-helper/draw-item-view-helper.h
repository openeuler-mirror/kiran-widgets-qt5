/*
 * @file   draw-item-view-helper.h
 * @brief  绘制ItemView
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
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
