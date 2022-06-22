//
// Created by liuxinhao on 2022/6/20.
//

#ifndef KIRANWIDGETS_QT5_MESSAGEDEMO_H
#define KIRANWIDGETS_QT5_MESSAGEDEMO_H

#include <kiran-message-box/kiran-message-box.h>
#include <QWidget>

class MessageDemo:public  KiranMessageBox
{
    Q_OBJECT
public:
    explicit MessageDemo(QWidget* parent = nullptr);
    ~MessageDemo() override{};

    int exec() override;
};

#endif  // KIRANWIDGETS_QT5_MESSAGEDEMO_H
