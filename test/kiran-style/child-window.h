/*
 * @file   child-window.h
 * @brief  测试KiranTitlebarWindow参数的控件
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_CHILD_WINDOW_H
#define KIRANWIDGETS_QT5_CHILD_WINDOW_H

#include "kiran-titlebar-window.h"
class ChildWindow : public KiranTitlebarWindow {
    Q_OBJECT
public:
    explicit ChildWindow(QWidget* widget);
    ~ChildWindow();

    virtual QSize sizeHint() const override;
};


#endif //KIRANWIDGETS_QT5_CHILD_WINDOW_H
