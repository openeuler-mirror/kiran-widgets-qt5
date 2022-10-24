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
 

#include "kiran-image-item.h"
#include "kiran-image-load-manager.h"
#include "kiran-image-selector-global.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QtConcurrent>
#include <utility>
#include <QMouseEvent>

#include "style.h"
#include <QStyleOption>
#include <QPainter>

KiranImageItem::KiranImageItem(QWidget *parent, const QString &path)
        : QWidget(parent),
          m_imagePath(path) {
    setAttribute(Qt::WA_Hover,true);
    setObjectName(QString("imgageItem_%1").arg(path));
    setAccessibleName("KiranImageItem");
    setToolTip(path);
    connect(KiranImageLoadManager::instance(), &KiranImageLoadManager::imageLoaded,
            this, &KiranImageItem::loadPixmapFinished, Qt::QueuedConnection);
}

KiranImageItem::~KiranImageItem() {

}

void KiranImageItem::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    bool imageIsLoaded = false;

    //NOTE:ImageItem绘制过程由自己绘制不在Style中绘制的原因是由于不想再次图片在内存中再次拷贝传递给Style
    if (m_previewPixmap.first == size() && !m_previewPixmap.second.isNull()) {
        QSize scaledPixmapSize = m_previewPixmap.second.size();
        QSize size = geometry().size();
        QRect drawTargetRect((scaledPixmapSize.width() - size.width()) / -2,
                             (scaledPixmapSize.height() - size.height()) / -2,
                             scaledPixmapSize.width(),
                             scaledPixmapSize.height());
        p.drawPixmap(drawTargetRect, m_previewPixmap.second, m_previewPixmap.second.rect());
        imageIsLoaded = true;
    } else {
        p.fillRect(rect(), QBrush(QColor("#292929")));
        drawLoadingImage(p);
    }

    if (m_isSelected) {
        drawSelectedIndicator(p);
    } else {
        /* 没加载完成不绘制遮罩 */
        if (imageIsLoaded) {
            drawMask(p);
        }
        if ( m_isHover ){
            drawHoverIndicator(p);
        }
    }
}

void KiranImageItem::mousePressEvent(QMouseEvent *event) {
    m_isDown = true;
    event->accept();
}

QSize KiranImageItem::sizeHint() const {
    return QSize(212, 148);
}

void KiranImageItem::loadPixmapFinished(QString imagePath, QSize imageSize, QPixmap pixmap) {
    if (imagePath == m_imagePath) {
        m_previewPixmap.first = imageSize;
        m_previewPixmap.second = std::move(pixmap);
        update();
    }
}

void KiranImageItem::updatePixmap() {
    if (m_previewPixmap.first == size() && !m_previewPixmap.first.isNull()) {
        return;
    }
    KiranImageLoadManager::instance()->load(m_imagePath, size());
}

void KiranImageItem::drawSelectedIndicator(QPainter &painter) {
    static QSvgRenderer selectedRender(QString(":/kiranwidgets-qt5/images/image-selector/selected.svg"));

    painter.save();

    QPen pen(QColor("#2094fc"));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect().adjusted(1, 1, -1, -1));

    QRect widgetRect = rect().adjusted(0, 0, -2, -2);
//    qreal widgetScaledFactor = widgetRect.width()/IMAGE_ITEM_DEFAULT_WIDTH;
//    QSize selectedSize(selectedRender.defaultSize().width() * widgetScaledFactor,
//                       selectedRender.defaultSize().height() * widgetScaledFactor);
    QSize selectedSize = selectedRender.defaultSize();
    QRect selectedRect(widgetRect.width() - selectedSize.width() - 4,
                       widgetRect.height() - selectedSize.height() - 4,
                       selectedSize.width(), selectedSize.height());
    selectedRender.render(&painter, selectedRect);

    painter.restore();
}

void KiranImageItem::drawHoverIndicator(QPainter &painter) {
    painter.save();
    QPen pen(QColor(229,235,246,0.5*255));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect().adjusted(1,1,-1,-1));
    painter.restore();
}

void KiranImageItem::drawMask(QPainter &painter) {
    painter.save();
    QBrush brush(QColor(0, 0, 0, 0.5 * 255));
    painter.fillRect(rect(), brush);
    painter.restore();
}

QString KiranImageItem::imagePath() {
    return m_imagePath;
}

void KiranImageItem::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }
    if (m_isDown) {
        setIsSelected(true);
    }

    m_isDown = false;
}

bool KiranImageItem::isSelected() {
    return m_isSelected;
}

void KiranImageItem::setIsSelected(bool selected) {
    if (m_isSelected != selected) {
        m_isSelected = selected;
        emit isSelectedChanged(m_isSelected);
        if (m_isSelected) {
            emit itemIsSelected();
        }
        update();
    }
}

void KiranImageItem::drawLoadingImage(QPainter &painter) {
    static QSvgRenderer loadingRender(QString(":/kiranwidgets-qt5/images/image-selector/loading.svg"));
    QRect widgetRect = rect();
    qreal widgetScaledFactor = widgetRect.width() / IMAGE_ITEM_DEFAULT_WIDTH;
    QSize loadingSize(loadingRender.defaultSize().width() * widgetScaledFactor,
                      loadingRender.defaultSize().height() * widgetScaledFactor);
    QRect loadingRect(QPoint((widgetRect.width() - loadingSize.width()) / 2, (widgetRect.height() - loadingSize.height()) / 2),
            loadingSize);
    loadingRender.render(&painter, loadingRect);
}

void KiranImageItem::enterEvent(QEvent *event) {
    m_isHover = true;
    QWidget::enterEvent(event);
}

void KiranImageItem::leaveEvent(QEvent *event) {
    m_isHover = false;
    QWidget::leaveEvent(event);
}