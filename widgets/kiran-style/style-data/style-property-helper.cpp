//
// Created by lxh on 2020/11/19.
//

#include "style-property-helper.h"

#include <QToolButton>
#include <QPushButton>
#include <QSpinBox>

#define PROPERTY_KIRAN_BUTTON_TYPE      "_kiran_button_type"

#define PROPERTY_KIRAN_SPINBOX_POSITION "_kiran_spinbox_position"

Kiran::ButtonType Kiran::PropertyHelper::getButtonType(const QPushButton *btn)
{
    Kiran::ButtonType type = Kiran::BUTTON_Normal;
    QVariant var = btn->property(PROPERTY_KIRAN_BUTTON_TYPE);
    if( var.isValid() ){
        bool toInt = false;
        auto temp = static_cast<Kiran::ButtonType>(var.toInt(&toInt));
        if(toInt){
            type = temp;
        }
    }
    return type;
}

void Kiran::PropertyHelper::setButtonType(QPushButton *btn, Kiran::ButtonType type)
{
    btn->setProperty(PROPERTY_KIRAN_BUTTON_TYPE,type);
}

void Kiran::PropertyHelper::setSpinboxButtonPosition(QSpinBox *spinBox,
                                                     Kiran::SpinboxArrowPosition position)
{
    spinBox->setProperty(PROPERTY_KIRAN_SPINBOX_POSITION,position);
}

Kiran::SpinboxArrowPosition Kiran::PropertyHelper::getSpinboxButtonPosition(QSpinBox *spinBox)
{
    Kiran::SpinboxArrowPosition position = ARROW_POSITION_AUTOMATIC;
    QVariant var = spinBox->property(PROPERTY_KIRAN_SPINBOX_POSITION);
    if(var.isValid()){
        bool toInt = false;
        Kiran::SpinboxArrowPosition temp = static_cast<Kiran::SpinboxArrowPosition>(var.toInt(&toInt));
        if(toInt){
            position = temp;
        }
    }
    return position;
}
