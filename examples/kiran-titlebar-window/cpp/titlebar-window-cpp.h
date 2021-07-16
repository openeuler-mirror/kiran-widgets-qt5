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
 
/*
 * @file   titlebar-window-cpp.h
 * @brief  通过派生使用cpp创建控件的方法来使用KiranTitlebarWindow自定义标题栏窗口的例子
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef TITLEBARWINDOWUI_H
#define TITLEBARWINDOWUI_H

#include <QWidget>

#include <kiranwidgets-qt5/kiran-titlebar-window.h>
class TitlebarWindowCPP : public KiranTitlebarWindow
{
    Q_OBJECT

public:
    explicit TitlebarWindowCPP(QWidget *parent = nullptr);
    ~TitlebarWindowCPP();

private:
    void initUI();
};

#endif // TITLEBARWINDOWUI_H
