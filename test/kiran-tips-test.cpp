#define private public
#include "kiran-tips/kiran-tips.h"
#undef private

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QTest>
#include <QWidget>

static const int default_delay = 2000;

class KiranTipsTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        widget = new QWidget();
        widget->resize(400, 400);

        tips = new KiranTips(widget);

        auto layout = new QVBoxLayout(widget);
        layout->setMargin(8);

        edit = new QLineEdit(widget);
        edit->setText("这是一个输入框");
        layout->addWidget(edit);

        label = new QLabel(widget);
        label->setText("这是一个label");
        layout->addWidget(label);

        button = new QPushButton(widget);
        button->setIcon(QIcon::fromTheme("firefox"));
        button->setText("按钮");
        layout->addWidget(button, 0, Qt::AlignCenter);

        auto spacerItem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(spacerItem);

        widget->show();
        QCOMPARE(QTest::qWaitForWindowExposed(widget), true);
    };

    void cleanupTestCase()
    {
        delete widget;
    };

    void case1_position()
    {
        tips->setText("正在测试定位");
        const QSet<KiranTips::ShowPostionHint> positionVector = {
            KiranTips::POSITION_LEFT,
            KiranTips::POSITION_RIGHT,
            KiranTips::POSITION_TOP,
            KiranTips::POSITION_BOTTM};
        foreach (auto position, positionVector)
        {
            tips->setShowPosition(position);
            tips->setBackgroundColor(QColor("pink"));
            tips->showTipAroundWidget(button);
            QTest::qWait(2000);
        }
    }

    void case2_backgroundColor()
    {
        tips->setText("正在测试背景色");
        const QVector<QColor> colors = {
            QColor("red"), QColor("orange"), QColor("blue"), QColor("green")};
        foreach (auto c, colors)
        {
            tips->setShowPosition(KiranTips::POSITION_BOTTM);
            tips->setBackgroundColor(c);
            tips->showTipAroundWidget(button);
            QTest::qWait(1500);
        }
    }

    void case3_timeout()
    {
        tips->setText("正在测试延时关闭");
        tips->setHideTimeout(1000);
        tips->showTipAroundWidget(button);
        QTest::qWait(1000);
        QApplication::processEvents();
        QCOMPARE(tips->isVisible(), false);
    }

    void case4_clickedExit()
    {
        tips->setText("正在测试点击退出");
        tips->setHideTimeout(0);
        tips->showTipAroundWidget(button);
        QTest::qWait(1000);
        QTest::mouseClick(tips, Qt::LeftButton);
        QApplication::processEvents();
        QCOMPARE(tips->isVisible(), false);
    }

private:
    QWidget* widget;
    KiranTips* tips;
    QLineEdit* edit;
    QLabel* label;
    QPushButton* button;
};

QTEST_MAIN(KiranTipsTest);
#include "kiran-tips-test.moc"