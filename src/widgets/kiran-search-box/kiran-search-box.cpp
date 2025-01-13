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

#include "kiran-search-box.h"
#include "kiran-search-box-private.h"

#include <QDebug>
#include <QEvent>
#include <QLineEdit>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>

KiranSearchBox::KiranSearchBox(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new KiranSearchBoxPrivate(this))
{
    d_ptr->init(this);
}

KiranSearchBox::~KiranSearchBox()
{
}

bool KiranSearchBox::event(QEvent *event)
{
    return QLineEdit::event(event);
}

bool KiranSearchBox::eventFilter(QObject *watched, QEvent *event)
{
    return QLineEdit::eventFilter(watched, event);
}

void KiranSearchBox::paintEvent(QPaintEvent *ev)
{
    QLineEdit::paintEvent(ev);
}