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

#include "kiran-label/kiran-label.h"

#include <QEventLoop>
#include <QLineEdit>
#include <QTest>
#include <QWindow>

#define TEST_TEXT_1 "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend." \
                    "hello, my friend."

#define TEST_TEXT_2 "wow!!!!" \
                    "wow!!!!" \
                    "wow!!!!" \
                    "wow!!!!" \
                    "wow!!!!" \
                    "wow!!!!" \
                    "wow!!!!"

class KiranLabelTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        kiranLabel = new KiranLabel;
        kiranLabel->resize(500, 200);
        kiranLabel->show();
        QTest::qWaitForWindowExposed(kiranLabel);
    }

    void testElideRight()
    {
        kiranLabel->resize(500, 200);
        kiranLabel->setText(TEST_TEXT_1);
        kiranLabel->setElideMode(Qt::ElideRight);
        QTest::qWait(1000);
        kiranLabel->resize(200, 200);
        QTest::qWait(1000);
        kiranLabel->setText(TEST_TEXT_2);
        QTest::qWait(1000);
    }

    void testElideLeft()
    {
        kiranLabel->resize(500, 200);
        kiranLabel->setText(TEST_TEXT_1);
        kiranLabel->setElideMode(Qt::ElideLeft);
        QTest::qWait(1000);
        kiranLabel->resize(200, 200);
        QTest::qWait(1000);
        kiranLabel->setText(TEST_TEXT_2);
        QTest::qWait(1000);
    }

    void testElideMiddle()
    {
        kiranLabel->resize(500, 200);
        kiranLabel->setText(TEST_TEXT_1);
        kiranLabel->setElideMode(Qt::ElideMiddle);
        QTest::qWait(1000);
        kiranLabel->resize(200, 200);
        QTest::qWait(1000);
        kiranLabel->setText(TEST_TEXT_2);
        QTest::qWait(1000);
    }

    void cleanupTestCase()
    {
        kiranLabel->hide();
        delete kiranLabel;
    }

private:
    KiranLabel* kiranLabel;
};

QTEST_MAIN(KiranLabelTest)
#include "kiran-label-test.moc"