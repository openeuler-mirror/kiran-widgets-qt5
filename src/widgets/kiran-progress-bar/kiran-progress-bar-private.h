//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PROGRESS_BAR_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_PROGRESS_BAR_PRIVATE_H

#include "kiran-progress-bar.h"

#include <QObject>

class KiranProgressBarPrivate :QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranProgressBar)
public:
    KiranProgressBarPrivate(QObject *parent = nullptr);
    ~KiranProgressBarPrivate();

public:
    void init(KiranProgressBar* progressBar);

private:
    KiranProgressBar* q_ptr;

};

#endif //KIRANWIDGETS_QT5_KIRAN_PROGRESS_BAR_PRIVATE_H
