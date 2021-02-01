/**
 *@file  kiran-image-button.h
 *@brief 
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
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
