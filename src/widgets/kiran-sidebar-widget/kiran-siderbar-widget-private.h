//
// Created by lxh on 2020/12/15.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_PRIVATE_H

#include "kiran-sidebar-widget.h"

class KiranSidebarWidgetPrivate : QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranSidebarWidget)
public:
    KiranSidebarWidgetPrivate(QObject* parent = nullptr);
    ~KiranSidebarWidgetPrivate();

    void init(KiranSidebarWidget* ptr);

private:
    KiranSidebarWidget* q_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_PRIVATE_H
