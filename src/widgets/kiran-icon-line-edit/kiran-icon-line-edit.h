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

#ifndef KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_H
#define KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_H

#include <QIcon>
#include <QLineEdit>
#include <kiran-style-public-define.h>

class KiranIconLineEditPrivate;

/**
 * WARNING:
 * 该类应该不再继续使用，使用KiranLineEdit替代
 */

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
class Q_DECL_DEPRECATED KiranIconLineEdit : public QLineEdit
{
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
    void setIcon(const QIcon &icon);

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
    QIcon                     m_icon;
    KiranIconLineEditPrivate *d_ptr;
};

#endif  //KIRANWIDGETS_QT5_KIRAN_ICON_LINE_EDIT_H
