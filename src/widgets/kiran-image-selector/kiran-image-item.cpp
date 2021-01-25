//
// Created by lxh on 2021/1/15.
//

#include "kiran-image-item.h"
#include "kiran-image-load-manager.h"
#include "kiran-image-selector-global.h"

#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QtConcurrent>
#include <utility>
#include <QMouseEvent>


KiranImageItem::KiranImageItem(QWidget *parent, const QString &path)
        : QWidget(parent),
          m_imagePath(path) {
    setObjectName(QString("imgageItem_%1").arg(path));
    connect(KiranImageLoadManager::instance(), &KiranImageLoadManager::imageLoaded,
            this, &KiranImageItem::loadPixmapFinished, Qt::QueuedConnection);
}

KiranImageItem::~KiranImageItem() {

}

void KiranImageItem::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    bool imageIsLoaded = false;

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
    }
}

void KiranImageItem::mousePressEvent(QMouseEvent *event) {
    qInfo() << m_imagePath << "pressed";
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
        qInfo() << "update" << imagePath << imageSize;
    }
}

void KiranImageItem::updatePixmap() {
    if (m_previewPixmap.first == size() && !m_previewPixmap.first.isNull()) {
        return;
    }
    KiranImageLoadManager::instance()->load(m_imagePath, size());
}

void KiranImageItem::drawSelectedIndicator(QPainter &painter) {
    static QSvgRenderer selectedRender(QString(":/images/selected.svg"));

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
    qInfo() << m_imagePath << "release";
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
    static QSvgRenderer loadingRender(QString(":/images/loading.svg"));
    QRect widgetRect = rect();
    qreal widgetScaledFactor = widgetRect.width() / IMAGE_ITEM_DEFAULT_WIDTH;
    QSize loadingSize(loadingRender.defaultSize().width() * widgetScaledFactor,
                      loadingRender.defaultSize().height() * widgetScaledFactor);
    QRect loadingRect(
            QPoint((widgetRect.width() - loadingSize.width()) / 2, (widgetRect.height() - loadingSize.height()) / 2),
            loadingSize);
    loadingRender.render(&painter, loadingRect);
}
