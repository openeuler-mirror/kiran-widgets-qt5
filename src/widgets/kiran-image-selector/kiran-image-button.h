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
 
#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H

#include <QPushButton>

/**
 * @brief KiranImageSelector的两侧悬浮按钮
 *       在KiranStyle中的QPushButton绘制过程中单独通过Inherits进行特殊绘制
 */
class KiranImageButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(bool anchorParentLeftSide READ anchorParentLeftSide);
public:
    explicit KiranImageButton(QWidget *parent,bool leftSide );
    virtual ~KiranImageButton();
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    bool anchorParentLeftSide();
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    bool m_anchorParentLeftSide = false;
};


#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_BUTTON_H
