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

#include "kiran-push-button.h"
#include "kiran-push-button-private.h"

#include <QPushButton>
#include <QStyleOptionButton>
#include <QStylePainter>

#define KIRAN_STYLE_PROPERTY_BUTTON_TYPE "_kiran_button_type"
KiranPushButton::KiranPushButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new KiranPushButtonPrivate(this))
{
}

KiranPushButton::KiranPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent),
      d_ptr(new KiranPushButtonPrivate(this))
{
}

KiranPushButton::~KiranPushButton()
{
    delete d_ptr;
}

bool KiranPushButton::fontUnderLine()
{
    return d_ptr->m_fontUnderLineEnable;
}

void KiranPushButton::setFontUnderLine(bool enable)
{
    if (KiranPushButton::fontUnderLine() == enable)
    {
        return;
    }

    d_ptr->m_fontUnderLineEnable = enable;
    update();
}

KiranPushButton::ButtonType KiranPushButton::getButtonType(const QPushButton *btn)
{
    KiranPushButton::ButtonType buttonType = KiranPushButton::BUTTON_Normal;

    if (btn)
    {
        QVariant var = btn->property(KIRAN_STYLE_PROPERTY_BUTTON_TYPE);
        if (var.isValid())
        {
            bool toInt = false;
            auto temp = static_cast<KiranPushButton::ButtonType>(var.toInt(&toInt));
            if (toInt)
            {
                buttonType = temp;
            }
        }
    }

    return buttonType;
}

void KiranPushButton::setButtonType(QPushButton *btn, KiranPushButton::ButtonType type)
{
    btn->setProperty(KIRAN_STYLE_PROPERTY_BUTTON_TYPE, type);
}

void KiranPushButton::paintEvent(QPaintEvent *event)
{
    QStylePainter p(this);
    QStyleOptionButton option;

    // 不设置font进入QWidget之中，避免影响后续字体变更的功能
    auto tempfont = p.font();
    tempfont.setUnderline(d_ptr->m_fontUnderLineEnable);
    p.setFont(tempfont);

    initStyleOption(&option);
    p.drawControl(QStyle::CE_PushButton, option);
}
