//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H
#define KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H

#include <qnamespace.h>

namespace Kiran{

    /// KiranStyle中内置的三种按钮样式
    enum ButtonType {
        BUTTON_Normal,  ///普通按钮
        BUTTON_Default, ///默认按钮，突出显示
        BUTTON_Warning  ///警告按钮，突出警示显示
    };

    /// Spinbox类型(包括QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit等)上下按钮位置枚举
    enum SpinboxArrowPosition {
        ARROW_POSITION_AUTOMATIC,   ///自动根据位置进行定位
        ARROW_TWO_SIDERS,           ///左右两侧
        ARROW_HORIZONTAL_STACK,     ///左右堆叠
        ARROW_VERTICAL_STACK        ///上下堆叠
    };

    /// QProgressBar进度条进度文本显示位置
    enum ProgressBarTextPosition {
        PROGRESS_TEXT_LEFT,     // 水平-左侧 垂直-上侧
        PROGRESS_TEXT_CENTER,   // 中间
        PROGRESS_TEXT_RIGHT     // 水平-右侧 垂直-下侧
    };

    enum KiranSidebarDataRole{
        ItemStatus_Role = Qt::UserRole+1,
        ItemStatusColor_Role
    };
}

#endif //KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H
