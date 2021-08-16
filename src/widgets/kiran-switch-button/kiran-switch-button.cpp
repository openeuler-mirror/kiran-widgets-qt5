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
 
#include "kiran-switch-button.h"
#include "kiran-switch-button-private.h"
#include "style.h"

#include <QDebug>
#include <QStyleOption>
#include <QFontMetrics>
#include <QPainter>

KiranSwitchButton::KiranSwitchButton(QWidget *parent)
    : QAbstractButton(parent) ,
    d_ptr(new KiranSwitchButtonPrivate(this))
{
    setCheckable(true);
}

KiranSwitchButton::~KiranSwitchButton()
{
    delete d_ptr;
}

bool KiranSwitchButton::event(QEvent *e)
{
    return QAbstractButton::event(e);
}

void KiranSwitchButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QStyleOptionButton optionButton;
    initStyleOption(&optionButton);

    if( Kiran::Style::isKiranStyle() ){
        Kiran::Style* kiranStyle = Kiran::Style::castToKiranStyle();
        kiranStyle->drawControl(Kiran::CE_SwitchButton,&optionButton,&painter,this);
    }
}

QSize KiranSwitchButton::sizeHint() const
{
    QStyleOptionButton optionButton;
    initStyleOption(&optionButton);

    int w=0,h=0;

    //获取文字宽高
    QString str = text();
    QFontMetrics metrics = fontMetrics();
    QSize size = metrics.size(Qt::TextHideMnemonic,str);
    if( Kiran::Style::isKiranStyle() ){
        Kiran::Style* kiranStyle = Kiran::Style::castToKiranStyle();
        size = kiranStyle->sizeFromContents(Kiran::CT_SwitchButton,&optionButton,size,this);
    }else{
        qWarning() << "isn't KiranStyle!" << "style objectname:" << style()->metaObject()->className() << style()->proxy()->metaObject()->className();
    }

    return size;
}

void KiranSwitchButton::initStyleOption(QStyleOptionButton *option) const
{
    option->init(this);
    option->initFrom(this);

    if( isChecked() ){
        option->state |= QStyle::State_On;
    }else{
        option->state |= QStyle::State_Off;
    }

    option->text = text();
}

QSize KiranSwitchButton::minimumSizeHint() const
{
    return sizeHint();
}
