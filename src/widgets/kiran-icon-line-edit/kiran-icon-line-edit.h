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
 
#ifndef KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_H
#define KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_H

#include <QLineEdit>
#include <QIcon>

#include <kiran-style-public-define.h>

class KiranIconLineEditPrivate;

/**
 * @brief 带有图标的行输入框，在KiranStyle下提供特殊的绘制,使用方法可见QLineEdit
 * 只有才KiranStyle下才支持绘制，其他Style下绘制出来只是个普通输入框
 *
 * 使用说明
 *　和QLineEdit一样的用法
 *
 * @since 2.1.0
 * @see QLineEdit
 */
class KiranIconLineEdit : public QLineEdit{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranIconLineEdit)
public:
    explicit KiranIconLineEdit(QWidget *parent = nullptr);
    explicit KiranIconLineEdit(const QString &text, QWidget *parent = nullptr);
    ~KiranIconLineEdit();

    /**
     * @brief 设置图标
     * @param icon 图标
     */
    void setIcon(const QIcon& icon);

    /**
     * @brief 获取设置的图标
     * @return 图标
     */
    QIcon icon();

    /**
     * @brief 设置按钮绘制大小
     * @param iconSize 按钮大小
     */
    void setIconSize(QSize iconSize);

    /**
     * @brief 获取按钮绘制大小
     * @return iconSize 按钮大小
     */
    QSize iconSize();

    /**
     * @brief 设置图标绘制位置
     * @param position 图标绘制位置
     */
    void setIconPosition(Kiran::IconLineEditIconPosition position);

    /**
     * @brief 获取图标绘制位置
     * @return Kiran::IconLineEditIconPosition 图标绘制位置
     */
    Kiran::IconLineEditIconPosition iconPosition();

private:
    /* 绘制图标,调用QLineEdit绘制边框背景,KiranStyle单独处理,预留图片绘制位置 */
    void paintEvent(QPaintEvent *) override;

private:
    QIcon m_icon;
    KiranIconLineEditPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_H
