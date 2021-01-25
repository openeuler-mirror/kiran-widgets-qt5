/**
 *@file  kiran-image-selector-item.h
 *@brief 
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
 */
#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_ITEM_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_ITEM_H

#include <QWidget>
#include <QFuture>
#include <QPixmap>
#include <QFutureWatcher>
#include <QSvgRenderer>

class KiranImageItem : public QWidget {
Q_OBJECT
    Q_PROPERTY(bool isSelected READ isSelected WRITE setIsSelected NOTIFY isSelectedChanged);
public:
    KiranImageItem(QWidget *parent, const QString &path);
    ~KiranImageItem();

    QString imagePath();
    void updatePixmap();

    bool isSelected();
    void setIsSelected(bool selected);

signals:
    void isSelectedChanged(bool isSelected);
    void itemIsSelected();

private:
    virtual QSize sizeHint() const;

    void drawSelectedIndicator(QPainter &painter);
    void drawMask(QPainter &painter);
    void drawLoadingImage(QPainter &painter);

protected slots:
    void loadPixmapFinished(QString imagePath, QSize imageSize, QPixmap map);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

private:
    QString m_imagePath;
    QPair<QSize, QPixmap> m_previewPixmap;
    bool m_isDown;
    bool m_isSelected = false;
};


#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_ITEM_H
