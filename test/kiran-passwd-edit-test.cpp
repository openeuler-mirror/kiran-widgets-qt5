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

#include "kiran-passwd-edit/kiran-passwd-edit.h"

#include <QEventLoop>
#include <QLineEdit>
#include <QTest>
#include <QWindow>

class KiranPasswdEditTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        passwdEdit = new KiranPasswdEdit;
        passwdEdit->resize(500, 200);
        passwdEdit->show();
        QTest::qWaitForWindowExposed(passwdEdit);
    }

    void testClearButton()
    {
        passwdEdit->lineEdit()->setText("test clean button....");
        passwdEdit->setClearButtonEnabled(true);
        QTest::qWait(1000);
        passwdEdit->setClearButtonEnabled(false);
        QTest::qWait(1000);
        passwdEdit->lineEdit()->clear();
    }

    void testEchoModeButton()
    {
        passwdEdit->lineEdit()->setText("test text....");
        passwdEdit->setEchoMode(QLineEdit::Normal);
        QTest::qWait(1000);
        passwdEdit->lineEdit()->clear();
        QTest::qWait(1000);
    }

    void cleanupTestCase()
    {
        passwdEdit->hide();
        delete passwdEdit;
    }

private:
    KiranPasswdEdit* passwdEdit;
};

QTEST_MAIN(KiranPasswdEditTest)
#include "kiran-passwd-edit-test.moc"