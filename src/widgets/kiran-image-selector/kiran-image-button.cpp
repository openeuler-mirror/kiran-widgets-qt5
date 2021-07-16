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
 

#include "kiran-image-button.h"
#include "style.h"

#include <QEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QStyleOption>

KiranImageButton::KiranImageButton(QWidget *parent, bool leftSide)
        : QPushButton(parent),
          m_anchorParentLeftSide(leftSide) {
    parent->installEventFilter(this);
}

KiranImageButton::~KiranImageButton() {

}

bool KiranImageButton::eventFilter(QObject *watched, QEvent *event) {
    switch (event->type()) {
        case QEvent::Resize: {
            QSize size = dynamic_cast<QResizeEvent *>(event)->size();
            this->setFixedHeight(size.height());
            this->move(m_anchorParentLeftSide ? QPoint(0, 0) : QPoint(size.width() - rect().width(), 0));
            break;
        }
        default:
            break;
    }
    return QObject::eventFilter(watched, event);
}

void KiranImageButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QStyleOptionButton option;
    option.init(this);
    if( QPushButton::isDown() ){
        option.state |= QStyle::State_Sunken;
    }
    if( Kiran::Style::isKiranStyle() ){
        auto style = Kiran::Style::castToKiranStyle();
        style->drawPrimitive(Kiran::PE_KiranImageSelectorButtonFrame,&option,&painter,this);
        style->drawPrimitive(m_anchorParentLeftSide?Kiran::PE_KiranImageSelectorPrevButtonArrow:Kiran::PE_KiranImageSelectorNextButtonArrow,
                             &option,
                             &painter,
                             this);
    }
}

bool KiranImageButton::anchorParentLeftSide() {
    return m_anchorParentLeftSide;
}
