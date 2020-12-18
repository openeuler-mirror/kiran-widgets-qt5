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
 * @since kiranwidgets-qt5-2.1.0
 */
class KiranSidebarWidget : public QListWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSidebarWidget)
public:
    explicit KiranSidebarWidget(QWidget *parent = nullptr);

    ~KiranSidebarWidget();

protected:
    virtual QItemSelectionModel::SelectionFlags
    selectionCommand(const QModelIndex &index, const QEvent *event = Q_NULLPTR) const override;

private:
    KiranSidebarWidgetPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SIDEBAR_WIDGET_H
