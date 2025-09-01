/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiran-widgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */
#include "kiran-input-dialog.h"
#include "kiran-input-dialog_p.h"
#include "kiran-color-block/kiran-color-block.h"
#include "kiran-passwd-edit/kiran-passwd-edit.h"
#include "kiran-push-button/kiran-push-button.h"
#include <QBoxLayout>
#include <QCloseEvent>
#include <QEventLoop>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

KiranInputDialogPrivate::KiranInputDialogPrivate(KiranInputDialog* q)
    : QObject(q),
      m_success(false),
      m_labelDesc(nullptr),
      m_edit(nullptr),
      m_confirmButton(nullptr),
      q_ptr(q)
{
    q->installEventFilter(this);
}

KiranInputDialogPrivate::~KiranInputDialogPrivate()
{
}

bool KiranInputDialogPrivate::eventFilter(QObject *watched, QEvent *event)
{
    Q_Q(KiranInputDialog);
    
    // 处理关闭事件
    if (watched == q && event->type() == QEvent::Close) {
        emit completed();
        return false;
    }
    
    return QObject::eventFilter(watched, event);
}

void KiranInputDialogPrivate::initUI()
{
    Q_Q(KiranInputDialog);

    // 初始化自定义标题栏
    q->setTitlebarColorBlockEnable(true);
    q->setButtonHints(KiranInputDialog::TitlebarCloseButtonHint);
    q->setResizeable(false);

    // 初始化内容容器
    auto container = new QWidget(q);
    auto containerLayout = new QBoxLayout(QBoxLayout::TopToBottom, container);
    containerLayout->setContentsMargins(4, 4, 4, 4);

    auto colorBlock = new KiranColorBlock(container);
    colorBlock->setDrawBackground(true);
    containerLayout->addWidget(colorBlock);

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, colorBlock);
    layout->setContentsMargins(24, 24, 24, 24);

    m_labelDesc = new QLabel(q);
    m_labelDesc->setWordWrap(true);
    layout->addWidget(m_labelDesc);

    layout->addSpacerItem(new QSpacerItem(10, 16, QSizePolicy::Minimum, QSizePolicy::Fixed));

    m_edit = new KiranPasswdEdit(q);
    m_edit->setEchoMode(QLineEdit::Password);
    m_edit->lineEdit()->setMaxLength(32);
    QObject::connect(m_edit, &KiranPasswdEdit::passwordChanged, 
                   this, &KiranInputDialogPrivate::processTextChanged);
    layout->addWidget(m_edit);

    layout->addSpacerItem(new QSpacerItem(10, 16, QSizePolicy::Minimum, QSizePolicy::Fixed));

    auto boxlayout = new QBoxLayout(QBoxLayout::LeftToRight);
    boxlayout->setContentsMargins(0, 0, 0, 0);

    boxlayout->addStretch();

    m_confirmButton = new QPushButton(q);
    m_confirmButton->setObjectName("ConfirmButton");
    m_confirmButton->setFixedSize(QSize(110, 40));
    m_confirmButton->setText(QObject::tr("Confirm"));
    // checkValid检查输入有效性才启用
    m_confirmButton->setEnabled(false);

    KiranPushButton::setButtonType(m_confirmButton, KiranPushButton::BUTTON_Default);
    QObject::connect(m_confirmButton, &QPushButton::clicked, 
                   this, &KiranInputDialogPrivate::onConfirmClicked);
    boxlayout->addWidget(m_confirmButton);

    boxlayout->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));

    auto cancelButton = new QPushButton(q);
    cancelButton->setObjectName("CancelButton");
    cancelButton->setFixedSize(QSize(110, 40));
    cancelButton->setText(QObject::tr("Cancel"));
    QObject::connect(cancelButton, &QPushButton::clicked, this, &KiranInputDialogPrivate::completed);
    boxlayout->addWidget(cancelButton);

    boxlayout->addStretch();

    layout->addLayout(boxlayout);

    q->setWindowContentWidget(container);
}

void KiranInputDialogPrivate::processTextChanged(const QString& text)
{
    Q_Q(KiranInputDialog);
    m_confirmButton->setEnabled(q->checkValid(text));
}

void KiranInputDialogPrivate::onConfirmClicked()
{
    QString text = m_edit->lineEdit()->text();
    if (text.isEmpty())
    {
        return;
    }
    m_success = true;
    emit completed();
}

// KiranInputDialog implementation
KiranInputDialog::KiranInputDialog(QWidget* parent)
    : KiranTitlebarWindow(parent, Qt::Dialog),
      d_ptr(new KiranInputDialogPrivate(this))
{
    setAttribute(Qt::WA_ShowModal, true);
    Q_D(KiranInputDialog);
    d->initUI();
}

KiranInputDialog::~KiranInputDialog()
{
    delete d_ptr;
}

QString KiranInputDialog::getUserInput() const
{
    Q_D(const KiranInputDialog);
    return d->m_edit->lineEdit()->text();
}

void KiranInputDialog::setDesc(const QString& desc)
{
    Q_D(KiranInputDialog);
    d->m_labelDesc->setText(desc);
}

void KiranInputDialog::setInputMode(QLineEdit::EchoMode mode, qint32 maxLength)
{
    Q_D(KiranInputDialog);
    d->m_edit->setEchoMode(mode);
    d->m_edit->lineEdit()->setMaxLength(maxLength);
}

void KiranInputDialog::setPlaceholderText(const QString& text)
{
    Q_D(KiranInputDialog);
    d->m_edit->lineEdit()->setPlaceholderText(text);
}

void KiranInputDialog::clearInput()
{
    Q_D(KiranInputDialog);
    d->m_edit->lineEdit()->clear();
}

bool KiranInputDialog::exec()
{
    Q_D(KiranInputDialog);
    QEventLoop loop;
    connect(d_ptr, &KiranInputDialogPrivate::completed, &loop, &QEventLoop::quit);
    this->show();
    loop.exec(QEventLoop::DialogExec);
    return d->m_success;
}