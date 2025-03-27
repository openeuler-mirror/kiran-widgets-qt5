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

#pragma once

#include <QObject>
#include "kiran-line-edit.h"

class QLineEdit;
class QHBoxLayout;
class KiranLineEditPrivate : public QObject
{
    Q_OBJECT
public:
    KiranLineEditPrivate(QObject* parent = nullptr);
    ~KiranLineEditPrivate();

private:
    void init();
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    KiranLineEdit* q_ptr;
    Q_DECLARE_PUBLIC(KiranLineEdit)
    QHBoxLayout* m_layout;
    QLineEdit* m_lineEdit;

    bool m_isAlert = false;
    KiranLineEdit::TipsPosition m_tipsPosition = KiranLineEdit::TIPS_POSITION_BOTTOM;
};
