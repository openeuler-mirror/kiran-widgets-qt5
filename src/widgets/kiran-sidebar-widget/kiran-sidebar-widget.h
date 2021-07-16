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
 
#ifndef KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H
#define KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H

#include <QListWidget>

class KiranSidebarWidgetPrivate;

/**
 * @brief Kiran控制中心组件侧边栏封装
 * 基于QListWidget重新实现,提供在KiranStyle下特殊的样式绘制
 * <img src="../snapshot/kiran-sidebar-widget.png" alt="kiran-sidebar-widget.png" style="zoom:90%;" />
 *
 * 使用说明
 * - 可通过QtDesigner ui文件时,右键提升为该控件
 * - 通过CPP代码新建控件加入布局之中
 *
 * @since 2.1.0
 * @see QListWidget
 */
class KiranSidebarWidget : public QListWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSidebarWidget)
public:
    /**
     * @brief KiranSidebarWidget构造方法
     * @param parent 父控件
     */
    explicit KiranSidebarWidget(QWidget *parent = nullptr);

    /**
     * @brief KiranSidebarWidget析构方法
     */
    ~KiranSidebarWidget();

protected:
    /* 重新实现selectionCommand，以自定义选择行为 */
    virtual QItemSelectionModel::SelectionFlags
    selectionCommand(const QModelIndex &index, const QEvent *event = Q_NULLPTR) const override;

private:
    /* KiranSidebarWidget私有类指针 */
    KiranSidebarWidgetPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H
