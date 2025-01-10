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

#ifndef KIRAN_PUSH_BUTTON_PRIVATE_H
#define KIRAN_PUSH_BUTTON_PRIVATE_H

#include "kiran-push-button.h"

class KiranPushButtonPrivate
{
    Q_DECLARE_PUBLIC(KiranPushButton)
public:
    KiranPushButtonPrivate(KiranPushButton* ptr)
        : q_ptr(ptr)
    {
    }
    ~KiranPushButtonPrivate() = default;

private:
    KiranPushButton* q_ptr;
    bool m_fontUnderLineEnable = false;
};

#endif  // KIRAN_PUSH_BUTTON_PRIVATE_H