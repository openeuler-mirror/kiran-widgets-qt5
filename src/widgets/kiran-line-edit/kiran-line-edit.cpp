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

#include "kiran-line-edit.h"
#include <palette.h>
#include "kiran-line-edit-private.h"

using namespace Kiran::Theme;

KiranLineEdit::KiranLineEdit(QWidget *parent)
    : QWidget(parent)
{
    d_ptr = new KiranLineEditPrivate();
    d_ptr->q_ptr = this;
    d_ptr->init();

    setAccessibleName("KiranLineEdit");
}

KiranLineEdit::~KiranLineEdit()
{
    delete d_ptr;
}

QLineEdit *KiranLineEdit::lineEdit() const
{
    return d_func()->m_lineEdit;
}

void KiranLineEdit::setAlert(bool alert)
{
    Q_D(KiranLineEdit);
    if (alert == d->m_isAlert)
    {
        return;
    }

    d->m_isAlert = alert;
    update();
}

bool KiranLineEdit::getAlert() const
{
    return d_func()->m_isAlert;
}

void KiranLineEdit::setTipsPosition(TipsPosition position)
{
    Q_D(KiranLineEdit);

    if (position == d->m_tipsPosition)
    {
        return;
    }

    d->m_tipsPosition = position;
}

KiranLineEdit::TipsPosition KiranLineEdit::getTipsPosition() const
{
    return d_func()->m_tipsPosition;
}

void KiranLineEdit::paintEvent(QPaintEvent *event)
{
    DEFAULT_PALETTE();
    QWidget::paintEvent(event);
}

QSize KiranLineEdit::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize KiranLineEdit::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}
