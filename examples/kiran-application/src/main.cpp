 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd. 
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */
 

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