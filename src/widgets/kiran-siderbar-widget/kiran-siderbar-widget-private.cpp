//
// Created by lxh on 2020/12/15.
//

#include "kiran-siderbar-widget-private.h"

KiranSiderbarWidgetPrivate::KiranSiderbarWidgetPrivate(QObject *parent)
    : QObject(parent)
{

}

KiranSiderbarWidgetPrivate::~KiranSiderbarWidgetPrivate()
{

}

void KiranSiderbarWidgetPrivate::init(KiranSiderbarWidget* ptr)
{
    q_ptr = ptr;

    q_ptr->setSpacing(12);
    q_ptr->setSelectionBehavior(QListView::SelectRows);
    q_ptr->setSelectionMode(QListView::SingleSelection);
}
