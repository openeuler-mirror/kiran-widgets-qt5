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
