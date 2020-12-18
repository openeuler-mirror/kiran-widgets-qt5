/*
 * @file   kiran-siderbar-widget.h
 * @brief  Kiran控制中心组件侧边栏封装
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H
#define KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H

#include <QListWidget>

class KiranSidebarWidgetPrivate;

/**
 * @brief Kiran控制中心组件侧边栏封装
 * 基于QListWidget重新实现,提供在KiranStyle下特殊的样式绘制
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
    /**
     * @brief 重新实现selectionCommand，以自定义选择行为
     * @param index 索引
     * @param event 事件类型
     * @return 返回选择标志
     */
    virtual QItemSelectionModel::SelectionFlags
    selectionCommand(const QModelIndex &index, const QEvent *event = Q_NULLPTR) const override;

private:
    /* KiranSidebarWidget私有类指针 */
    KiranSidebarWidgetPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H
