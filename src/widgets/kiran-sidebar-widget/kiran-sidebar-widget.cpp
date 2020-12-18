//
// Created by lxh on 2020/12/15.
//

#include "kiran-sidebar-widget.h"
#include "kiran-siderbar-widget-private.h"

#include <QEvent>
#include <QMouseEvent>

KiranSidebarWidget::KiranSidebarWidget(QWidget *parent)
    : QListWidget(parent),
      d_ptr(new KiranSidebarWidgetPrivate(this))
{
    d_ptr->init(this);
}

KiranSidebarWidget::~KiranSidebarWidget()
{

}

QItemSelectionModel::SelectionFlags
KiranSidebarWidget::selectionCommand(const QModelIndex &index, const QEvent *event) const
{
//    //NOTE:为了避免一些环境下会出现ItemFocus直接设置选中的情况
    if(event==nullptr){
        return QItemSelectionModel::NoUpdate;
    }
    //禁用用户按住鼠标切换用户情况
    if(event->type()==QEvent::MouseMove){
        return QItemSelectionModel::NoUpdate;
    }
    if( (event!=nullptr) && (event->type()==QEvent::MouseButtonPress) ){
        const QMouseEvent* mouseEvent = (QMouseEvent*) event;
        if( (mouseEvent->modifiers()&Qt::ControlModifier)!=0 ){
            return QItemSelectionModel::NoUpdate;
        }
    }
    return QListWidget::selectionCommand(index,event);
}
