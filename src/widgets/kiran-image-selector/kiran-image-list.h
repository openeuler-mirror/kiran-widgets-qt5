/**
 *@file  kiran-image-list-view.h
 *@brief 
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
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

    /* 往图片选择器中添加图片 */
    KiranImageItem *addImageItem(const QString &imagePath);
    /* 添加图片项 */
    void addImageItem(KiranImageItem *item);

    /* 根据List大小调整图标项大小 */
    void updateItemSize(const QSize &size);

    /* 设置图片项之间的间距 */
    void setItemSpacing(int spacing);
    /* 设置图片上下间距 */
    void setItemUpAndDownSidesMargin(int margin);

    void scrollToNext(int step);
    void scrollToPrev(int step);

public slots:
    /* 更新可见的Item图片 */
    void updateImageItem();

private slots:
    void handlerImageItemSelectedChanged();

private:
    void initUI();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;

private:
    QHBoxLayout *m_viewportLayout;
    QWidget *m_viewportWidget;
    QSpacerItem *m_spacerItem;
    QList<KiranImageItem *> m_itemList;
    QTimer m_updateTimer;
    QPropertyAnimation m_scrollAnimation;
};

#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_LIST_VIEW_H