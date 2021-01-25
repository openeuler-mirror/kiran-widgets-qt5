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

class KiranImageList;
class KiranImageButton;
class KiranImageSelector : public QWidget {
    Q_OBJECT
public:
    KiranImageSelector(QWidget *parent = nullptr);

public:
    ~KiranImageSelector();

private:
    void initUI();

    void loadImageItems();

protected:
    virtual void wheelEvent(QWheelEvent *event) override;


private:
    KiranImageList *m_selectorList;
    KiranImageButton *m_prevBtn;
    KiranImageButton *m_nextBtn;
};


#endif //KIRANWIDGETS_QT5_KIRAN_IMAGE_SELECTOR_H
