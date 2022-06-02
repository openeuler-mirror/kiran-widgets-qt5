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
 
#ifndef KIRANSTYLE_PROPERTY_HELPER_H
#define KIRANSTYLE_PROPERTY_HELPER_H

#include <kiran-style-public-define.h>

class QToolButton;
class QPushButton;
class QSpinBox;
class QProgressBar;
class QWidget;
/**
 * WARNING:
 * 该文件提供接口自2.3已被废弃,现保持兼容性
 * 3.0将会被删除，后续不再提供相关接口
 * 2.3版本之后使用请调用kiranstyle提供的相关接口
 */
namespace Kiran {
    /**
     * @brief KiranStyle自定义属性读写接口,可定制部分KiranStyle绘制细节,KiranStyle读出属性值进行特殊的绘制
     */
    namespace WidgetPropertyHelper {

        /**
         * @brief 获取按钮类型
         * @param btn 按钮控件，从该按钮中取出属性
         * @return 该按钮的Style绘制类型,采取什么风格进行绘制
         * @see Kiran::ButtonType
         */
        Q_DECL_DEPRECATED ButtonType getButtonType(const QPushButton *btn);

        /**
         * @brief 设置按钮类型
         * @param btn  按钮
         * @param type 按钮的Style绘制类型,采取什么风格进行绘制
         * @see Kiran::ButtonType
         */
        Q_DECL_DEPRECATED void setButtonType(QPushButton *btn, ButtonType type);

        /**
         * @brief 设置Spinbox类型的控件按钮显示位置(QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit)
         * @param spinBox  spinbox类别的控件
         * @param position 文本绘制位置
         * @see Kiran::SpinboxArrowPosition
         */
        Q_DECL_DEPRECATED void setSpinboxButtonPosition(QWidget *spinBox, SpinboxArrowPosition position);

        /**
         * @brief 获取Spinbox类型的控件按钮显示位置(QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit)
         * @param spinBox 获取属性的控件
         * @return SpinBox按钮绘制位置枚举
         * @see Kiran::SpinboxArrowPosition
         */
        Q_DECL_DEPRECATED SpinboxArrowPosition getSpinboxButtonPosition(const QWidget *spinBox);

        /**
         * @brief 设置QProgressBar进度文本显示位置
         * @param progressBar   进度条
         * @param textPosition  文本绘制位置
         * @see Kiran::ProgressBarTextPosition
         */
        Q_DECL_DEPRECATED void setProgressBarTextProsition(QProgressBar *progressBar,ProgressBarTextPosition textPosition);

        /**
         * @brief 获取QProgressBar文本绘制位置
         * @param progressBar 进度条
         * @return 文本绘制位置
         * @see Kiran::ProgressBarTextPosition
         */
        Q_DECL_DEPRECATED ProgressBarTextPosition getProgressBarTextPosition(const QProgressBar *progressBar);
    }
}
#endif //KIRANSTYLE_PROPERTY_HELPER_H
