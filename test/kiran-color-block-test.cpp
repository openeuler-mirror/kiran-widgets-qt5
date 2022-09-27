
#include "kiran-color-block/kiran-color-block.h"
#include <style-palette.h>
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

    void testSetAndGetDrawBackground()
    {
        colorBlock->setDrawBackground(true);
        QCOMPARE(colorBlock->getDrawBackground(), true);
        QTest::qWait(500);
        colorBlock->setDrawBackground(false);
        QCOMPARE(colorBlock->getDrawBackground(), false);
        QTest::qWait(500);
    }

    void testSetFixedBackgroundState()
    {
        colorBlock->setFixedBackgroundState(Kiran::StylePalette::Normal);
        QTest::qWait(500);
        colorBlock->setFixedBackgroundState(Kiran::StylePalette::Disabled);
        QTest::qWait(500);
    }

    void testUnsetFixedBackgroundState()
    {
        colorBlock->unsetFixedBackgroundState();
    }

private:
    KiranColorBlock *colorBlock;
};

QTEST_MAIN(KiranColorBlockTest)
#include "kiran-color-block-test.moc"