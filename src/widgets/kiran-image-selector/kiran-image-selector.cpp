//
// Created by lxh on 2021/1/14.
//

#include "kiran-image-selector.h"
#include "kiran-image-list.h"
#include "kiran-image-button.h"

#include <QBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QListWidget>
#include <QApplication>
#include <QScrollBar>
#include <QDateTime>
#include <QWheelEvent>

KiranImageSelector::KiranImageSelector(QWidget *parent) {
    initUI();
}

KiranImageSelector::~KiranImageSelector() {

}

void KiranImageSelector::initUI() {
    QHBoxLayout *qhBoxLayout = new QHBoxLayout(this);
    qhBoxLayout->setMargin(0);

    m_selectorList = new KiranImageList(this);
    m_selectorList->setContentsMargins(15, 15, 15, 15);

    loadImageItems();

    auto automatciPrevNextButton = [this]() {
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
    connect(m_selectorList->horizontalScrollBar(), &QScrollBar::rangeChanged, automatciPrevNextButton);
    connect(m_selectorList->horizontalScrollBar(), &QScrollBar::valueChanged, automatciPrevNextButton);

    qhBoxLayout->addWidget(m_selectorList);

    m_prevBtn = new KiranImageButton(this, KiranImageButton::Anchor_Left);
    m_prevBtn->setIcon(QIcon::fromTheme("window"));
    m_prevBtn->setFixedWidth(22);
    m_prevBtn->raise();
    connect(m_prevBtn, &KiranImageButton::clicked, [this]() {
        m_selectorList->scrollToPrev(1);
    });

    m_nextBtn = new KiranImageButton(this, KiranImageButton::Anchor_Right);
    m_nextBtn->setIcon(QIcon::fromTheme("window"));
    m_nextBtn->setFixedWidth(22);
    m_nextBtn->raise();
    connect(m_nextBtn, &KiranImageButton::clicked, [this]() {
        m_selectorList->scrollToNext(1);
    });
}

#define SEARCH_DIR "/usr/share/backgrounds/kiran/"

#include <QDir>
#include <QStringList>

void KiranImageSelector::loadImageItems() {
    QDir dir(SEARCH_DIR);
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList() << "*.jpg" << "*.png", QDir::Files);
    for (QFileInfo fileInfo:fileInfoList) {
        auto item = m_selectorList->addImageItem(fileInfo.absoluteFilePath());

    }
}

void KiranImageSelector::wheelEvent(QWheelEvent *event) {
    int step = event->delta() / 8 / 15;
    if (step < 0) {
        m_selectorList->scrollToNext(qAbs(step));
        event->accept();
    } else {
        m_selectorList->scrollToPrev(qAbs((step)));
        event->accept();
    }
}
