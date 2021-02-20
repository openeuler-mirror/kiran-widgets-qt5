/**
 *@file  draw-image-selector-helper.h
 *@brief 绘制图片选择器相关具体实现
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_DRAW_IMAGE_SELECTOR_HELPER_H
#define KIRANWIDGETS_QT5_DRAW_IMAGE_SELECTOR_HELPER_H

class QStyleOption;
class QPainter;
class QWidget;
namespace Kiran {
    class Style;
    class StyleDetailFetcher;
    namespace DrawImageSelectorHelper{
        void drawPEKiranImageSelector(const Style *style, const QStyleOption *opt,
                                              QPainter *p,StyleDetailFetcher *fetcher,
                                              const QWidget *widget);

        void drawPEKiranImageSelectorButtonFrame(const Style *style,const QStyleOption *opt,
                                                        QPainter *p,StyleDetailFetcher *fetcher,
                                                        const QWidget *widget);

        void drawPEKiranImageSelectorPrevButtonArrow(const Style *style,const QStyleOption *opt,
                                                     QPainter *p,StyleDetailFetcher *fetcher,
                                                     const QWidget *widget);

        void drawPEKiranImageSelectorNextButtonArrow(const Style *style,const QStyleOption *opt,
                                                     QPainter *p,StyleDetailFetcher *fetcher,
                                                     const QWidget *widget);

        void drawPEKiranImageSelectorItem(const Style *style,const QStyleOption *opt,
                                          QPainter *p,StyleDetailFetcher *fetcher,
                                          const QWidget *widget);
    }
}


#endif //KIRANWIDGETS_QT5_DRAW_IMAGE_SELECTOR_HELPER_H
