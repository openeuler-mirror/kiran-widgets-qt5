/*
 * @file   kiran-icon-line-edit-private.h
 * @brief  KiranIconLineEdit私有类
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_PRIVATE_H

#include <QObject>
#include "kiran-icon-line-edit.h"

class KiranIconLineEditPrivate : public QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranIconLineEdit)
public:
    KiranIconLineEditPrivate(QObject *parent=nullptr);
    ~KiranIconLineEditPrivate();

    void init(KiranIconLineEdit* ptr);

private:
    KiranIconLineEdit *q_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_PRIVATE_H
