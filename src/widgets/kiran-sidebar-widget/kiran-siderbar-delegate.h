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

#include <QItemDelegate>

class KiranSiderbarDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit KiranSiderbarDelegate(QObject *parent = nullptr);
    ~KiranSiderbarDelegate();

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize sizeFromContents(const QStyleOptionViewItem &opt, const QModelIndex &idx,
                           QSize &pixmapSize, QSize &textSize,
                           QSize &statusDescSize, QSize &indicatorSize) const;

    QPixmap getDecorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index, QSize &pixmapSize) const;
    inline QIcon::State iconState(QStyle::State styleState) const
    {
        return (styleState & QStyle::State_On) ? QIcon::On : QIcon::Off;
    }

    inline QIcon::Mode iconMode(QStyle::State styleState) const
    {
        if (!(styleState & QStyle::State_Enabled))
            return QIcon::Disabled;
        else if (styleState & QStyle::State_Selected)
            return QIcon::Selected;
        else
            return QIcon::Normal;
    }

private:
    QString textForRole(Qt::ItemDataRole role, const QVariant &value, const QLocale &locale) const;
    QRect textLayoutBounds(const QStyleOptionViewItem &option) const;
    void doLayout(const QStyleOptionViewItem &option, const QModelIndex &index,
                  QRect &pixmapRect, QRect &textRect,
                  QRect &statusDescRect, QRect &indicatorRect) const;
};