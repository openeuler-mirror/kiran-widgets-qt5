#include "kiran-label/kiran-label.h"

#include <QTest>
#include <QWindow>
#include <QEventLoop>
#include <QLineEdit>

#define TEST_TEXT_1 "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."\
                    "hello, my friend."


#define TEST_TEXT_2 "wow!!!!"\
                    "wow!!!!"\
                    "wow!!!!"\
                    "wow!!!!"\
                    "wow!!!!"\
                    "wow!!!!"\
                    "wow!!!!"\

class KiranLabelTest: public QObject
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