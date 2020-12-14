//
// Created by lxh on 2020/11/19.
//

#ifndef KIRANSTYLE_PROPERTY_HELPER_H
#define KIRANSTYLE_PROPERTY_HELPER_H

/// 写入自定义属性到控件中，Style插件读出属性做控件定制

#include "kiran-public-define.h"

class QToolButton;
class QPushButton;
class QSpinBox;
class QProgressBar;
namespace Kiran {
    namespace PropertyHelper {
        ButtonType getButtonType(const QPushButton *btn);
        void setButtonType(QPushButton *btn, ButtonType type);

        ///设置QSpinbox的按钮显示位置
        void setSpinboxButtonPosition(QSpinBox *spinBox, SpinboxArrowPosition position);
        SpinboxArrowPosition getSpinboxButtonPosition(QSpinBox *spinBox);

        void setProgressBarTextProsition(QProgressBar *progressBar,ProgressBarTextPosition textPosition);
        ProgressBarTextPosition getProgressBarTextPosition(const QProgressBar *progressBar);
    }
}
#endif //KIRANSTYLE_PROPERTY_HELPER_H
