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
 
#include "kiran-image-selector-private.h"
#include "kiran-image-selector.h"
#include "kiran-image-list.h"
#include "kiran-image-button.h"

#include <QHBoxLayout>
#include <QDir>
#include <QStringList>
#include <QScrollBar>
#include <QEvent>
#include <QWheelEvent>

#define SEARCH_DIR "/usr/share/backgrounds/kiran/"

KiranImageSelectorPrivate::KiranImageSelectorPrivate(QObject *parent)
    :QObject(parent) {

}

KiranImageSelectorPrivate::~KiranImageSelectorPrivate() {

}

void KiranImageSelectorPrivate::init(KiranImageSelector *ptr) {

    q_ptr = ptr;
    q_ptr->installEventFilter(this);

    QHBoxLayout *qhBoxLayout = new QHBoxLayout(q_ptr);

    m_selectorList = new KiranImageList(q_ptr);
    m_selectorList->setFrameShape(QFrame::NoFrame);
    m_selectorList->setContentsMargins(15, 15, 15, 15);

    auto pFunction = [this]() {
        int max = m_selectorList->horizontalScrollBar()->maximum();
        int min = m_selectorList->horizontalScrollBar()->minimum();
        int currentValue = m_selectorList->horizontalScrollBar()->value();

        bool showPrev = false, showNext = false;
        if (currentValue != min) {
            showPrev = true;
        }
        if (currentValue != max) {
            showNext = true;
        }
        m_prevBtn->setVisible(showPrev);
        m_nextBtn->setVisible(showNext);
    };
    connect(m_selectorList->horizontalScrollBar(), &QScrollBar::rangeChanged, pFunction);
    connect(m_selectorList->horizontalScrollBar(), &QScrollBar::valueChanged, pFunction);

    qhBoxLayout->addWidget(m_selectorList);

    m_prevBtn = new KiranImageButton(q_ptr, true);
    m_prevBtn->setObjectName("image_selector_prev");
    m_prevBtn->setIcon(QIcon::fromTheme("window"));
    m_prevBtn->setFixedWidth(22);
    m_prevBtn->raise();
    connect(m_prevBtn, &KiranImageButton::clicked, [this]() {
        m_selectorList->scrollToPrev(1);
    });

    m_nextBtn = new KiranImageButton(q_ptr, false);
    m_nextBtn->setObjectName("image_selector_next");
    m_nextBtn->setIcon(QIcon::fromTheme("window"));
    m_nextBtn->setFixedWidth(22);
    m_nextBtn->raise();
    connect(m_nextBtn, &KiranImageButton::clicked, [this]() {
        m_selectorList->scrollToNext(1);
    });
}

bool KiranImageSelectorPrivate::eventFilter(QObject *watched, QEvent *event) {
    switch (event->type()) {
        case QEvent::Wheel:
        {
            QWheelEvent* wheelEvent = dynamic_cast<QWheelEvent*>(event);
            int step = wheelEvent->delta() / 8 / 15;
            if (step < 0) {
                m_selectorList->scrollToNext(qAbs(step));
                event->accept();
            } else {
                m_selectorList->scrollToPrev(qAbs((step)));
                event->accept();
            }
            break;
        }
        default:
            break;
    }
    return QObject::eventFilter(watched, event);
}
