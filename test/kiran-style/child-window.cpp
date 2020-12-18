//
// Created by lxh on 2020/12/18.
//

#include "child-window.h"

ChildWindow::ChildWindow(QWidget *widget)
    : KiranTitlebarWindow(widget, Qt::Window)
{

}

ChildWindow::~ChildWindow()
{

}

QSize ChildWindow::sizeHint() const
{
    return QSize(640,480);
}
