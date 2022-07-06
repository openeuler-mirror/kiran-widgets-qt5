//
// Created by lxh on 2022/3/31.
//

#include "kiran-line-edit-private.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QEvent>

KiranLineEditPrivate::KiranLineEditPrivate(QObject *parent) : QObject(parent)
{

}

KiranLineEditPrivate::~KiranLineEditPrivate()
{

}

void KiranLineEditPrivate::init()
{
    m_layout = new QHBoxLayout(q_ptr);
    m_layout->setContentsMargins(1,1,1,1);
    m_layout->setSpacing(0);

    m_lineEdit = new QLineEdit(q_ptr);
    m_lineEdit->setFrame(false);
    q_ptr->setFocusProxy(m_lineEdit);

    m_layout->addWidget(m_lineEdit);
}

bool KiranLineEditPrivate::eventFilter(QObject *watched, QEvent *event)
{
    return QObject::eventFilter(watched, event);
}
