//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SPIN_BOX_H
#define KIRANWIDGETS_QT5_KIRAN_SPIN_BOX_H

#include <QSpinBox>
#include <kiran-public-define.h>

class KiranSpinBoxPrivate;
class Q_DECL_EXPORT KiranSpinBox : public QSpinBox{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSpinBox)
public:
    explicit KiranSpinBox(QWidget *parent = nullptr);
    ~KiranSpinBox();

    void setSpinboxArrowPosition(Kiran::SpinboxArrowPosition arrowPosition);
    Kiran::SpinboxArrowPosition getSpinboxArrowPosition();

protected:
    //NOTE:预留，考虑到之后可能会需要
    bool event(QEvent *event) override;

private:
    KiranSpinBoxPrivate* d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SPIN_BOX_H
