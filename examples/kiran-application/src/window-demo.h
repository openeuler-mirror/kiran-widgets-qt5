 /**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
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
