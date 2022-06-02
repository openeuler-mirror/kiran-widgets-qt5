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
 
#ifndef KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H
#define KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H

#include <QRect>

class QStyle;
class QStyleOption;
class QPainter;
class QWidget;
class QStyleOptionFrame;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制输入框的相关方法
     */
    namespace DrawLineEditHelper {
        QSize lineEditSizeFromContents(const Style *style, const QStyleOption *option, const QSize &contentsSize,
                                       const QWidget *widget, StyleDetailFetcher *detailFetcher);
        QRect lineEditContentsRect(const Style* style,const QStyleOption* opt,const QWidget* widget);
        bool drawFrameLineEditPrimitive(const Style* style ,const QStyleOption* opt,QPainter* painter,
                                        StyleDetailFetcher* detaulFetcher,const QWidget* widget);
    };
}

#endif //KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H
