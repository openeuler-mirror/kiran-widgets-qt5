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
 

#include "widget-property-helper.h"

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

ButtonType WidgetPropertyHelper::getButtonType(const QPushButton *btn)
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

void WidgetPropertyHelper::setButtonType(QPushButton *btn, ButtonType type)
{
    btn->setProperty(PROPERTY_KIRAN_BUTTON_TYPE,type);
}

void WidgetPropertyHelper::setSpinboxButtonPosition(QWidget *spinBox,
                                                    SpinboxArrowPosition position)
{
    spinBox->setProperty(PROPERTY_KIRAN_SPINBOX_POSITION,position);
}

SpinboxArrowPosition WidgetPropertyHelper::getSpinboxButtonPosition(const QWidget *spinBox)
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

void WidgetPropertyHelper::setProgressBarTextProsition(QProgressBar *progressBar,
                                                       ProgressBarTextPosition textPosition)
{
    progressBar->setProperty(PROPERTY_KIRAN_PROGRESSBAR_TEXT_POSITION,textPosition);
}

ProgressBarTextPosition WidgetPropertyHelper::getProgressBarTextPosition(const QProgressBar *progressBar)
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
