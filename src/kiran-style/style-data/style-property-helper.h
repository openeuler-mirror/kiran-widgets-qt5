//
// Created by lxh on 2020/11/19.
//

#ifndef KIRANSTYLE_PROPERTY_HELPER_H
#define KIRANSTYLE_PROPERTY_HELPER_H

/// 写入自定义属性到控件中，Style插件读出属性做控件定制

class QToolButton;
class QPushButton;
class QSpinBox;
class QProgressBar;

namespace Kiran {
    ///TODO:在下列控件封成自定义控件后，提取枚举值到kiranwidgets-qt5/globalxxx中,枚举值需提供出去
    enum ButtonType {
        BUTTON_Normal,  ///普通按钮
        BUTTON_Default, ///默认按钮，突出显示
        BUTTON_Warning  ///警告按钮，突出警示显示
    };

    enum SpinboxArrowPosition {
        ARROW_POSITION_AUTOMATIC,   ///自动根据位置进行定位
        ARROW_TWO_SIDERS,           ///左右两侧
        ARROW_HORIZONTAL_STACK,     ///左右堆叠
        ARROW_VERTICAL_STACK        ///上下堆叠
    };

    ///进度条进度显示位置
    enum ProgressBarTextPosition {
        PROGRESS_TEXT_LEFT,     // 水平-左侧 垂直-上侧
        PROGRESS_TEXT_CENTER,   // 中间
        PROGRESS_TEXT_RIGHT     // 水平-右侧 垂直-下侧
    };

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
