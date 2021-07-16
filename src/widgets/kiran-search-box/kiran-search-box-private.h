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
