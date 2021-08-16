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
