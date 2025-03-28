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

#include "kiran-line-edit-private.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QLineEdit>

KiranLineEditPrivate::KiranLineEditPrivate(QObject *parent)
    : QObject(parent),
      q_ptr(nullptr),
      m_lineEdit(nullptr),
      m_layout(nullptr)
{
}

KiranLineEditPrivate::~KiranLineEditPrivate()
{
}

void KiranLineEditPrivate::init()
{
    m_layout = new QHBoxLayout(q_ptr);
    m_layout->setContentsMargins(1, 1, 1, 1);
    m_layout->setSpacing(0);

    m_lineEdit = new QLineEdit(q_ptr);
    m_lineEdit->setFrame(false);
    q_ptr->setFocusProxy(m_lineEdit);

    m_layout->addWidget(m_lineEdit);
}

bool KiranLineEditPrivate::eventFilter(QObject *watched, QEvent *event)
{
    return QObject::eventFilter(watched, event);
}
