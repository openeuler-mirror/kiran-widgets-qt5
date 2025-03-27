/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */

#ifndef KIRAN_BACKGROUND_WIDGET_PRIVATE_H
#define KIRAN_BACKGROUND_WIDGET_PRIVATE_H

#include "kiran-color-block.h"

class KiranColorBlockPrivate
{
public:
    KiranColorBlockPrivate(KiranColorBlock* ptr) : q_ptr(ptr) {}

private:
    KiranColorBlock* q_ptr;
    Q_DECLARE_PUBLIC(KiranColorBlock)

    int m_radius = 6;
    bool m_drawBackground = true;
    KiranColorBlock::Corner m_radiusCorner = KiranColorBlock::AllCorners;
    QColor m_normalColor;
    QColor m_hoverColor;
};

#endif  // KIRAN_BACKGROUND_WIDGET_PRIVATE_H
