/*
 * @file   style-property-helper.h
 * @brief  KiranStyle自定义属性读写接口
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANSTYLE_PROPERTY_HELPER_H
#define KIRANSTYLE_PROPERTY_HELPER_H

#include <kiran-public-define.h>

class QToolButton;
class QPushButton;
class QSpinBox;
class QProgressBar;
class QWidget;
namespace Kiran {
    /**
     * @brief KiranStyle自定义属性读写接口,使用者可定制部分KiranStyle绘制细节,KiranStyle读出属性值进行特殊的绘制
     */
    namespace PropertyHelper {

        /**
         * @brief 获取按钮类型
         * @param btn 按钮控件，从该按钮中取出属性
         * @return 该按钮的类型
         */
        ButtonType getButtonType(const QPushButton *btn);

        /**
         * @brief 设置按钮类型
         * @param btn  按钮
         * @param type 按钮类型
         */
        void setButtonType(QPushButton *btn, ButtonType type);


        /**
         * @brief 设置Spinbox类型的控件按钮显示位置(QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit)
         * @param spinBox  spinbox类别的控件
         * @param position 文本绘制位置
         */
        void setSpinboxButtonPosition(QWidget *spinBox, SpinboxArrowPosition position);

        /**
         * @brief 获取Spinbox类型的控件按钮显示位置(QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit)
         * @param spinBox 获取属性的控件
         * @return SpinBox按钮绘制位置枚举
         */
        SpinboxArrowPosition getSpinboxButtonPosition(const QWidget *spinBox);


        /// 设置QProgressBar进度文本显示位置
        /// \param progressBar  进度条
        /// \param textPosition 文本绘制位置
        void setProgressBarTextProsition(QProgressBar *progressBar,ProgressBarTextPosition textPosition);

        /// 获取QProgressBar文本绘制位置
        /// \param progressBar  进度条
        /// \return 文本绘制位置
        ProgressBarTextPosition getProgressBarTextPosition(const QProgressBar *progressBar);

    }
}
#endif //KIRANSTYLE_PROPERTY_HELPER_H
