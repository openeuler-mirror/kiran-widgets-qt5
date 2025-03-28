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

#include "kiran-application/kiran-application.h"
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTest>

class KiranApplicationTest : public QObject
{
    Q_OBJECT
private slots:
    void t1() { QVERIFY(true); }
};

int main(int argc, char *argv[])
{
    KiranApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);
    KiranApplicationTest tc;
    return QTest::qExec(&tc, argc, argv);
}
#include "kiran-application-test.moc"