/*
 * @file   combo-box-item-delegate.h
 * @brief  QComboBox的绘制代理
 * 　　　　　KiranStyle::polish一个QComboBox时设置代理为该代理，以控制QComboBox的绘制过程
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */

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
