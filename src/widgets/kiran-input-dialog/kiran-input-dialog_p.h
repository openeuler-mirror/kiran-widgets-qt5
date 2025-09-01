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
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */
#pragma once

#include "kiran-input-dialog.h"
#include <QLineEdit>
#include <QObject>

class KiranPasswdEdit;
class QLabel;
class QPushButton;

class KiranInputDialogPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranInputDialog)
public:
    KiranInputDialogPrivate(KiranInputDialog* q);
    ~KiranInputDialogPrivate();

    void initUI();
    void processTextChanged(const QString& text);
    void onConfirmClicked();
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void completed();

private:
    bool m_success;
    QLabel* m_labelDesc;
    KiranPasswdEdit* m_edit;
    QPushButton* m_confirmButton;
    KiranInputDialog* q_ptr;
};
