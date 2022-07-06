#pragma once

#include <QObject>
#include "kiran-line-edit.h"

class QLineEdit;
class QHBoxLayout;
class KiranLineEditPrivate : public QObject
{
    Q_OBJECT
public:
    KiranLineEditPrivate(QObject* parent = nullptr);
    ~KiranLineEditPrivate();

private:
    void init();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranLineEdit* q_ptr;
    Q_DECLARE_PUBLIC(KiranLineEdit)
    QHBoxLayout* m_layout;
    QLineEdit* m_lineEdit;

    bool m_isAlert = false;
    KiranLineEdit::TipsPosition m_tipsPosition = KiranLineEdit::TIPS_POSITION_BOTTOM;
};
