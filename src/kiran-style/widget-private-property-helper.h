/*
 * @file   widget-private-property-helper.h
 * @brief  KiranStyle 私有的控件属性设置获取接口
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_WIDGET_PRIVATE_PROPERTY_HELPER_H
#define KIRANWIDGETS_QT5_WIDGET_PRIVATE_PROPERTY_HELPER_H

#include "kiran-style-public-define.h"
#include <QSize>

class QLineEdit;
namespace Kiran{
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
