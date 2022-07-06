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
