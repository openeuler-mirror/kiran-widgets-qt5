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

#ifndef KIRANWIDGETS_QT5_WIDGET_PRIVATE_PROPERTY_HELPER_H
#define KIRANWIDGETS_QT5_WIDGET_PRIVATE_PROPERTY_HELPER_H

#include "kiran-style-public-define.h"
#include <QSize>

class QLineEdit;
namespace Kiran{
    /**
     * @brief 控件私有属性辅助接口,不提供给外部使用
     */
    namespace WidgetPrivatePropertyHelper {
        /**
          *  通过设置QLineEdit的图标位置和图标大小,KiranStyle绘制时和计算控件会考虑到图片的位置(但是不绘制)
          *  需从QLineEdit派生,实现paintEvent函数,在调用QLineEdit::paintEvent绘制完背景和边框之后,再进行图片的绘制
          */
        /* 设置QLineEdit绘制图标位置 */
        void setLineEditIconPosition(QLineEdit* edit,IconLineEditIconPosition position);
        /* 获取QLineEdit绘制图标位置 */
        IconLineEditIconPosition  getLineEditIconPosition(const QLineEdit* edit);
        /* 设置QLineEdit绘制图标大小 */
        void setLineEditIconSize(QLineEdit* edit,QSize size);
        /* 获取QLineEdit绘制图标大小 */
        QSize getLineEditIconSize(const QLineEdit* edit);
    };
}

#endif //KIRANWIDGETS_QT5_WIDGET_PRIVATE_PROPERTY_HELPER_H
