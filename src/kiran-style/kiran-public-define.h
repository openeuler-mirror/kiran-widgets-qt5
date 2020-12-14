//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H
#define KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H

namespace Kiran{

    ///支持的主题枚举
    enum StyleEnum {
        KIRAN_BLACK
    };

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

}

#endif //KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H
