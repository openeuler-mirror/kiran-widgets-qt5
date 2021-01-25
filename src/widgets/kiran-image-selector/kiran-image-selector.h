/**
 *@file  kiran-image-selector.h
 *@brief Kiran桌面图片选择器
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H
#define KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H

#include <QWidget>
#include <QRect>
#include "kiran-image-selector-private.h"

class KiranImageSelectorPrivate;
class KiranImageSelector : public QWidget {
    Q_DECLARE_PRIVATE(KiranImageSelector)
    Q_OBJECT
public:
    KiranImageSelector(QWidget *parent = nullptr);
    ~KiranImageSelector();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    KiranImageSelectorPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H
