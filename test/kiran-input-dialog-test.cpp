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
#include "kiran-input-dialog/kiran-input-dialog.h"
#include <QPushButton>
#include <QTest>
#include <QTimer>

class KiranInputDialogTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
    }

    void testNormal()
    {
        QScopedPointer<KiranInputDialog> dialog(new KiranInputDialog());
        dialog->setTitle("Normal Test");
        dialog->setDesc("Please enter content");
        dialog->setPlaceholderText("Please enter");
        dialog->setInputMode(QLineEdit::Normal, 20);

        QTimer::singleShot(2000, [&dialog]()
                           {
                               QLineEdit* edit = dialog->findChild<QLineEdit*>();
                               QVERIFY(edit != nullptr);
                               QTest::keyClicks(edit, "TestUser");

                               QPushButton* btn = dialog->findChild<QPushButton*>("ConfirmButton");
                               QVERIFY(btn != nullptr);
                               QTest::mouseClick(btn, Qt::LeftButton);
                           });

        auto bRes = dialog->exec();
        QVERIFY(bRes == true);

        QString input = dialog->getUserInput();
        QTest::qWait(200);
    }

    void testCancel()
    {
        QScopedPointer<KiranInputDialog> dialog(new KiranInputDialog());
        dialog->setTitle("Cancel Test");
        dialog->setDesc("Please enter content");
        dialog->setPlaceholderText("Please enter");
        dialog->setInputMode(QLineEdit::Normal, 20);
        dialog->clearInput();

        QTimer::singleShot(2000, [&dialog]()
                           {
                               QPushButton* btn = dialog->findChild<QPushButton*>("CancelButton");
                               QVERIFY(btn != nullptr);
                               QTest::mouseClick(btn, Qt::LeftButton);
                           });

        auto bRes = dialog->exec();
        QVERIFY(bRes == false);

        QString input = dialog->getUserInput();
        QTest::qWait(200);
    }

    void testLongDesc()
    {
        QString longDesc = QString("This is a very long description. ").repeated(10);

        QScopedPointer<KiranInputDialog> dialog(new KiranInputDialog());
        dialog->setTitle("Long Desc Test");
        dialog->setDesc(longDesc);
        dialog->setPlaceholderText("Please enter");
        dialog->setInputMode(QLineEdit::Normal, 20);

        QTimer::singleShot(2000, [&dialog]() {
            QLineEdit* edit = dialog->findChild<QLineEdit*>();
            QVERIFY(edit != nullptr);
            QTest::keyClicks(edit, "LongDescUser");

            QPushButton* btn = dialog->findChild<QPushButton*>("ConfirmButton");
            QVERIFY(btn != nullptr);
            QTest::mouseClick(btn, Qt::LeftButton);
        });

        auto bRes = dialog->exec();
        QVERIFY(bRes == true);

        QString input = dialog->getUserInput();
        QTest::qWait(2000);
    }

    void testLongPlaceholder()
    {
        QString longPlaceholder = QString("This is a very long placeholder. ").repeated(10);

        QScopedPointer<KiranInputDialog> dialog(new KiranInputDialog());
        dialog->setTitle("Long Placeholder Test");
        dialog->setDesc("Please enter content");
        dialog->setPlaceholderText(longPlaceholder);
        dialog->setInputMode(QLineEdit::Normal, 20);

        QTimer::singleShot(2000, [&dialog]() {
            QLineEdit* edit = dialog->findChild<QLineEdit*>();
            QVERIFY(edit != nullptr);
            QTest::keyClicks(edit, "LongPlaceholderUser");

            QPushButton* btn = dialog->findChild<QPushButton*>("ConfirmButton");
            QVERIFY(btn != nullptr);
            QTest::mouseClick(btn, Qt::LeftButton);
        });

        auto bRes = dialog->exec();
        QVERIFY(bRes == true);

        QString input = dialog->getUserInput();
        QTest::qWait(200);
    }

    void testPasswdMode()
    {
        const QString& passwdExample = "!@#$%^&*()_+-=~`[]{}|;:',.<>?/!@#$%^&*()_+-=~`[]{}|;:',.<>?/!@#$%^&*()_+";
        
        QScopedPointer<KiranInputDialog> dialog(new KiranInputDialog());
        dialog->setTitle("Password Mode Test");
        dialog->setDesc("Please enter password");
        dialog->setPlaceholderText("Please enter");
        dialog->setInputMode(QLineEdit::Password, 20);

        QTimer::singleShot(2000, [&dialog, &passwdExample]()
                           {
                               QLineEdit* edit = dialog->findChild<QLineEdit*>();
                               QVERIFY(edit != nullptr);
                               QTest::keyClicks(edit, passwdExample);

                               QPushButton* btn = dialog->findChild<QPushButton*>("ConfirmButton");
                               QVERIFY(btn != nullptr);
                               QTest::mouseClick(btn, Qt::LeftButton);
                           });

        auto bRes = dialog->exec();
        QVERIFY(bRes == true);

        QString input = dialog->getUserInput();
        QVERIFY(passwdExample.left(20) == input);
        
        QTest::qWait(200);
    }
};
QTEST_MAIN(KiranInputDialogTest)
#include "kiran-input-dialog-test.moc"