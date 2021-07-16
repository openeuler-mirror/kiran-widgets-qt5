 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */
 
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
