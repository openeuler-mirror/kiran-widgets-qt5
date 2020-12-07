//
// Created by lxh on 2020/11/24.
//

#ifndef KIRANSTYLE_KIRAN_GLOBAL_DEFINES_H
#define KIRANSTYLE_KIRAN_GLOBAL_DEFINES_H

#include <QStyle>

namespace Kiran{
    enum StyleEnum {
        KIRAN_BLACK
    };

    enum KiranPrimitiveElement{
        PE_SwitchButtonIndicator = QStyle::PE_CustomBase+1
    };

    enum KiranControlElement{
        CE_SwitchButton = QStyle::CE_CustomBase+1
    };

    enum KiranContentsType{
        CT_SwitchButton = QStyle::CT_CustomBase+1
    };

    enum KiranSubElement{
        SE_SwitchButtonContents = QStyle::SE_CustomBase+1,
        SE_SwitchButtonIndicator
    };

    enum KiranComplexControl{

    };

    enum KiranSubControl{

    };

    enum KiranPixelMetric{

    };

    enum KiranStyleHint{

    };

    enum Metrics {
        // frames
        Frame_FrameWidth = 4,
        Frame_FrameRadius = 4,

        // layout
        Layout_TopLevelMarginWidth = 10,
        Layout_ChildMarginWidth = 6,
        Layout_DefaultSpacing = 6,

        // line editors
        LineEdit_FrameWidth = 10,

        // menu items
        Menu_FrameWidth = 2,
        MenuItem_MarginWidth = 9,
        MenuItem_ItemSpacing = 6,
        MenuItem_AcceleratorSpace = 16,
        MenuItem_CheckedIndicatorSize = 18,
        MenuButton_IndicatorWidth = 20,


        // combobox
        ComboBox_FrameWidth = 7,
        ComboBox_ItemSpacing = 6,

        // spinbox
        SpinBox_FrameWidth = LineEdit_FrameWidth,
        SpinBox_ArrowButtonWidth = 20,

        // groupbox title margin
        GroupBox_TitleMarginWidth = 4,

        // buttons
        Button_MinWidth = 80,
        Button_MarginWidth = 4,
        Button_ItemSpacing = 3,

        // switch button
        //NOTE:预留，为后续增加聚焦虚线框
        SwitchButton_FocusMarginWidth = 3,
        SwitchButton_IndicatorCircularSize = 16,
        SwitchButton_IndicatorCircularSpacing = 4,
        SwitchButton_IndicatorWidth = 48,
        SwitchButton_IndicatorHeight = 22,
        SwitchButton_ItemSpacing = 8,

        // tool buttons
        ToolButton_MarginWidth = 6,
        ToolButton_ItemSpacing = 4,
        ToolButton_InlineIndicatorWidth = 12,

        // checkboxes and radio buttons
        CheckBox_Size = 18,
        CheckBox_FocusMarginWidth = 3,
        CheckBox_ItemSpacing = 4,

        // menubar items
        MenuBarItem_MarginWidth = 8,
        MenuBarItem_MarginHeight = 4,

        // scrollbars
        ScrollBar_Extend = 14,
        ScrollBar_SliderWidth = 8,
        ScrollBar_MinSliderHeight = 24,
        ScrollBar_NoButtonHeight = (ScrollBar_Extend - ScrollBar_SliderWidth) / 2,
        ScrollBar_SingleButtonHeight = 0,
        ScrollBar_DoubleButtonHeight = 0,

        // toolbars
        ToolBar_FrameWidth = 2,
        ToolBar_HandleExtent = 10,
        ToolBar_HandleWidth = 6,
        ToolBar_SeparatorWidth = 8,
        ToolBar_ExtensionWidth = 20,
        ToolBar_ItemSpacing = 0,

        // progressbars
        ProgressBar_BusyIndicatorSize = 24,
        ProgressBar_Thickness = 3,
        ProgressBar_ItemSpacing = 3,

        // mdi title bar
        TitleBar_MarginWidth = 4,

        // sliders
        Slider_TickLength = 4,
        Slider_TickMarginWidth = 6,
        Slider_GrooveThickness = 3,
        Slider_ControlThickness = 24,

        // tabbar
        TabBar_TabMarginHeight = 9,
        TabBar_TabMarginWidth = 8,
        TabBar_TabMinWidth = 80,
        TabBar_TabMinHeight = 36,
        TabBar_TabItemSpacing = 8,
        TabBar_TabOverlap = 1,
        TabBar_BaseOverlap = 0,

        // tab widget
        TabWidget_MarginWidth = 4,

        // toolbox
        ToolBox_TabMinWidth = 80,
        ToolBox_TabItemSpacing = 4,
        ToolBox_TabMarginWidth = 8,

        // tooltips
        ToolTip_FrameWidth = 3,

        // scroll areas
        ScrollArea_FrameWidth = 2,

        // list headers
        Header_MarginWidth = 3,
        Header_ItemSpacing = 2,
        Header_ArrowSize = 10,

        // tree view
        ItemView_ArrowSize = 10,
        ItemView_ItemMarginWidth = 3,
        SidePanel_ItemMarginWidth = 4,

        // splitter
        Splitter_SplitterWidth = 1,

        // shadow dimensions
        Shadow_Overlap = 0

    };

    enum CheckBoxIndicatorState{
        CheckOff,
        CheckPartial,
        CheckOn
    };

    enum ArrowOrientation
    {
        ArrowNone,
        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight
    };

}


#endif //KIRANSTYLE_KIRAN_GLOBAL_DEFINES_H
