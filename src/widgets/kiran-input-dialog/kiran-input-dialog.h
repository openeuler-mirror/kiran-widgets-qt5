/**
 * Copyright (c) 2020 ~ 2023 KylinSec Co., Ltd.
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
#pragma once
#include <kiranwidgets-qt5/kiran-titlebar-window.h>
#include <QLineEdit>

class KiranInputDialogPrivate;
class KiranInputDialog : public KiranTitlebarWindow
{
    Q_OBJECT
public:
    KiranInputDialog(QWidget* parent = nullptr);
    ~KiranInputDialog();

    void setDesc(const QString& desc);
    void setInputMode(QLineEdit::EchoMode mode, qint32 maxLength);
    void setPlaceholderText(const QString& text);

    void clearInput();
    QString getUserInput() const;

    bool exec();

    /**
     * @brief 校验输入内容的有效性
     * 可重写该虚函数以自定义输入校验逻辑，默认始终返回 true。
     * @param text 用户输入的文本内容
     * @return true 表示输入有效，false 表示输入无效
     */
    virtual bool checkValid(const QString& text) { return true; }

private:
    KiranInputDialogPrivate* d_ptr;
    Q_DECLARE_PRIVATE(KiranInputDialog)
    Q_DISABLE_COPY(KiranInputDialog)
};