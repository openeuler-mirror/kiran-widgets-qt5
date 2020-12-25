//
// Created by lxh on 2020/12/15.
//

#include "kiran-siderbar-widget-private.h"
#include <QDebug>

KiranSidebarWidgetPrivate::KiranSidebarWidgetPrivate(QObject *parent)
    : QObject(parent)
{

}

KiranSidebarWidgetPrivate::~KiranSidebarWidgetPrivate()
{

}

void KiranSidebarWidgetPrivate::init(KiranSidebarWidget* ptr)
{
    q_ptr = ptr;
    qInfo() << __FUNCTION__  << "setSpacing";
    q_ptr->setSpacing(12);
    q_ptr->setSelectionBehavior(QListView::SelectRows);
    q_ptr->setSelectionMode(QListView::SingleSelection);
}
