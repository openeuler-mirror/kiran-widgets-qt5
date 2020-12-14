//
// Created by lxh on 2020/12/12.
//

#include "kiran-push-button.h"
#include "kiran-push-button-private.h"
#include "style-property-helper.h"

using namespace Kiran;

KiranPushButton::KiranPushButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new KiranPushButtonPrivate(this))
{
    d_ptr->init(this);
    PropertyHelper::setButtonType(this,BUTTON_Normal);
}

KiranPushButton::KiranPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent),
      d_ptr(new KiranPushButtonPrivate(this))
{
    d_ptr->init(this);
    PropertyHelper::setButtonType(this,BUTTON_Normal);
}

KiranPushButton::KiranPushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text,parent),
      d_ptr(new KiranPushButtonPrivate(this))
{
    d_ptr->init(this);
    PropertyHelper::setButtonType(this,BUTTON_Normal);
}

KiranPushButton::~KiranPushButton()
{

}

void KiranPushButton::setButtonType(Kiran::ButtonType buttonType)
{
    PropertyHelper::setButtonType(this,buttonType);
}

Kiran::ButtonType KiranPushButton::getButtonType()
{
    return PropertyHelper::getButtonType(this);
}

bool KiranPushButton::event(QEvent *e)
{
    return QPushButton::event(e);
}
