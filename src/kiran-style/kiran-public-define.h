/*
 * @file   kiran-public-define.h
 * @brief  KiranStyle提供的部分枚举值做为接口参数使用
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H
#define KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H

#include <qnamespace.h>

namespace Kiran{

    /**
     * @brief KiranStyle中内置的三种按钮样式
     */
    enum ButtonType {
        BUTTON_Normal,   /** < 普通按钮 */
        BUTTON_Default,  /** < 默认按钮，突出显示 */
        BUTTON_Warning   /** < 警告按钮，突出警示显示 */
    };

    /**
     * @brief Spinbox类型(包括QSpinBox,QTimeEdit,QDateEdit,QDateTimeEdit等)上下按钮位置枚举
     */
    enum SpinboxArrowPosition {
        ARROW_POSITION_AUTOMATIC,   /** < 自动根据位置进行定位 */
        ARROW_TWO_SIDERS,           /** < 左右两侧 */
        ARROW_HORIZONTAL_STACK,     /** < 左右堆叠 */
        ARROW_VERTICAL_STACK        /** < 上下堆叠 */
    };

    /**
     * @brief QProgressBar进度条进度文本显示位置
     */
    enum ProgressBarTextPosition {
        PROGRESS_TEXT_LEFT,     /** < 水平-左侧 垂直-上侧 */
        PROGRESS_TEXT_CENTER,   /** < 中间 */
        PROGRESS_TEXT_RIGHT     /** < 水平-右侧 垂直-下侧 */
    };

    /**
     * @brief KiranSideWidget支持的Item特殊样式定制
     */
    enum KiranSidebarDataRole{
        ItemStatus_Role = Qt::UserRole+1, /** < Item状态显示,eg:账户管理工具的侧边栏显示启用和禁用状态 */
        ItemStatusColor_Role /** <　Item状态绘制颜色  */
    };
}

#endif //KIRANWIDGETS_QT5_KIRAN_PUBLIC_DEFINE_H
