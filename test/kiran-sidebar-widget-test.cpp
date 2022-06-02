#include "kiran-sidebar-widget/kiran-sidebar-widget.h"

#include <QTest>

class KiranSidebarWidgetTest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        sidebarWidget = new KiranSidebarWidget;
        sidebarWidget->resize(200,500);
        sidebarWidget->show();
        QTest::qWaitForWindowExposed(sidebarWidget);
    }
    void testCase1()
    {
        for(int i=0;i<10;i++)
        {
            sidebarWidget->addItem(QString("TestTestTest%1").arg(i));
            auto item = sidebarWidget->item(sidebarWidget->count()-1);
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