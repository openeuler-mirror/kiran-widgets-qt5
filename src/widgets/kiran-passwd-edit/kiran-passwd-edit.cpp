/**
 * Copyright (c) 2020 ~ 2022 KylinSec Co., Ltd.
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
#include "kiran-passwd-edit.h"

#include <QAction>
#include <QHBoxLayout>
#include <QIcon>

class KiranPasswdEditPrivate
{
public:
    KiranPasswdEditPrivate(KiranPasswdEdit *qq)
        : q(qq)
    {
    }
    void initialize();
    void echoModeToggled();
    void showToggleEchoModeAction(const QString &text);

    QIcon passwordIcon;
    QIcon visibleIcon;

    QLineEdit *passwordLineEdit = nullptr;
    QAction *toggleEchoModeAction = nullptr;
    bool isToggleEchoModeAvailable = true;
    bool revealPasswordAvailable = false;
    KiranPasswdEdit *const q;
};

void KiranPasswdEditPrivate::initialize()
{
    QIcon visibilityIcon = QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg")));
    toggleEchoModeAction = passwordLineEdit->addAction(visibilityIcon, QLineEdit::TrailingPosition);
    toggleEchoModeAction->setObjectName(QStringLiteral("visibilityAction"));
    toggleEchoModeAction->setVisible(false);
    toggleEchoModeAction->setToolTip(QObject::tr("Change the visibility of the password", "@info:tooltip"));
    q->connect(toggleEchoModeAction, &QAction::triggered, q, [this]()
               { echoModeToggled(); });
    q->connect(passwordLineEdit, &QLineEdit::textChanged, q, [this](const QString &str)
               { showToggleEchoModeAction(str); });
}

void KiranPasswdEditPrivate::showToggleEchoModeAction(const QString &text)
{
    if (revealPasswordAvailable)
    {
        toggleEchoModeAction->setVisible(isToggleEchoModeAvailable && (passwordLineEdit->echoMode() == QLineEdit::Normal || !text.isEmpty()));
    }
    else
    {
        toggleEchoModeAction->setVisible(false);
    }
}

void KiranPasswdEditPrivate::echoModeToggled()
{
    if (passwordLineEdit->echoMode() == QLineEdit::Password)
    {
        passwordLineEdit->setEchoMode(QLineEdit::Normal);
        if (passwordIcon.isNull())
        {
            passwordIcon = QIcon::fromTheme("ksvg-reveal-passwd");
        }
        toggleEchoModeAction->setIcon(passwordIcon);
    }
    else if (passwordLineEdit->echoMode() == QLineEdit::Normal)
    {
        if (visibleIcon.isNull())
        {
            visibleIcon = QIcon::fromTheme("ksvg-unreveal-passwd");
        }
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        toggleEchoModeAction->setIcon(visibleIcon);
    }
    Q_EMIT q->echoModeChanged(passwordLineEdit->echoMode());
}

KiranPasswdEdit::KiranPasswdEdit(QWidget *parent)
    : QWidget(parent), d_ptr(new KiranPasswdEditPrivate(this))
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    d_ptr->passwordLineEdit = new QLineEdit(this);
    d_ptr->passwordLineEdit->setObjectName(QStringLiteral("passwordlineedit"));
    d_ptr->passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(d_ptr->passwordLineEdit, &QLineEdit::textChanged, this, &KiranPasswdEdit::passwordChanged);
    setFocusProxy(d_ptr->passwordLineEdit);
    setFocusPolicy(d_ptr->passwordLineEdit->focusPolicy());
    mainLayout->addWidget(d_ptr->passwordLineEdit);
    d_ptr->initialize();

    setStyleSheet("QLineEdit[echoMode=\"2\"]{ lineedit-password-character: 9679; }");
}

KiranPasswdEdit::~KiranPasswdEdit() = default;

void KiranPasswdEdit::setPassword(const QString &password)
{
    if (d_ptr->passwordLineEdit->text() != password)
    {
        d_ptr->isToggleEchoModeAvailable = password.isEmpty();
        d_ptr->passwordLineEdit->setText(password);
    }
}

QString KiranPasswdEdit::password() const
{
    return d_ptr->passwordLineEdit->text();
}

void KiranPasswdEdit::clear()
{
    d_ptr->passwordLineEdit->clear();
}

void KiranPasswdEdit::setClearButtonEnabled(bool clear)
{
    d_ptr->passwordLineEdit->setClearButtonEnabled(clear);
}

bool KiranPasswdEdit::isClearButtonEnabled() const
{
    return d_ptr->passwordLineEdit->isClearButtonEnabled();
}

void KiranPasswdEdit::setEchoMode(QLineEdit::EchoMode mode)
{
    d_ptr->passwordLineEdit->setEchoMode(mode);
}

QLineEdit::EchoMode KiranPasswdEdit::echoMode() const
{
    return d_ptr->passwordLineEdit->echoMode();
}

QLineEdit *KiranPasswdEdit::lineEdit() const
{
    return d_ptr->passwordLineEdit;
}

void KiranPasswdEdit::setRevealPasswordAvailable(bool reveal)
{
    d_ptr->revealPasswordAvailable = reveal;
    d_ptr->showToggleEchoModeAction(password());
}

bool KiranPasswdEdit::isRevealPasswordAvailable() const
{
    return d_ptr->revealPasswordAvailable;
}

QAction *KiranPasswdEdit::toggleEchoModeAction() const
{
    return d_ptr->toggleEchoModeAction;
}

#include "moc_kiran-passwd-edit.cpp"