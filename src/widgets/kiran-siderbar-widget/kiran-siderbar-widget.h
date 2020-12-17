//
// Created by lxh on 2020/12/15.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_H
#define KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_H

#include <QListWidget>

class KiranSiderbarWidgetPrivate;

class KiranSiderbarWidget : public QListWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSiderbarWidget)
public:
    explicit KiranSiderbarWidget(QWidget *parent = nullptr);

    ~KiranSiderbarWidget();

protected:
    virtual QItemSelectionModel::SelectionFlags
    selectionCommand(const QModelIndex &index, const QEvent *event = Q_NULLPTR) const override;

private:
    KiranSiderbarWidgetPrivate *d_ptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SIDERBAR_WIDGET_H
