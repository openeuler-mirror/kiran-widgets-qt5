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
 
#ifndef KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_PRIVATE_H

#include "kiran-search-box.h"

#include <QObject>
#include <QBoxLayout>

class KiranSearchBoxPrivate : public QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranSearchBox)
public:
    KiranSearchBoxPrivate(QObject* parent = nullptr);
    ~KiranSearchBoxPrivate();

private:
    void init(KiranSearchBox* ptr);

private:
    KiranSearchBox* q_ptr = nullptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_PRIVATE_H
