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
