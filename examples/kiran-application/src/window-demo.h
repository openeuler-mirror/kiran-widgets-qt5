/*
 * @file   window-demo.h
 * @brief  KiranApplication实例
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */

#ifndef KIRANWIDGETS_QT5_WINDOW_DEMO_H
#define KIRANWIDGETS_QT5_WINDOW_DEMO_H

#include <kiran-titlebar-window.h>

class QLabel;
class WindowDemo : public KiranTitlebarWindow{
    Q_OBJECT
public:
    explicit WindowDemo();
    ~WindowDemo();

private:
    void initUI();
    void updateSpecialFont();

public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QLabel* m_normalLabel = nullptr;
    QLabel* m_specialLabel = nullptr;
};


#endif //KIRANWIDGETS_QT5_WINDOW_DEMO_H
