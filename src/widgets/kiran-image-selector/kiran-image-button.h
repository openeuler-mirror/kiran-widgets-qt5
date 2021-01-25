/**
 *@file  kiran-image-button.h
 *@brief 
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
 */
#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H

#include <QPushButton>

class KiranImageButton : public QPushButton {
Q_OBJECT
public:
    enum AnchorPosition {
        Anchor_Left,
        Anchor_Right
    };
    explicit KiranImageButton(QWidget *parent, AnchorPosition position);
    virtual ~KiranImageButton();
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
private:
    AnchorPosition m_anchorPosition;
};


#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H
