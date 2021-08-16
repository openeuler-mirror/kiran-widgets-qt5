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
 
#ifndef KIRANSTYLE_DRAW_COMBO_BOX_HELPER_H
#define KIRANSTYLE_DRAW_COMBO_BOX_HELPER_H

#include <QStyle>

class QStyleOptionComplex;
class QPainter;
class QWidget;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    /**
     * @brief 绘制ComboBox的相关方法
     */
    namespace DrawComboBoxHelper{
        bool drawComboBoxComplexControl(const Style* style, const QStyleOptionComplex* opt,StyleDetailFetcher* fetcher, QPainter* p, const QWidget* w);
        bool drawComboBoxMenuItem(const Style *style, const QStyleOption *opt,QPainter *p, StyleDetailFetcher *fetcher, const QWidget *widget);
        QRect comboBoxSubControlRect(const Style *style,const QStyleOptionComplex *opt, QStyle::SubControl subControl,const QWidget *w);
    }
}


#endif //KIRANSTYLE_DRAW_COMBO_BOX_HELPER_H
