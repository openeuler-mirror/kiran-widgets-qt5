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
#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_ITEM_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_ITEM_H

#include <QWidget>
#include <QFuture>
#include <QPixmap>
#include <QFutureWatcher>
#include <QSvgRenderer>

/**
 * @brief KiranImageSelector图片选择器中的图片项
 */
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
    void drawHoverIndicator(QPainter &painter);
    void drawMask(QPainter &painter);
    void drawLoadingImage(QPainter &painter);

protected slots:
    void loadPixmapFinished(QString imagePath, QSize imageSize, QPixmap map);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void leaveEvent(QEvent *event) override;

    virtual void enterEvent(QEvent *event) override;

private:
    QString m_imagePath;
    QPair<QSize, QPixmap> m_previewPixmap;
    bool m_isDown;
    bool m_isSelected = false;
    bool m_isHover = false;
};


#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_ITEM_H
