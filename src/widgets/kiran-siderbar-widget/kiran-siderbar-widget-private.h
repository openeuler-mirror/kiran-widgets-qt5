//
// Created by lxh on 2020/12/15.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_PRIVATE_H

#include "kiran-siderbar-widget.h"

class KiranSiderbarWidgetPrivate :QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranSiderbarWidget)
public:
    KiranSiderbarWidgetPrivate(QObject* parent = nullptr);
    ~KiranSiderbarWidgetPrivate();

    void init(KiranSiderbarWidget* ptr);

private:
    KiranSiderbarWidget* q_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_PRIVATE_H
