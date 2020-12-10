//
// Created by lxh on 2020/11/28.
//

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
    }

    qInfo() << size;
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
