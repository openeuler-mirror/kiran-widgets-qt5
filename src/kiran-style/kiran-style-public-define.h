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
  
#ifndef KIRANWIDGETS_QT5_KIRAN_STYLE_PUBLIC_DEFINE_H
#define KIRANWIDGETS_QT5_KIRAN_STYLE_PUBLIC_DEFINE_H

#include <qnamespace.h>
#include <QStyle>

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
    enum SidebarWidgetDataRole{
        ItemStatus_Role = Qt::UserRole+666, /** < Item状态显示,eg:账户管理工具的侧边栏显示启用和禁用状态 */
        ItemStatusColor_Role                /** <　Item状态绘制颜色  */
    };

    /**
     * @brief KiranIconLinEdit支持的图片位置枚举
     */
    enum IconLineEditIconPosition{
        ICON_POSITION_NONE, /** < 不绘制Icon */
        ICON_POSITION_LEFT, /** < 图标绘制在输入框内偏左 */
        ICON_POSITION_RIGHT /** < 图标绘制在输入框内偏右 */
    };

    /**
     * @brief Kiran自定义控件原始元素枚举
     */
    enum KiranPrimitiveElement{
        PE_SwitchButtonIndicator = QStyle::PE_CustomBase+1, /** < KiranSwitchButton开关指示器  */

        PE_SearchBoxIndicator,/** < KiranSearchBox搜索指示器(搜索图标) */

        PE_KiranImageSelector,/** < KiranImageSelector 图片选择器主体 **/

        PE_KiranImageSelectorButtonFrame,/** < KiranImageSelector 按钮背景边框 **/
        PE_KiranImageSelectorPrevButtonArrow,/** < KiranImageSelector 向上跳转箭头 **/
        PE_KiranImageSelectorNextButtonArrow,/** < KiranImageSelector 向下跳转箭头 * **/
    };

    /**
     * @brief Kiran自定义控件控制元素枚举
     */
    enum KiranControlElement{
        CE_SwitchButton = QStyle::CE_CustomBase+1 /** < 绘制KiranSwitchButton */
    };

    /**
     * @brief Kiran自定义控件内容类型,计算各种小部件内容的大小
     */
    enum KiranContentsType{
        CT_SwitchButton = QStyle::CT_CustomBase+1 /** < KiranSwitchButton控件内容枚举 */
    };

    /**
     * @brief Kiran自定义控件子区域枚举,Style实现这些区域来绘制小组件的不同部分
     */
    enum KiranSubElement{
        SE_SwitchButtonContents = QStyle::SE_CustomBase+1, /** < KiranSwitchButton内容文本绘制区域 */
        SE_SwitchButtonIndicator /** < KiranSwitchButton开关指示标志区域 */
    };

    /**
     * @brief KiranPixelMetric 像素度量属性枚举
     */
     enum KiranPixelMetric{
         PM_KiranImageSelectorRadius = QStyle::PM_CustomBase+1
     };
}

#endif //KIRANWIDGETS_QT5_KIRAN_STYLE_PUBLIC_DEFINE_H
