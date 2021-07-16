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
