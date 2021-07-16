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
 
#include "kiran-search-box.h"
#include "kiran-search-box-private.h"
#include "style.h"

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QLineEdit>
#include <QEvent>
#include <QDebug>

/*FIXME:
 * 搜索框该部分为了偷懒使用了QLineEdit控件
 * 该情况需使用布局，设置左边距,在调用KiranStyle来绘制搜索框边框和搜索图标。
 * 这种方案不能在KiranStyle里修改图标和输入框的间隙和在KiranStyle里定制更多细节。
 * */

KiranSearchBox::KiranSearchBox(QWidget *parent)
        : QLineEdit(parent),
          d_ptr(new KiranSearchBoxPrivate(this))
{
    d_ptr->init(this);
}

KiranSearchBox::~KiranSearchBox()
{

}

bool KiranSearchBox::event(QEvent *event)
{
    return QLineEdit::event(event);
}

bool KiranSearchBox::eventFilter(QObject *watched, QEvent *event)
{
    return QLineEdit::eventFilter(watched,event);
}

void KiranSearchBox::paintEvent(QPaintEvent *ev)
{
    QLineEdit::paintEvent(ev);

    QPainter painter(this);
    QStyleOption styleOption;
    styleOption.init(this);
    if(Kiran::Style::isKiranStyle()){
        Kiran::Style* kiranStyle = Kiran::Style::castToKiranStyle();
        kiranStyle->drawPrimitive(Kiran::PE_SearchBoxIndicator,&styleOption,&painter,this);
    }
}