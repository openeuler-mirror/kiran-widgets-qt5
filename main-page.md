@mainpage    
**kiranwidgets-qt5** 提供了许多Qt开发中的常用控件    
##功能组件列表
<table bgcolor="#f8f8ff" cellspacing="10" cellpadding="10" aria-rowcount="10">
    <tr align="left">
    	<th>类名</th>
        <th>头文件</th>
        <th>功能简述</th>
    </tr>
    <tr>
        <td>KiranApplication</td>
        <td>kiran-application.h</td>
        <td>在QApplication之上加入了对字体的监控和设置KiranStyle等功能</td>
    </tr>
    <tr>
        <td>KiranMessageBox</td>
        <td>kiran-message-box.h</td>
        <td>基于QMessageBox所封装的消息对话框</td>
    </tr>
    <tr>
        <td>KiranSearchBox</td>
        <td>kiran-search-box.h</td>
        <td>修改了QLineEdit的绘制的搜索框</td>
    </tr>
    <tr>
        <td>KiranSearchBox</td>
        <td>kiran-search-box.h</td>
        <td>修改了QLineEdit的绘制的搜索框</td>
    </tr>
    <tr >
        <td>KiranSidebarWidget</td>
        <td>kiran-sidebar-widget.h</td>
        <td>基于QListWidget封装的侧边栏组件</td>
    </tr>
    <tr>
        <td>KiranSingleApplication</td>
        <td>kiran-single-application.h</td>
        <td>KiranApplication之封装了进程单例相关功能</td>
    </tr>
    <tr>
        <td>KiranSwitchButton</td>
        <td>kiran-switch-button.h</td>
        <td>基于QAbstractButton封装的开关按钮</td>
    </tr>
    <tr>
        <td>KiranTitlebarWindow</td>
        <td>kiran-titlebar-window.h</td>
        <td>Kiran桌面自定义标题栏窗口</td>
    </tr>
</table>

##KiranStyle接口
**KiranStyle** 指的是 **Kiran** 桌面所写的Qt插件，暂时只通过 **KiranApplication** 或其派生类 **KiranSingleApplication** 来加载其中提供了部分 **Kiran桌面Qt常用控件绘制** 和 **Kiran桌面自定义控件** 的绘制
<table bgcolor="#f8f8ff" cellspacing="10" cellpadding="10" aria-rowcount="10">
    <tr align="left">
    	<th>类名</th>
        <th>头文件</th>
        <th>功能简述</th>
    </tr>
    <tr>
        <td>Kiran::PropertyHelper</td>
        <td>style-property-helper.h</td>
        <td>在KiranStyle下可以通过该命名空间中的方法定制相关控件的绘制方式 </td>
    </tr>
</table>

##用法
提供了pkgconf构建依赖,包名为kiranwidgets-qt5
- 查看kiranwidgets-qt5库依赖和头文件目录 `pkgconf --libs --cflags kiranwidgets-qt5`
- qmake中加入kiranwidgets-qt5依赖,在pro文件中加入`CONFIG+=link_pkgconfig PKGCONFIG+=kiranwidgets-qt5`
- cmake中通过`pkg_search_module(KIRAN_WIDGETS_QT5 REQUIRED kiranwidgets-qt5)`引入kiranwidgets-qt5的库依赖和头文件目录,
后续过程中通过`${KIRAN_WIDGETS_QT5_INCLUDE_DIRS}`引用kiranwidgets-qt5头文件目录,`${KIRAN_WIDGETS_QT5_LIBRARIES}`引用kiranwidgets-qt5依赖库
在代码中包含需要的控件头文件:例如```#include <kiransearchbox.h>```即可使用
