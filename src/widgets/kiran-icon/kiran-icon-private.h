/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiran-widgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     yuanxing <yuanxing@kylinsec.com.cn>
 */

#ifndef KIRANICON_PRIVATE_H
#define KIRANICON_PRIVATE_H

#include <QIcon>
#include "kiran-icon.h"

class KiranIconPrivate
{
    Q_DECLARE_PUBLIC(KiranIcon)
public:
    KiranIconPrivate(KiranIcon* ptr)
        : q_ptr(ptr)
    {
    }
    ~KiranIconPrivate() = default;

private:
    QIcon m_icon;
    KiranIcon* q_ptr;
};

#endif  // KIRAN_PUSH_BUTTON_PRIVATE_H