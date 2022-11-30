#include "kiran-passwd-edit/kiran-passwd-edit.h"

#include <QTest>
#include <QWindow>
#include <QEventLoop>
#include <QLineEdit>

class KiranPasswdEditTest: public QObject
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