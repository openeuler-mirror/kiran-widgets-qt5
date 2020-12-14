//
// Created by lxh on 2020/12/12.
//

#include "kiran-spin-box.h"
#include "kiran-spin-box-private.h"
#include "style-property-helper.h"

using namespace Kiran;

KiranSpinBox::KiranSpinBox(QWidget *parent)
    : QSpinBox(parent),
      d_ptr(new KiranSpinBoxPrivate(this))
{
    d_ptr->init(this);
    PropertyHelper::setSpinboxButtonPosition(this,ARROW_POSITION_AUTOMATIC);
}

KiranSpinBox::~KiranSpinBox()
{

}

void KiranSpinBox::setSpinboxArrowPosition(Kiran::SpinboxArrowPosition arrowPosition)
{
    PropertyHelper::setSpinboxButtonPosition(this,arrowPosition);
}

Kiran::SpinboxArrowPosition KiranSpinBox::getSpinboxArrowPosition()
{
    return PropertyHelper::getSpinboxButtonPosition(this);
}

bool KiranSpinBox::event(QEvent *event)
{
    return QSpinBox::event(event);
}