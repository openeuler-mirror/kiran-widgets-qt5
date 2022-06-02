/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 */

#ifndef KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_PRIVATE_H

#include <QObject>
#include "kiran-icon-line-edit.h"

class KiranIconLineEditPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranIconLineEdit)
public:
    KiranIconLineEditPrivate(QObject *parent = nullptr);
    ~KiranIconLineEditPrivate();

    void init(KiranIconLineEdit *ptr);

private:
    KiranIconLineEdit *q_ptr;
};

#endif  //KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_PRIVATE_H
