# kiranwidgets-qt5

kiran桌面环境的相关**Qt控件**的封装

## 编译

1.  安装编译依赖  
   `sudo yum install gcc-c++ qt5-qtbase qt5-qtbase-devel libX11 libX11-devel`
2. **源码根目录**下创建**build**目录`mkdir build`
3. 进行**build**目录,执行`qmake-qt5 ..`生成**Makefile**
4. 执行`make`进行编译

## 安装

1. 在**build**目录下执行`sudo make install`

## 卸载

1. 在**build**目录下执行`sudo make uninstall`

## 使用

1. 安装**examples**，查看**/usr/share/kiranwidgets-qt5/examples/**


## 具体控件的使用

### kiran-titlebar-window

<img src="preview-images/kiran-titlebar-window.png" alt="kiran-titlebar-window" style="zoom:33%;" />

自定义标题栏窗口

#### 头文件位置

/usr/include/kiranwidgets-qt5/kiran-titlebar-window.h

#### 例子

##### KiranTitlebarWindow_UI

使用UI文件来生成界面的示例代码

##### KiranTitlebarWindow_CPP

使用代码来生成界面的示例代码

##### KiranTitlebarWindow_Simple

单纯使用面向过程,不通过派生来使用KiranTitlebarWindow
