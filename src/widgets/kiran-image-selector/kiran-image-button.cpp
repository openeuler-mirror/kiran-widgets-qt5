//
// Created by lxh on 2021/1/18.
//

#include "kiran-image-button.h"
#include "style.h"

#include <QEvent>
#include <QResizeEvent>

KiranImageButton::KiranImageButton(QWidget *parent, KiranImageButton::AnchorPosition position)
        : QPushButton(parent),
          m_anchorPosition(position) {
    parent->installEventFilter(this);
}

KiranImageButton::~KiranImageButton() {

}

bool KiranImageButton::eventFilter(QObject *watched, QEvent *event) {
    switch (event->type()) {
        case QEvent::Resize: {
            QSize size = dynamic_cast<QResizeEvent *>(event)->size();
            this->setFixedHeight(size.height());
            this->move(m_anchorPosition == Anchor_Left ? QPoint(0, 0) : QPoint(size.width() - rect().width(), 0));
            break;
        }
        default:
            break;
    }
    return QObject::eventFilter(watched, event);
}