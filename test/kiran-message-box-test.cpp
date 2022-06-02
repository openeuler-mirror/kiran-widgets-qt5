#include <QTest>
#include <QPushButton>
#include "kiran-message-box/kiran-message-box.h"

// ExecCloseHelper: Closes a modal QDialog during its exec() function by either
// sending a key event or closing it (CloseWindow) once it becomes the active
// modal window. Pass nullptr to "autodetect" the instance for static methods.
class ExecCloseHelper : public QObject
{
public:
    enum { CloseWindow = -1 };

    explicit ExecCloseHelper(QObject *parent = nullptr)
        : QObject(parent), m_key(0), m_timerId(0), m_testCandidate(nullptr) { }

    void start(int key,int interval=50, QWidget *testCandidate = nullptr)
    {
        m_key = key;
        m_testCandidate = testCandidate;
        m_timerId = startTimer(interval);
    }

    bool done() const { return !m_timerId; }

protected:
    void timerEvent(QTimerEvent *te) override;

private:
    int m_key;
    int m_timerId;
    QWidget *m_testCandidate;
};

void ExecCloseHelper::timerEvent(QTimerEvent *te)
{
    if (te->timerId() != m_timerId)
        return;

    QWidget *modalWidget = QApplication::activeModalWidget();

    if (!m_testCandidate && modalWidget)
        m_testCandidate = modalWidget;

    if (m_testCandidate && m_testCandidate == modalWidget) {
        if (m_key == CloseWindow) {
            m_testCandidate->close();
        } else {
            QKeyEvent *ke = new QKeyEvent(QEvent::KeyPress, m_key, Qt::NoModifier);
            QCoreApplication::postEvent(m_testCandidate, ke);
        }
        m_testCandidate = nullptr;
        killTimer(m_timerId);
        m_timerId = m_key = 0;
    }
}


class KiranMessageBoxTest: public QObject
{
    Q_OBJECT
private slots:
    void testDialog()
    {
        KiranMessageBox messageBox;
        messageBox.setText("测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，"
                           "测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本，测试文本");
        messageBox.setTitle("测试");

        QPushButton btn_ok;
        btn_ok.setText("Ok");

        QPushButton btn_cancel;
        btn_cancel.setText("Cancel");

        messageBox.addButton(&btn_ok,QDialogButtonBox::AcceptRole);
        messageBox.addButton(&btn_cancel,QDialogButtonBox::RejectRole);

        ExecCloseHelper closeHelper;
//        closeHelper.start(ExecCloseHelper::CloseWindow,2000,&messageBox);
        messageBox.exec();
        QVERIFY(true);
    }
};

QTEST_MAIN(KiranMessageBoxTest)
#include "kiran-message-box-test.moc"