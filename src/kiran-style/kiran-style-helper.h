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

#ifndef KIRANWIDGETS_QT5_KIRAN_STYLE_HELPER_H
#define KIRANWIDGETS_QT5_KIRAN_STYLE_HELPER_H

#include <kiran-style-public-define.h>

namespace Kiran{
    /**
     * @brief 方便外部调用KiranStyle进行绘制小部件的接口
     * @note 必须是在KiranStyle下,或者在QStyleSheet的底层为KiranStyle的情况下
     */
    namespace StyleHelper {
        /**
         * @brief 绘制Kiran自定义控件原始类型
         * @param pe   Kiran自定义控件原始类型枚举
         * @param opt  绘制选项
         * @param p    画笔
         * @param w    控件指针
         * @see QStyle::drawPrimitive
         * @see Kiran::KiranPrimitiveElement
         */
        void drawPrimitive(KiranPrimitiveElement pe, const QStyleOption *opt,
                           QPainter *p,const QWidget *w = nullptr);

        /**
         * @brief 绘制Kiran自定义控件
         * @param ce    Kiran自定义控件类型枚举
         * @param opt   绘制选项
         * @param p     画笔
         * @param w     控件指针
         */
        void drawControl(KiranControlElement ce, const QStyleOption *opt,
                         QPainter *p, const QWidget *w = nullptr);

        /**
         * @brief 获取Kiran自定义控件子元素区域
         * @param se      控件子元素类型枚举
         * @param opt     绘制选项
         * @param widget  控件指针
         * @return  自定义控件子元素绘制位置
         */
        QRect subElementRect(KiranSubElement se,const QStyleOption *opt,
                             const QWidget *widget = nullptr);

        /**
         * @brief 获取Kiran自定义控件基于内容大小在特殊的绘制选项和类型的尺寸
         * @param ct            内容类型
         * @param opt           绘制选项
         * @param contentsSize  内容尺寸
         * @param widget        控件指针
         * @return  控件在特殊绘制选项和类型的尺寸
         */
        QSize sizeFromContents(KiranContentsType ct,const QStyleOption *opt,
                               const QSize &contentsSize,const QWidget *widget = nullptr);
    }
}

#endif //KIRANWIDGETS_QT5_KIRAN_STYLE_HELPER_H
