#include <QTest>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include "kiran-application/kiran-application.h"

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