//
// Created by lxh on 2021/1/14.
//

#include "kiran-image-list.h"
#include "kiran-image-item.h"
#include "kiran-image-load-manager.h"
#include "kiran-image-selector-global.h"

#include <QDebug>
#include <QWidget>
#include <QBoxLayout>
#include <QtMath>
#include <QResizeEvent>
#include <QScrollBar>

KiranImageList::KiranImageList(QWidget *parent) : QScrollArea(parent) {
    initUI();
    m_updateTimer.setInterval(200);
    m_updateTimer.setSingleShot(true);
    connect(&m_updateTimer, &QTimer::timeout,
            this, &KiranImageList::updateImageItem);
    connect(horizontalScrollBar(),&QScrollBar::valueChanged,[this]{
        m_updateTimer.start();
    });
}

KiranImageList::~KiranImageList() {

}

void KiranImageList::initUI() {
    //设置滚动条常隐藏
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //设置ViewPort窗口,layout
    m_viewportWidget = new QWidget(this);
    m_viewportWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_viewportWidget->setObjectName("KiranImageListViewport");
    m_viewportWidget->setStyleSheet("QWidget#KiranImageListViewport{background:#191919;}");
    setWidget(m_viewportWidget);
    setWidgetResizable(true);

    m_viewportLayout = new QHBoxLayout(m_viewportWidget);
    m_viewportLayout->setSpacing(12);
    m_viewportLayout->setContentsMargins(0, 10, 0, 10);
    m_spacerItem = new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_viewportLayout->addItem(m_spacerItem);

    //安装滚动动画在水平滚动条value属性
    m_scrollAnimation.setTargetObject(horizontalScrollBar());
    m_scrollAnimation.setPropertyName("value");
    m_scrollAnimation.setEasingCurve(QEasingCurve::OutQuint);
}

KiranImageItem *KiranImageList::addImageItem(const QString &imagePath) {
    KiranImageItem *item = new KiranImageItem(this, imagePath);
    item->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    addImageItem(item);
    return item;
}

void KiranImageList::addImageItem(KiranImageItem *item) {
    m_itemList.append(item);
    m_viewportLayout->insertWidget(m_viewportLayout->count() - 1, item, 0, Qt::AlignVCenter | Qt::AlignLeft);
    m_viewportWidget->adjustSize();
    connect(item, &KiranImageItem::itemIsSelected,
            this, &KiranImageList::handlerImageItemSelectedChanged);
}

void KiranImageList::showEvent(QShowEvent *event) {
    QScrollArea::showEvent(event);
}

void KiranImageList::resizeEvent(QResizeEvent *event) {
    updateItemSize(event->size());
    m_viewportWidget->adjustSize();
    m_updateTimer.start();
    QScrollArea::resizeEvent(event);
}

/*延时调用*/
void KiranImageList::updateImageItem() {
    KiranImageLoadManager::instance()->reset();
    QRect imageListRect = rect();
    for (KiranImageItem *item:m_itemList) {
        /* 只更新显示项的图片 */
        /* 将图片项的位置转换成在ImageList中的位置 */
        QRect itemMappedRect(item->mapTo(this, QPoint(0, 0)), item->size());
        if (imageListRect.intersects(itemMappedRect)) {
            item->updatePixmap();
        }
    }
}

void KiranImageList::setItemSpacing(int spacing) {
    m_viewportLayout->setSpacing(spacing);
}

void KiranImageList::setItemUpAndDownSidesMargin(int margin) {
    QMargins margins = m_viewportLayout->contentsMargins();
    margins.setTop(margin);
    margins.setBottom(margin);
    m_viewportLayout->setContentsMargins(margins);
}

void KiranImageList::updateItemSize(const QSize &size) {
    int topBottomMargin = m_viewportLayout->contentsMargins().top();
    int itemHeight = size.height() - (2 * topBottomMargin);

    /* 根据高度生成合适的尺寸 */
    QSize fitSize = QSize(qFloor(itemHeight * IMAGE_ITEM_ASPECT_RATIO), itemHeight);

    /* 若宽度显示不全，则忽略margin，直接以当前宽度生成尺寸 */
    if (size.width() < fitSize.width()) {
        int itemWidth = size.width();
        fitSize = QSize(itemWidth, qFloor(itemWidth / IMAGE_ITEM_ASPECT_RATIO));
    }

    for (auto iter:m_itemList) {
        iter->setFixedSize(fitSize);
    }
}

void KiranImageList::scrollToNext(int step) {
    if (m_itemList.size() == 0) {
        return;
    }
    if(m_scrollAnimation.state()==QPropertyAnimation::Running){
        return;
    }

    int itemWidth = m_itemList.at(0)->width();
    int layoutSpacing = m_viewportLayout->spacing();
    int scrollValue = horizontalScrollBar()->value();

    m_scrollAnimation.setDuration(150);
    m_scrollAnimation.setStartValue(horizontalScrollBar()->value());
    m_scrollAnimation.setEndValue(scrollValue + (itemWidth + layoutSpacing) * step);
    m_scrollAnimation.start();
}

void KiranImageList::scrollToPrev(int step) {
    if (m_itemList.size() == 0) {
        return;
    }
    if(m_scrollAnimation.state()==QPropertyAnimation::Running){
        return;
    }

    int itemWidth = m_itemList.at(0)->width();
    int layoutSpacing = m_viewportLayout->spacing();
    int scrollValue = horizontalScrollBar()->value();

    m_scrollAnimation.setDuration(150);
    m_scrollAnimation.setStartValue(horizontalScrollBar()->value());
    m_scrollAnimation.setEndValue(scrollValue - (itemWidth + layoutSpacing) * step);
    m_scrollAnimation.start();
}


void KiranImageList::handlerImageItemSelectedChanged() {
    KiranImageItem *senderItem = qobject_cast<KiranImageItem *>(sender());
    for (KiranImageItem *item:m_itemList) {
        if (item != senderItem) {
            item->setIsSelected(false);
        }
    }
}