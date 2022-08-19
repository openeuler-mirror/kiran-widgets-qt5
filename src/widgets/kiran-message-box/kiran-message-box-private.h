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
 
#ifndef KIRANMESSAGEBOXPRIVATE_H
#define KIRANMESSAGEBOXPRIVATE_H

#include "kiran-message-box.h"

#include <QMap>
#include <QDialogButtonBox>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QSpacerItem>

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
    QWidget* initChildWidgets(const QString& title,const QString& text);

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
    static const int shadowWidth;
    static const int shadowRadius;
    static const QColor shadowColor;
    static const QColor shadowActiveColor;

    KiranMessageBox *q_ptr;
    QLayout *m_layout;
    QLayout *m_hlayout;
    QSpacerItem *m_topShadowSpacerItem;
    QSpacerItem *m_bottomShadowSpacerItem;
    QSpacerItem *m_leftShadowSpacerItem;
    QSpacerItem *m_rightShadowSpacerItem;

    QFrame *m_frame;
    QVBoxLayout *m_frameLayout;

    QHBoxLayout *m_customLayout;

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
