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

    void testSpecifyColor()
    {
        QColor normalColor(Qt::red);
        QColor hoverColor(Qt::blue);
        colorBlock->setAttribute(Qt::WA_Hover);
        colorBlock->specifyColor(normalColor, hoverColor);
        QTest::qWait(2000);

        colorBlock->specifyColor(normalColor, QColor());
        QTest::qWait(2000);

        colorBlock->unsetSpecifiedColor();
        QTest::qWait(2000);
    }

private:
    KiranColorBlock *colorBlock;
};

QTEST_MAIN(KiranColorBlockTest)
#include "kiran-color-block-test.moc"