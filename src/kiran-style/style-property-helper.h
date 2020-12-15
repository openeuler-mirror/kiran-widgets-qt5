//
// Created by lxh on 2020/11/19.
//

#ifndef KIRANSTYLE_PROPERTY_HELPER_H
#define KIRANSTYLE_PROPERTY_HELPER_H

/// 写入自定义属性到控件中，Style插件读出属性做控件定制

#include <kiran-public-define.h>

class QToolButton;
class QPushButton;
class QSpinBox;
class QProgressBar;
class QWidget;
namespace Kiran {
    namespace PropertyHelper {
        /// 获取按钮类型
        /// \param btn 按钮
        /// \return 按钮类型
        ButtonType getButtonType(const QPushButton *btn);

        /// 设置按钮类型
        /// \param btn 按钮
        /// \param type 按钮类型
        void setButtonType(QPushButton *btn, ButtonType type);

        /// 设置Spinbox类型的控件按钮显示位置(QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit)
        /// \param spinBox  spinbox类别的控件
        /// \param position 文本绘制位置
        void setSpinboxButtonPosition(QWidget *spinBox, SpinboxArrowPosition position);

        /// 设置Spinbox类型的控件按钮显示位置(QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit)
        /// \param spinBox spinbox类别的控件
        /// \return 文本绘制位置
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
