//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_PRIVATE_H

#include "kiran-push-button.h"

class KiranPushButtonPrivate : public QObject {
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranPushButton)
public:
    KiranPushButtonPrivate(QObject* parent = nullptr);
    ~KiranPushButtonPrivate();

    void init(KiranPushButton* ptr);

private:
    KiranPushButton* q_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_PRIVATE_H
