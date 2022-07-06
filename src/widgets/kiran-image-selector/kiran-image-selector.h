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
 
#ifndef KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H
#define KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H

#include <QWidget>
#include <QRect>
#include <QStyleOption>

class KiranImageSelectorPrivate;

/**
 * @brief 图片选择控件,提供动态异步加载和删除
 * @since 2.1.1
 */
class KiranImageSelector : public QWidget {
    Q_DECLARE_PRIVATE(KiranImageSelector)
    Q_OBJECT
public:
    KiranImageSelector(QWidget *parent = nullptr);
    ~KiranImageSelector();

    /**
     * @brief 获取当前显示的图片列表
     * @return 图片路径列表
     */
    QStringList imageList();

    /**
     * @brief 往图片选择器中添加图片
     * @param image 图片路径
     * @return 添加是否成功，不允许添加重复图片
     */
    bool addImage(const QString& image);

    /**
     * @brief 往图片选择器中添加多个图片
     * @param imageList 图片列表路径
     */
    void addImages(const QStringList& imageList);

    /**
     * @brief 从图片选择器中删除指定图片项
     * @param image 图片项的路径
     */
    void removeImage(const QString& image);

    /**
     * @brief 从图片选择中删除指定列表的多个图片项
     * @param imageList 图片项列表
     */
    void removeImages(const QStringList& imageList);

    /**
     * @brief 获取图片选择器中当前选中的项
     * @return  当前选中的项的路径
     */
    QString selectedImage();

    /**
     * @brief 设置图片选择器中当前选中的项
     * @param imagePath 需选择的图片路径
     * @return 是否成功
     */
    bool setSelectedImage(const QString& imagePath);

    /**
     * @brief 获取图片项和图片项之间的间隔
     * @return 图片项和图片项之间的间隔
     */
    quint64 itemSpacing();

    /**
     * @brief 设置图片项和图片项之间的间隔
     * @param spacing 图片项和图片项之间的间隔
     */
    void setItemSpacing(quint64 spacing);

    /**
     * @brief 获取图片项上下边距
     * @return 图片项上下边距
     */
    quint64 itemUpAndDownSidesMargin();

    /**
     * @brief 设置图片项上下边距
     * @param margin 图片项上下边距
     */
    void setItemUpAndDownSidesMargin(quint64 margin);

signals:
    /**
     * @brief 图片当前选择项改变时发送的信号
     * @param image 选择项的图片路径
     */
    void selectedImageChanged(QString image);

protected:
    virtual bool event(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    KiranImageSelectorPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H
