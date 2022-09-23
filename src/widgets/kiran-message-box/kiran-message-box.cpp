/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 */

#include "kiran-message-box.h"
#include "kiran-message-box-private.h"
#include "xlib-helper.h"

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QX11Info>

KiranMessageBox::KiranMessageBox(QWidget *parent)
    : QDialog(parent),
      d_ptr(new KiranMessageBoxPrivate(this))
{
    setWindowFlag(Qt::FramelessWindowHint);      //无边框
    setAttribute(Qt::WA_TranslucentBackground);  //背景透明
    setAccessibleName("KiranMessageBox");
    d_ptr->init();
    connect(d_ptr->m_dialogButtonBox, &QDialogButtonBox::clicked, [this](QAbstractButton *button) {
        d_ptr->m_clickedStandardButton = d_ptr->standardButton(button);
        d_ptr->m_clickedButton = qobject_cast<QPushButton *>(button);
        done(0);
    });
}

KiranMessageBox::~KiranMessageBox()
{
    delete d_ptr;
}

void KiranMessageBox::setTitle(const QString &title)
{
    d_ptr->setTitle(title);
}

void KiranMessageBox::setText(const QString &text)
{
    d_ptr->setText(text);
}

bool KiranMessageBox::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ShowToParent:
        d_func()->enableShadow(QX11Info::isCompositingManagerRunning());
        break;
    case QEvent::MouseButtonPress:
        d_func()->handleMouseButtonPressEvent(dynamic_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseButtonRelease:
        d_func()->handleMouseButtonReleaseEvent(dynamic_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseMove:
        d_func()->handlerMouseMoveEvent(dynamic_cast<QMouseEvent *>(event));
        break;
    case QEvent::ActivationChange:
        d_func()->handlerActivationChangeEvent(isActiveWindow());
        break;
    default:
        break;
    }
    return QDialog::event(event);
}

KiranStandardButton KiranMessageBox::message(QWidget *parent, const QString &title,
                                             const QString &text, KiranStandardButtons buttons)
{
    KiranMessageBox msgBox(parent);
    msgBox.setTitle(title);
    msgBox.setText(text);
    msgBox.d_ptr->setStandarButtons(buttons);
    msgBox.exec();
    return msgBox.d_ptr->m_clickedStandardButton;
}

QPushButton *KiranMessageBox::clickedButton()
{
    return d_ptr->m_clickedButton;
}

QSize KiranMessageBox::buttonSize()
{
    return d_ptr->m_buttonSize;
}

void KiranMessageBox::setButtonSize(const QSize &size)
{
    d_ptr->setButtonSize(size);
}

void KiranMessageBox::addButton(QPushButton *button, QDialogButtonBox::ButtonRole role)
{
    d_ptr->addButton(button, role);
}

void KiranMessageBox::removeButton(QPushButton *button)
{
    d_ptr->removeButton(button);
}

void KiranMessageBox::cleanButton()
{
    d_ptr->cleanButton();
}

QSize KiranMessageBox::sizeHint() const
{
    QSize size = QDialog::sizeHint();
    QSize buttonBoxSizeHint = d_ptr->m_dialogButtonBox->sizeHint();
    bool showShadow = QX11Info::isCompositingManagerRunning();
    QMargins margins = d_ptr->m_frameLayout->contentsMargins();

    int minimumWidth = buttonBoxSizeHint.width() + margins.left() + margins.right() + (showShadow ? (2 * d_ptr->shadowWidth) : 0);
    if (size.width() < minimumWidth)
    {
        size.rwidth() = minimumWidth;
    }
    return size;
}

void KiranMessageBox::addWidgetToDialog(QWidget* widget,Qt::AlignmentFlag alignment)
{
    d_ptr->m_customLayout->setContentsMargins(0,10,0,0);
    d_ptr->m_customLayout->addWidget(widget,0,alignment);
}
