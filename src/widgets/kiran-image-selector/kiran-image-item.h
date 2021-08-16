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
