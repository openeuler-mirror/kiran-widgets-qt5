/**
 * Copyright (c) 2020 ~ 2022 KylinSec Co., Ltd. 
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
#ifndef __KIRAN_LABEL_PRIVATE_H__
#define __KIRAN_LABEL_PRIVATE_H__

#include "kiran-label.h"

class KiranLabelPrivate:public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranLabel)
public:
    explicit KiranLabelPrivate(KiranLabel* ptr,QObject* parent = nullptr);
    ~KiranLabelPrivate();

    void init();

    //以下方法由于QLabelPrivate未暴露函数符号,将QLabel::paintEvent中使用QLabelPrivate的方法,移动至KiranLabelPrivate重新实现
    static Qt::LayoutDirection textDirection(QLabelPrivate* ld);
    static QRectF layoutRect(QLabelPrivate* ld);
    static QRectF documentRect(QLabelPrivate* ld);
    static void ensureTextLayouted(QLabelPrivate* ld);

private:
    KiranLabel* q_ptr;
    Qt::TextElideMode elideMode = Qt::ElideNone;
};

#endif