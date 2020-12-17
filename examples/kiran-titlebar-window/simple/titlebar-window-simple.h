/*
 * @file   titlebar-window-simple.h
 * @brief  通过直接设置内容窗口的方法来使用KiranTitlebarWindow自定义标题栏窗口的例子
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef TITLEBARWINDOWSIMPLE_H
#define TITLEBARWINDOWSIMPLE_H

#include <QWidget>

namespace Ui {
class TitlebarWindowSimple;
}

class TitlebarWindowSimple : public QWidget
{
    Q_OBJECT

public:
    explicit TitlebarWindowSimple(QWidget *parent = nullptr);
    ~TitlebarWindowSimple();

private:
    Ui::TitlebarWindowSimple *ui;
};

#endif // TITLEBARWINDOWSIMPLE_H
