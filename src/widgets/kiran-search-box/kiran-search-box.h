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
 * @brief 搜索框，在KiranStyle下提供特殊的绘制,使用方法可见QLineEdit
 * 只有才KiranStyle下才支持绘制，其他Style下绘制出来只是个普通输入框
 * <img src="../snapshot/kiran-search-box.png" alt="kiran-search-box.png" style="zoom:90%;" />
 *
 * 使用说明
 *
 *　和QLineEdit一样的用法
 *
 * @since 2.1.0
 * @see QLineEdit
 */
class Q_DECL_EXPORT KiranSearchBox :public QLineEdit{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSearchBox)
public:
    /**
     * @brief KiranSearchBox构造方法
     * @param parent 父控件
     */
    explicit KiranSearchBox(QWidget *parent = nullptr);

    /**
     * @brief KiranSearchBox析构方法
     */
    ~KiranSearchBox();

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranSearchBoxPrivate* d_ptr;
};


#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
