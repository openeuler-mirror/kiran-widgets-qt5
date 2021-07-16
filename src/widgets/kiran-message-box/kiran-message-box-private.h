 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */
 
#ifndef KIRANMESSAGEBOXPRIVATE_H
#define KIRANMESSAGEBOXPRIVATE_H

#include "kiran-message-box.h"

#include <QMap>
#include <QDialogButtonBox>
#include <QGraphicsDropShadowEffect>

class QLabel;
class QPushButton;
class QFrame;

using KiranStandardButton = KiranMessageBox::KiranStandardButton;
using KiranStandardButtons = KiranMessageBox::KiranStandardButtons;
using ButtonRole = QDialogButtonBox::ButtonRole;

class KiranMessageBoxPrivate
{
    Q_DECLARE_PUBLIC(KiranMessageBox);
private:
    KiranMessageBoxPrivate(KiranMessageBox* ptr);
    ~KiranMessageBoxPrivate() = default;

private:
    void init(const QString &title="", const QString &text="");
    //NOTE:暂时不用
    void setIcon(const QString &iconPath);
    void setTitle(const QString &title);
    void setText(const QString &text);

    void setButtonSize(const QSize &size);
    QPushButton* addButton(KiranStandardButton button);
    QPushButton* addButton(const QString &text,QDialogButtonBox::ButtonRole role);
    void addButton(QPushButton* button,QDialogButtonBox::ButtonRole role);
    void removeButton(QPushButton* button);
    void cleanButton();

    void setStandarButtons(KiranStandardButtons buttons);
    KiranStandardButtons standardButtons();
    KiranStandardButton standardButton(QAbstractButton *button);
    QPushButton* button(KiranStandardButton which);

private:
    void enableShadow(bool enable);
    void handleMouseButtonPressEvent(QMouseEvent *event);
    void handleMouseButtonReleaseEvent(QMouseEvent *event);
    void handlerMouseMoveEvent(QMouseEvent* event);
    void handlerActivationChangeEvent(bool active);

private:
    KiranMessageBox *q_ptr;
    QLayout *m_layout;

    QFrame *m_frame;
    QLayout *m_frameLayout;

    ///标题
    QWidget *m_titleWidget;
    QLayout *m_titleLayout;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;

    ///正文
    QLabel *m_textLabel;

    ///按钮盒,默认按钮的映射关系
    KiranStandardButtons m_standardButtons;
    QMap<KiranStandardButton,QPushButton*> m_standardButtonsMap;
    QDialogButtonBox *m_dialogButtonBox;
    QGraphicsDropShadowEffect *m_dropShadowEffect;

    bool m_titlebarIsPressed;

    KiranStandardButton m_clickedStandardButton = KiranStandardButton::NoButton;
    QPushButton *m_clickedButton = nullptr;
    QSize m_buttonSize = QSize(100,40);
};

#endif // KIRANMESSAGEBOXPRIVATE_H
