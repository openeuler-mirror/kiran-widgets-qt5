#TODO List
- [ ] 将之前提供的Kiran::WidgetPropertyHelper接口以及kiran-style-public-define.h定义的枚举标记废弃，通过转调至kiran-qt5-integration之中的KiranStyle提供的接口，将枚举定义移动到其他位置
- [ ] 修改之前自定义控件的绘制，确认是否将自动控件的绘制过程不交由Style进行绘制，直接通过kiran-qt5-integration提供的KiranPalette拿到颜色进行绘制
- [ ] 加入字体绑定的功能，加入字体分级
- [ ] kiranwidgets-qt5项目之中的kiranstyle后续都将废弃,后续更新接口时删除该部分代码
- [ ] scrollarea 不占用空间 overlap