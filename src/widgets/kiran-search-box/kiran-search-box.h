/*
 * @file   kiran-search-box.h
 * @brief  Kiran搜索框
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
#define KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H

#include <QLineEdit>

class KiranSearchBoxPrivate;
class QLineEdit;
class QStyleOption;

/**
 * @brief 搜索框，只有才KiranStyle下才支持绘制搜索图标，其他Style下绘制出来只是个普通输入框
 * @since kiranwidgets-qt5-2.1.0
 */
class Q_DECL_EXPORT KiranSearchBox :public QLineEdit{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSearchBox)
public:
    explicit KiranSearchBox(QWidget *parent = nullptr);
    ~KiranSearchBox();

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranSearchBoxPrivate* d_ptr;
};


#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
