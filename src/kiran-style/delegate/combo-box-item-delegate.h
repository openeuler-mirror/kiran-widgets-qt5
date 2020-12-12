//
// Created by lxh on 2020/11/30.
//

#ifndef KIRANSTYLE_COMBO_BOX_ITEM_DELEGATE_H
#define KIRANSTYLE_COMBO_BOX_ITEM_DELEGATE_H

#include <QItemDelegate>

class QComboBox;
class ComboBoxItemDelegate : public QItemDelegate{
    Q_OBJECT
public:
    ComboBoxItemDelegate(QComboBox* comboBox,QObject* parent = nullptr);
    ~ComboBoxItemDelegate();

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    QStyleOptionMenuItem getStyleOptionMenuItem(const QStyleOptionViewItem *option,
                                                const QModelIndex &index) const;

private:
    QComboBox *m_bindingComboBox;
};


#endif //KIRANSTYLE_COMBO_BOX_ITEM_DELEGATE_H
