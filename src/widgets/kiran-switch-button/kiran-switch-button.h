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
 
 
#ifndef KIRANSTYLE_SWITCH_BUTTON_H
#define KIRANSTYLE_SWITCH_BUTTON_H

#include <QAbstractButton>

class KiranSwitchButtonPrivate;
class QStyleOptionButton;

/**
 * @brief SwitchButton开关按钮，仅在KiranStyle下生效，其他Style中仅绘制成Button
 * <img src="../snapshot/kiran-switch-button.png" alt="kiran-switch-button" style="zoom:90%;" />
 *
 * 使用说明
 *
 * 通过 `isChecked` 方法获取开关状态,通过 `setChecked`　方法来设置开关状态
 * 通过连接到QAbstractButton::toggled(bool checked)来处理开关变化
 *
 * @since 2.1.0
 * @see QAbstractButton
 */
class Q_DECL_EXPORT KiranSwitchButton : public QAbstractButton{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSwitchButton);
public:
    /**
     * @brief KiranSwitchButton构造方法
     * @param parent 父控件
     */
    explicit KiranSwitchButton(QWidget* parent = nullptr);
    /**
     * @brief KiranSwitchButton析构方法
     */
    ~KiranSwitchButton();

    /**
     * @see QWidget::sizeHint()
     */
    virtual QSize sizeHint() const override;

    /**
     * @see QWidget::minimumSizeHint()
     */
    virtual QSize minimumSizeHint() const override;

private:
    void initStyleOption(QStyleOptionButton* option) const;
    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    /* KiranSwitchButton私有类指针 */
    KiranSwitchButtonPrivate *d_ptr;
};


#endif //KIRANSTYLE_SWITCH_BUTTON_H
