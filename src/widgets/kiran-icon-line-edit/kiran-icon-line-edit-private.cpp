//
// Created by lxh on 2020/12/25.
//

#include "kiran-icon-line-edit-private.h"

KiranIconLineEditPrivate::KiranIconLineEditPrivate(QObject *parent)
    : QObject(parent)
{

}

KiranIconLineEditPrivate::~KiranIconLineEditPrivate()
{

}

void KiranIconLineEditPrivate::init(KiranIconLineEdit* ptr)
{
    q_ptr = ptr;
}
