//
// Created by lxh on 2020/12/12.
//

#include "kiran-spin-box-private.h"

KiranSpinBoxPrivate::KiranSpinBoxPrivate(QObject *parent)
    : QObject(parent)
{

}

KiranSpinBoxPrivate::~KiranSpinBoxPrivate()
{

}

void KiranSpinBoxPrivate::init(KiranSpinBox *ptr)
{
    q_ptr = ptr;
}
