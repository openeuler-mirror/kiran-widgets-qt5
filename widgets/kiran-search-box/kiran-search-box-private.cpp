//
// Created by lxh on 2020/12/9.
//

#include "kiran-search-box-private.h"

#include <QLineEdit>
#include <QHBoxLayout>

KiranSearchBoxPrivate::KiranSearchBoxPrivate(QObject* parent)
    :QObject(parent)
{

}

KiranSearchBoxPrivate::~KiranSearchBoxPrivate()
{

}

void KiranSearchBoxPrivate::init(KiranSearchBox* ptr)
{
    q_ptr = ptr;

    m_hBoxLayout = new QHBoxLayout(q_ptr);
    m_hBoxLayout->setContentsMargins(0,0,0,0);

    m_edit = new QLineEdit(q_ptr);
    m_edit->installEventFilter(q_ptr);
    m_edit->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    m_hBoxLayout->addWidget(m_edit,0,Qt::AlignVCenter);
}

void KiranSearchBoxPrivate::adjustMargins()
{
    QSize searchBoxSize = q_ptr->size();
    QMargins layoutMargins = q_ptr->layout()->contentsMargins();

    if( layoutMargins.left()!=searchBoxSize.height() ){
        layoutMargins.setLeft(searchBoxSize.height());
        q_ptr->layout()->setContentsMargins(layoutMargins);
    }
}
