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
 
#include "widget-private-property-helper.h"

#include <QLineEdit>

#define PROPERTY_KIRAN_LINE_EDIT_ICON_POSITION "_kiran_line_edit_icon_position"
#define PROPERTY_KIRAN_LINE_EDIT_ICON_SIZE     "_kiran_line_edit_icon_size"

using namespace Kiran;

void WidgetPrivatePropertyHelper::setLineEditIconPosition(QLineEdit *edit,
                                                          IconLineEditIconPosition position)
{
    edit->setProperty(PROPERTY_KIRAN_LINE_EDIT_ICON_POSITION,position);
    edit->update();
}

IconLineEditIconPosition WidgetPrivatePropertyHelper::getLineEditIconPosition(const QLineEdit *edit)
{
    IconLineEditIconPosition position = ICON_POSITION_NONE;
    QVariant var = edit->property(PROPERTY_KIRAN_LINE_EDIT_ICON_POSITION);
    if( var.isValid() ){
        bool toInt = false;
        auto temp = static_cast<IconLineEditIconPosition>(var.toInt(&toInt));
        if(toInt){
            position = temp;
        }
    }
    return position;
}

void WidgetPrivatePropertyHelper::setLineEditIconSize(QLineEdit* edit,QSize size)
{
    edit->setProperty(PROPERTY_KIRAN_LINE_EDIT_ICON_SIZE,size);
    edit->update();
}

QSize WidgetPrivatePropertyHelper::getLineEditIconSize(const QLineEdit* edit)
{
    QSize size;
    QVariant var = edit->property(PROPERTY_KIRAN_LINE_EDIT_ICON_SIZE);
    size = var.toSize();
    return size;
}
