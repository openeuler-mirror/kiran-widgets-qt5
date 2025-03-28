/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
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

#include <QLineEdit>
#include <QWidget>

/**
 * Todo:后续完成该部分功能，替换掉已失效的KiranIconLineEdit
 * 将会包含KiranIconLineEdit的功能
 */
class KiranLineEditPrivate;
class KiranLineEdit : public QWidget
{
    Q_OBJECT
public:
    enum TipsType
    {
        TIPS_INFO,
        TIPS_WARNING
    };
    enum TipsPosition
    {
        TIPS_POSITION_TOP,
        TIPS_POSITION_BOTTOM,
        TIPS_POSITION_LEFT,
        TIPS_POSITION_RIGHT
    };

public:
    explicit KiranLineEdit(QWidget* parent = nullptr);
    ~KiranLineEdit();

    QLineEdit* lineEdit() const;

    void setAlert(bool alert);
    bool getAlert() const;

    void setTipsPosition(TipsPosition position);
    TipsPosition getTipsPosition() const;

    void showTips(TipsType type, const QString& text, int duration = 2000);
    void hideTips();

    void setText(const QString& text);
    const QString& text();
    void clean();

    QLineEdit::EchoMode echoMode() const;
    void setEchoMode(QLineEdit::EchoMode mode);

    void setContextMenuPolicy(Qt::ContextMenuPolicy policy);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void alertChanged(bool alert) const;
    void focusChanged(bool onFocus) const;
    void textChanged(const QString&);
    void textEdited(const QString&);
    void cursorPositionChanged(int, int);
    void returnPressed();
    void editingFinished();
    void selectionChanged();

private:
    KiranLineEditPrivate* d_ptr;
    Q_DECLARE_PRIVATE(KiranLineEdit);
};
