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

#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_LIST_VIEW_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_LIST_VIEW_H

#include <QScrollArea>
#include <QList>
#include <QTimer>
#include <QPropertyAnimation>

class QHBoxLayout;
class QWidget;
class KiranImageItem;
class QSpacerItem;

class KiranImageList : public QScrollArea {
    Q_OBJECT
public:
    KiranImageList(QWidget *parent = nullptr);
    ~KiranImageList();

    QString selectedImage();
    bool setSelectedImage(const QString& selectedImage);

    /* 添加图片 */
    KiranImageItem *addImageItem(const QString &imagePath);
    void addImageItem(KiranImageItem *item);

    /* 删除图片项 */
    void removeImageItem(const QString &imagePath);
    void removeImageItem(KiranImageItem *item);

    QStringList imageList();

    /* 根据List大小调整图标项大小 */
    void updateItemSize(const QSize &size);

    /* 获取图片项之间的间距 */
    quint64 itemSpacing();
    /* 设置图片项之间的间距 */
    void setItemSpacing(quint64 spacing);

    /* 获取图片上下间距 */
    quint64 itemUpAndDownSidesMargin();
    /* 设置图片上下间距 */
    void setItemUpAndDownSidesMargin(quint64 margin);

    void scrollToNext(int step);
    void scrollToPrev(int step);

public slots:
    /* 更新可见的Item图片 */
    void updateImageItem();

private slots:
    void handlerImageItemSelectedChanged();

signals:
    void selectedImageChanged(QString imagePath);

private:
    void initUI();
    void ensureSelectedItemVisible( KiranImageItem* selectedItem = nullptr );
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;

private:
    QHBoxLayout *m_viewportLayout;
    QWidget *m_viewportWidget;
    QSpacerItem *m_spacerItem;
    QList<KiranImageItem *> m_itemList;
    QString m_selectedImagePath;
    QTimer m_updateTimer;
    QPropertyAnimation m_scrollAnimation;
};

#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_LIST_VIEW_H