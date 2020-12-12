//
// Created by lxh on 2020/11/19.
//

#include "style-property-helper.h"

#include <QToolButton>
#include <QPushButton>
#include <QSpinBox>
#include <QProgressBar>

/// pushbutton
#define PROPERTY_KIRAN_BUTTON_TYPE      "_kiran_button_type"

/// spinbox
#define PROPERTY_KIRAN_SPINBOX_POSITION "_kiran_spinbox_position"

/// progress bar
#define  PROPERTY_KIRAN_PROGRESSBAR_TEXT_POSITION "_kiran_progressbar_text_position"

using namespace Kiran;

ButtonType PropertyHelper::getButtonType(const QPushButton *btn)
{
    ButtonType type = BUTTON_Normal;
    QVariant var = btn->property(PROPERTY_KIRAN_BUTTON_TYPE);
    if( var.isValid() ){
        bool toInt = false;
        auto temp = static_cast<ButtonType>(var.toInt(&toInt));
        if(toInt){
            type = temp;
        }
    }
    return type;
}

void PropertyHelper::setButtonType(QPushButton *btn, ButtonType type)
{
    btn->setProperty(PROPERTY_KIRAN_BUTTON_TYPE,type);
}

void PropertyHelper::setSpinboxButtonPosition(QSpinBox *spinBox,
                                                     SpinboxArrowPosition position)
{
    spinBox->setProperty(PROPERTY_KIRAN_SPINBOX_POSITION,position);
}

SpinboxArrowPosition PropertyHelper::getSpinboxButtonPosition(QSpinBox *spinBox)
{
    SpinboxArrowPosition position = ARROW_POSITION_AUTOMATIC;
    QVariant var = spinBox->property(PROPERTY_KIRAN_SPINBOX_POSITION);
    if(var.isValid()){
        bool toInt = false;
        SpinboxArrowPosition temp = static_cast<SpinboxArrowPosition>(var.toInt(&toInt));
        if(toInt){
            position = temp;
        }
    }
    return position;
}

void PropertyHelper::setProgressBarTextProsition(QProgressBar *progressBar,
                                                        ProgressBarTextPosition textPosition)
{
    progressBar->setProperty(PROPERTY_KIRAN_PROGRESSBAR_TEXT_POSITION,textPosition);
}

ProgressBarTextPosition PropertyHelper::getProgressBarTextPosition(const QProgressBar *progressBar)
{
    ProgressBarTextPosition position = PROGRESS_TEXT_RIGHT;
    QVariant var = progressBar->property(PROPERTY_KIRAN_PROGRESSBAR_TEXT_POSITION);
    if(var.isValid()){
        bool toInt = false;
        ProgressBarTextPosition temp = static_cast<ProgressBarTextPosition>(var.toInt(&toInt));
        if(toInt){
            position = temp;
        }
    }
    return position;
}
