//
// Created by lxh on 2020/12/25.
//

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
