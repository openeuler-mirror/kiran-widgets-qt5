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
 
#ifndef KIRANSTYLE_COMBO_BOX_ITEM_DELEGATE_H
#define KIRANSTYLE_COMBO_BOX_ITEM_DELEGATE_H

#include <QItemDelegate>

class QComboBox;
/**
 * @brief QComboBox的绘制代理
 * 　　　　KiranStyle::polish一个QComboBox时设置代理为该代理，以控制QComboBox的绘制过程
 */
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
