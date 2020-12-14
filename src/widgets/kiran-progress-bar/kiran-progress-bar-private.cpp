//
// Created by lxh on 2020/12/12.
//

#include "kiran-progress-bar-private.h"

KiranProgressBarPrivate::KiranProgressBarPrivate(QObject *parent)
    :QObject(parent)
{

}

KiranProgressBarPrivate::~KiranProgressBarPrivate()
{

}

void KiranProgressBarPrivate::init(KiranProgressBar* progressBar)
{
    q_ptr = progressBar;
}