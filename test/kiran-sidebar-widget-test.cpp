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

#include "kiran-sidebar-widget/kiran-sidebar-widget.h"

#include <QTest>

class KiranSidebarWidgetTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        sidebarWidget = new KiranSidebarWidget;
        sidebarWidget->resize(200, 500);
        sidebarWidget->show();
        QTest::qWaitForWindowExposed(sidebarWidget);
    }
    void testCase1()
    {
        for (int i = 0; i < 10; i++)
        {
            sidebarWidget->addItem(QString("TestTestTest%1").arg(i));
            auto item = sidebarWidget->item(sidebarWidget->count() - 1);
            item->setIcon(QIcon("/usr/share/kiran-cpanel-account/account-icons/0.face"));
            QTest::qWait(500);
        }
    }
    void cleanupTestCase()
    {
    }

private:
    KiranSidebarWidget* sidebarWidget;
};

QTEST_MAIN(KiranSidebarWidgetTest)
#include "kiran-sidebar-widget-test.moc"