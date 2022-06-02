#pragma once

#include <QWidget>
#include <QLineEdit>

/**
 * Todo:后续完成该部分功能，替换掉已失效的KiranIconLineEdit
 * 将会包含KiranIconLineEdit的功能
 */
class KiranLineEditPrivate;
class KiranLineEdit : public QWidget
{
    Q_OBJECT
public:
    enum TipsType
    {
        TIPS_INFO,
        TIPS_WARNING
    };
    enum TipsPosition
    {
        TIPS_POSITION_TOP,
        TIPS_POSITION_BOTTOM,
        TIPS_POSITION_LEFT,
        TIPS_POSITION_RIGHT
    };
public:
    explicit KiranLineEdit(QWidget* parent = nullptr);
    ~KiranLineEdit();

    QLineEdit* lineEdit() const;

    void setAlert(bool alert);
    bool getAlert() const;

    void setTipsPosition(TipsPosition position);
    TipsPosition getTipsPosition() const;

    void showTips(TipsType type,const QString& text,int duration=2000);
    void hideTips();

    void setText(const QString& text);
    const QString& text();
    void clean();

    QLineEdit::EchoMode echoMode() const;
    void setEchoMode(QLineEdit::EchoMode mode);

    void setContextMenuPolicy(Qt::ContextMenuPolicy policy);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void alertChanged(bool alert) const;
    void focusChanged(bool onFocus) const;
    void textChanged(const QString &);
    void textEdited(const QString &);
    void cursorPositionChanged(int, int);
    void returnPressed();
    void editingFinished();
    void selectionChanged();

private:
    KiranLineEditPrivate* d_ptr;
    Q_DECLARE_PRIVATE(KiranLineEdit);
};
