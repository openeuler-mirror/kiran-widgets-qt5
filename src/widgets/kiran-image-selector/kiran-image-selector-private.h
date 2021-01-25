/**
 *@file  kiran-image-selector-private.h
 *@brief 
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_PRIVATE_H

#include <QObject>

class KiranImageSelector;
class KiranImageList;
class KiranImageButton;
class KiranImageSelectorPrivate : public QObject{
    Q_DECLARE_PUBLIC(KiranImageSelector)
    Q_OBJECT
public:
    KiranImageSelectorPrivate(QObject* parent = nullptr);
    ~KiranImageSelectorPrivate();

private:
    void init(KiranImageSelector *ptr);

public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void loadImageItems();

private:
    KiranImageSelector *q_ptr = nullptr;
    KiranImageList *m_selectorList = nullptr;
    KiranImageButton *m_prevBtn = nullptr;
    KiranImageButton *m_nextBtn = nullptr;

};

#endif //KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_PRIVATE_H
