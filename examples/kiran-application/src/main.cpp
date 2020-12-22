//
// Created by lxh on 2020/12/22.
//

#include <kiran-application.h>
#include "window-demo.h"

int main(int argc,char** argv)
{
    /* 使用KiranApplication替代QApplication,集成封装的QStyle代码和桌面环境字体监控功能 */
    KiranApplication app(argc,argv);

    /* 控件特殊字号单独处理例子 */
    WindowDemo demo;
    demo.show();

    return app.exec();
}