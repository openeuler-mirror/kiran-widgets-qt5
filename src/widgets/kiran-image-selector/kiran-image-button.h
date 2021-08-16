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
 
#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H

#include <QPushButton>

/**
 * @brief KiranImageSelector的两侧悬浮按钮
 *       在KiranStyle中的QPushButton绘制过程中单独通过Inherits进行特殊绘制
 */
class KiranImageButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(bool anchorParentLeftSide READ anchorParentLeftSide);
public:
    explicit KiranImageButton(QWidget *parent,bool leftSide );
    virtual ~KiranImageButton();
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    bool anchorParentLeftSide();
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    bool m_anchorParentLeftSide = false;
};


#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H
