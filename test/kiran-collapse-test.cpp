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
#include "kiran-collapse/kiran-collapse.h"
#include <QListWidget>
#include <QScrollBar>
#include <QStyledItemDelegate>
#include <QTest>
#include <QVBoxLayout>
#include <QWidget>

class ViewportSizeListWidget : public QListWidget
{
public:
    ViewportSizeListWidget(QWidget* parent = nullptr) : QListWidget(parent) {}

    // 重写sizeHint方法，倾向于所有项全部显示
    QSize sizeHint() const override
    {
        QSize sz = QListView::sizeHint();
        if (model())
        {
            int rows = model()->rowCount();
            int h = 0;
            for (int r = 0; r < rows; ++r)
            {
                h += sizeHintForRow(r);
            }
            sz.setHeight(h);
        }
        return sz;
    }
};

class KiranCollapseTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        m_window = new QWidget();

        auto windowLayout = new QVBoxLayout(m_window);
        windowLayout->setContentsMargins(0, 0, 0, 0);
        windowLayout->setSpacing(0);

        m_collapse = new KiranCollapse(m_window);
        m_collapse->setTopBarFixedHeight(46);
        m_collapse->setTitle("Test Collapse");
        windowLayout->addWidget(m_collapse);

        // 使用自定义的ViewportSizeListWidget替代QListWidget
        m_contentListWidget = new ViewportSizeListWidget();
        m_contentListWidget->setUniformItemSizes(true);
        m_contentListWidget->setFrameShape(QFrame::NoFrame);
        m_contentListWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        m_collapse->addExpansionSpaceWidget(m_contentListWidget);

        m_window->resize(300, 600);
        m_window->show();
    }

    void testNormal()
    {
        // 添加100项
        for (int i = 0; i < 100; ++i)
        {
            m_contentListWidget->addItem(QString("Item %1").arg(i));
        }
        
        // 设置拓展区域最大高度500px
        m_collapse->setFixMaxExpansionHeight(500);
        auto collapseHeight = m_collapse->sizeHint().height();

        // 确认展开尺寸
        m_collapse->setExpand();
        QTest::qWait(200);
        QVERIFY(m_collapse->sizeHint().height() == (collapseHeight+500));

        // 确认折叠尺寸
        m_collapse->setCollapse();
        QTest::qWait(200);
        QVERIFY(m_collapse->sizeHint().height() == collapseHeight);

        // 折叠状态更新拓展区域大小，应保持高度不变
        m_collapse->setFixMaxExpansionHeight(200);
        QTest::qWait(200);
        QVERIFY(m_collapse->sizeHint().height() == collapseHeight);

        // 展开时应更新最大高度
        m_collapse->setExpand();
        QTest::qWait(200);
        QVERIFY(m_collapse->sizeHint().height() == (collapseHeight+200));
    }

private:
    QWidget* m_window = nullptr;
    KiranCollapse* m_collapse = nullptr;
    QListWidget* m_contentListWidget = nullptr;
};

QTEST_MAIN(KiranCollapseTest)
#include "kiran-collapse-test.moc"
