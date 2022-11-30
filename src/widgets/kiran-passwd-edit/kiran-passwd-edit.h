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
#ifndef __KIRAN_PASSWD_EDIT_H__
#define __KIRAN_PASSWD_EDIT_H__

#include <QLineEdit>
#include <QWidget>
#include <memory>

class QAction;
class KiranPasswdEditPrivate;

class KiranPasswdEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool clearButtonEnabled READ isClearButtonEnabled WRITE setClearButtonEnabled)
    Q_PROPERTY(QLineEdit::EchoMode echoMode READ echoMode WRITE setEchoMode NOTIFY echoModeChanged)
    Q_DECLARE_PRIVATE(KiranPasswdEdit)
public:
    explicit KiranPasswdEdit(QWidget *parent = nullptr);
    ~KiranPasswdEdit() override;

    void setPassword(const QString &password);
    QString password() const;

    void clear();

    void setClearButtonEnabled(bool clear);
    bool isClearButtonEnabled() const;

    void setEchoMode(QLineEdit::EchoMode mode);
    QLineEdit::EchoMode echoMode() const;

    void setRevealPasswordAvailable(bool reveal);
    bool isRevealPasswordAvailable() const;
    
    QAction *toggleEchoModeAction() const;
    QLineEdit *lineEdit() const;

Q_SIGNALS:
    void echoModeChanged(QLineEdit::EchoMode echoMode);
    void passwordChanged(const QString &password);

private:
    KiranPasswdEditPrivate *d_ptr;
};

#endif