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
