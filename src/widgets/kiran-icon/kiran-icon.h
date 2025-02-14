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
 * Author:     yuanxing <yuanxing@kylinsec.com.cn>
 */

#ifndef KIRANICON_H
#define KIRANICON_H

#include <QFile>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

class KiranIconPrivate;

/**
 * @brief 该控件用于显示图标
 */

class KiranIcon : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranIcon)

public:
    explicit KiranIcon(QWidget *parent = nullptr);
    ~KiranIcon() override = default;

    /**
     * @brief 设置图标
     * @param icon 图标
     */
    void setIcon(const QIcon &icon);

    /**
     * @brief 获取设置的图标
     * @return 图标
     */
    QIcon icon();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QIcon m_icon;
    KiranIconPrivate *d_ptr;
};

#endif  // KIRANICON_H
