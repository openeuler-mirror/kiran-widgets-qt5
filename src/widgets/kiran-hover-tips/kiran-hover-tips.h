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

#ifndef KIRAN_ACCOUNT_MANAGER_HOVER_TIPS_H
#define KIRAN_ACCOUNT_MANAGER_HOVER_TIPS_H

#include <QMap>
#include <QWidget>

class QLabel;
class KiranHoverTipsPrivate;
class KiranHoverTips : private QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranHoverTips);

public:
    enum HoverTipsTypeEnum
    {
        HOVE_TIPS_SUC,
        HOVE_TIPS_INFO,
        HOVE_TIPS_WARNING,
        HOVE_TIPS_ERR
    };
    Q_ENUMS(HoverTipsEnum);

public:
    explicit KiranHoverTips(QWidget *parent = nullptr);
    ~KiranHoverTips();

    void setTimeout(quint32 ms);
    void setIcon(HoverTipsTypeEnum typeEnum, const QString &icon);
    void showTips(HoverTipsTypeEnum typeEnum, const QString &msg);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    KiranHoverTipsPrivate *d_ptr;
};

#endif  // KIRAN_ACCOUNT_MANAGER_HOVER_TIPS_H
