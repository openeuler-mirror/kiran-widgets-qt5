//
// Created by lxh on 2020/11/28.
//

#ifndef KIRANSTYLE_SWITCH_BUTTON_PRIVATE_H
#define KIRANSTYLE_SWITCH_BUTTON_PRIVATE_H

#include "kiran-switch-button.h"

class KiranSwitchButtonPrivate{
    Q_DECLARE_PUBLIC(KiranSwitchButton)
public:
    KiranSwitchButtonPrivate(KiranSwitchButton *ptr)
    :q_ptr(ptr)
    {

    }
    ~KiranSwitchButtonPrivate()=default;

private:
    KiranSwitchButton* q_ptr;
};

#endif //KIRANSTYLE_SWITCH_BUTTON_PRIVATE_H
