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

#include "kiran-search-box-private.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>

#include "kiran-icon/kiran-icon.h"

KiranSearchBoxPrivate::KiranSearchBoxPrivate(QObject* parent)
    : QObject(parent)
{
}

KiranSearchBoxPrivate::~KiranSearchBoxPrivate()
{
}

void KiranSearchBoxPrivate::init(KiranSearchBox* ptr)
{
    q_ptr = ptr;

    auto layout = new QHBoxLayout(q_ptr);
    m_searchIcon = new KiranIcon(q_ptr);
    m_searchIcon->setFixedSize(16, 16);
    m_searchIcon->setIcon(QIcon::fromTheme("ksvg-search"));

    layout->addWidget(m_searchIcon, 0, Qt::AlignLeft | Qt::AlignVCenter);

    q_ptr->setTextMargins(24, 0, 0, 0);
}
