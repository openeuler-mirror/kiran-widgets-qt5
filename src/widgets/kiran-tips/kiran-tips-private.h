/**
 * Copyright (c) 2021 ~ 2022 KylinSec Co., Ltd.
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
#pragma once

#include <QColor>
#include <QObject>
#include <QPropertyAnimation>
#include <QTimer>

#include "kiran-tips.h"

class QLabel;
class KiranTipsPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranTips)
public:
    KiranTipsPrivate(KiranTips *ptr);
    ~KiranTipsPrivate();

    void init();
    void updateContentsMargin();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranTips *q_ptr;
    bool m_hideOnClicked;
    bool m_animationEnable;

    KiranTips::ShowPostionHint m_showPostion = KiranTips::POSITION_RIGHT;
    QPropertyAnimation *m_EnterAnimation = nullptr;
    QTimer m_fadeOutTimer;
    QColor m_bgColor = Qt::white;

    QWidget *m_showAroudWidget = nullptr;
    QLabel *m_labelText = nullptr;
};