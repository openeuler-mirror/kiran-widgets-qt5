//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SPIN_BOX_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_SPIN_BOX_PRIVATE_H


#include "kiran-spin-box.h"

class KiranSpinBoxPrivate : public QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranSpinBox)
public:
    KiranSpinBoxPrivate(QObject* parent= nullptr);
    ~KiranSpinBoxPrivate();

    void init(KiranSpinBox* ptr);

private:
    KiranSpinBox* q_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SPIN_BOX_PRIVATE_H
