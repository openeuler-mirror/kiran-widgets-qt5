//
// Created by lxh on 2020/12/12.
//

#include "kiran-progress-bar.h"
#include "kiran-progress-bar-private.h"
#include "src/kiran-style/style-property-helper.h"

using namespace Kiran;

KiranProgressBar::KiranProgressBar(QWidget *parent)
    : QProgressBar(parent),
    d_ptr(new KiranProgressBarPrivate(this))
{
    d_ptr->init(this);
}

KiranProgressBar::~KiranProgressBar()
{

}

void KiranProgressBar::setTextPosition(ProgressBarTextPosition position)
{
    PropertyHelper::setProgressBarTextProsition(this,position);
}

ProgressBarTextPosition KiranProgressBar::getTextPosition()
{
    return PropertyHelper::getProgressBarTextPosition(this);
}

bool KiranProgressBar::event(QEvent *event)
{
    return QProgressBar::event(event);
}
