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
