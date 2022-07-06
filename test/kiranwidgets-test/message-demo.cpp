//
// Created by liuxinhao on 2022/6/20.
//

#include "message-demo.h"

#include <QLineEdit>
#include <QPushButton>

MessageDemo::MessageDemo(QWidget *parent)
    : KiranMessageBox(parent)
{
    auto edit = new QLineEdit(this);
    addWidgetToDialog(edit,Qt::AlignVCenter);
    edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);


    setTitle("Test");
    setText("测试文本");

    addButton(new QPushButton("Yes"),QDialogButtonBox::AcceptRole);
    addButton(new QPushButton("No"),QDialogButtonBox::RejectRole);
}

int MessageDemo::exec()
{
    KiranMessageBox::exec();
    auto button =  KiranMessageBox::clickedButton();
    return 0;
}
