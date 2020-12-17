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
