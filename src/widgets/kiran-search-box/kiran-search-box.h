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
class Q_DECL_EXPORT KiranSearchBox : public QLineEdit
{
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
    KiranSearchBoxPrivate *d_ptr;
};

#endif  // KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
