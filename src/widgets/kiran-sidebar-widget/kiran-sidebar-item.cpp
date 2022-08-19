//
// Created by lxh on 2022/4/20.
//

#include "kiran-sidebar-item.h"
#include "kiran-sidebar-define.h"

KiranSidebarItem::KiranSidebarItem(QListWidget *view, int type) : QListWidgetItem(view, type)
{

}

KiranSidebarItem::KiranSidebarItem(const QString &text, QListWidget *view, int type) : QListWidgetItem(text, view, type)
{
}

KiranSidebarItem::KiranSidebarItem(const QIcon &icon, const QString &text, QListWidget *view, int type) : QListWidgetItem(icon, text, view, type)
{
}

KiranSidebarItem::KiranSidebarItem(const QListWidgetItem &other) : QListWidgetItem(other)
{
}

KiranSidebarItem::~KiranSidebarItem()
{
}

void KiranSidebarItem::setStatusDesc(const QString &desc,const QColor &color)
{
    setData(ItemStatus_Role,desc);
    setData(ItemStatusColor_Role,color);
}

void KiranSidebarItem::getStatusDesc(QString &desc, QColor &color)
{
    QVariant statusRoleVar = data(ItemStatus_Role);
    QVariant colorRoleVar = data(ItemStatusColor_Role);

    if( statusRoleVar.isValid() && !statusRoleVar.isNull() && statusRoleVar.type()==QVariant::String &&
        colorRoleVar.isValid() && !colorRoleVar.isNull() && colorRoleVar.type()==QVariant::Color )
    {
        desc = statusRoleVar.toString();
        color = qvariant_cast<QColor>(colorRoleVar);
    }
}
