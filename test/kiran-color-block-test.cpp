
#include "kiran-color-block/kiran-color-block.h"
#include <QTest>

class KiranColorBlockTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        colorBlock = new KiranColorBlock;
        colorBlock->show();
    }

    void cleanupTestCase()
    {
        delete colorBlock;
    }

    void testSetAndGetRadius()
    {
        QList<int> radiusList = {0, 20, 50, 80, 100};
        for (auto radius : radiusList)
        {
            colorBlock->setRadius(radius);
            QCOMPARE(colorBlock->getRadius(), radius);
            QTest::qWait(500);
        }
    }

private:
    KiranColorBlock *colorBlock;
};

QTEST_MAIN(KiranColorBlockTest)
#include "kiran-color-block-test.moc"