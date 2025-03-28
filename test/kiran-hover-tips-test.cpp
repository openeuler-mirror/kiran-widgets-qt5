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

#define private public
#include "kiran-hover-tips/kiran-hover-tips.h"
#undef private

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
#include <QWidget>

static const int default_delay = 2000;

class KiranHoverTipsTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        widget = new QWidget();
        widget->resize(400, 400);

        hovertips = new KiranHoverTips(widget);

        auto layout = new QVBoxLayout(widget);
        layout->setMargin(8);

        auto edit = new QLineEdit(widget);
        layout->addWidget(edit);

        auto label = new QLabel(widget);
        layout->addWidget(label);

        widget->show();
        QCOMPARE(QTest::qWaitForWindowExposed(widget), true);
    };

    void cleanupTestCase()
    {
        delete widget;
    };

    void case_ShowSuccessTimeout()
    {
        hovertips->setTimeout(1000);
        hovertips->showTips(KiranHoverTips::HOVE_TIPS_SUC, "这是一段测试文本，测试超时关闭是否正常");
        QTest::qWait(1000);
        QApplication::processEvents();
        QCOMPARE(hovertips->isVisible(), false);
    }

    void case_ShowSuccessNeveTimeout()
    {
        hovertips->setTimeout(0);
        hovertips->showTips(KiranHoverTips::HOVE_TIPS_SUC, "这是一段测试文本，测试点击消失是否正常");
        QTest::qWait(1000);
        QTest::mouseClick(hovertips, Qt::LeftButton);
        QApplication::processEvents();
        QCOMPARE(hovertips->isVisible(), false);
    }

    void case_ShowInfo()
    {
        hovertips->setTimeout(1500);
        hovertips->showTips(KiranHoverTips::HOVE_TIPS_INFO, "这是一段测试文本，测试显示是否正常");
        QTest::qWait(1500);
        QApplication::processEvents();
        QCOMPARE(hovertips->isVisible(), false);
    }

    void case_ShowWarning()
    {
        hovertips->setTimeout(1500);
        hovertips->showTips(KiranHoverTips::HOVE_TIPS_WARNING, "这是一段测试文本，测试显示是否正常");
        QTest::qWait(1500);
        QApplication::processEvents();
        QCOMPARE(hovertips->isVisible(), false);
    }

    void case_ShowError()
    {
        hovertips->setTimeout(1500);
        hovertips->showTips(KiranHoverTips::HOVE_TIPS_ERR, "这是一段测试文本，测试显示是否正常");
        QTest::qWait(1500);
        QApplication::processEvents();
        QCOMPARE(hovertips->isVisible(), false);
    }

private:
    QWidget* widget;
    KiranHoverTips* hovertips;
    QLineEdit* edit;
    QLabel* label;
};

QTEST_MAIN(KiranHoverTipsTest)
#include "kiran-hover-tips-test.moc"