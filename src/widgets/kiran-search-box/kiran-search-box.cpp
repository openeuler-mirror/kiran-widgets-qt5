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