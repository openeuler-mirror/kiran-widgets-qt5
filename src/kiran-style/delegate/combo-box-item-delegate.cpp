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
 
#include "combo-box-item-delegate.h"

#include <QComboBox>
#include <QApplication>

//TODO: installEventFilter QComboBox 感知Resize事件调整菜单高度

ComboBoxItemDelegate::ComboBoxItemDelegate(QComboBox* comboBox,QObject *parent)
    : QItemDelegate(parent),
    m_bindingComboBox(comboBox)
{

}

ComboBoxItemDelegate::~ComboBoxItemDelegate()
{

}

void ComboBoxItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionMenuItem opt = getStyleOptionMenuItem(&option, index);
    m_bindingComboBox->style()->drawControl(QStyle::CE_MenuItem, &opt, painter, m_bindingComboBox);
}

QSize ComboBoxItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QItemDelegate::sizeHint(option, index);
    return QSize(size.width(),m_bindingComboBox->height());
}

QStyleOptionMenuItem
ComboBoxItemDelegate::getStyleOptionMenuItem(const QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyleOptionMenuItem menuOption;

    QPalette resolvedpalette = option->palette.resolve(QApplication::palette("QMenu"));
    QVariant value = index.data(Qt::ForegroundRole);
    if (value.canConvert<QBrush>()) {
        resolvedpalette.setBrush(QPalette::WindowText, qvariant_cast<QBrush>(value));
        resolvedpalette.setBrush(QPalette::ButtonText, qvariant_cast<QBrush>(value));
        resolvedpalette.setBrush(QPalette::Text, qvariant_cast<QBrush>(value));
    }
    menuOption.palette = resolvedpalette;
    menuOption.state = QStyle::State_None;
    if (m_bindingComboBox->window()->isActiveWindow())
        menuOption.state = QStyle::State_Active;
    if ((option->state & QStyle::State_Enabled) && (index.model()->flags(index) & Qt::ItemIsEnabled))
        menuOption.state |= QStyle::State_Enabled;
    else
        menuOption.palette.setCurrentColorGroup(QPalette::Disabled);
    if (option->state & QStyle::State_Selected)
        menuOption.state |= QStyle::State_Selected;

    //add
    if( option->state & QStyle::State_MouseOver )
        menuOption.state |= QStyle::State_MouseOver;

    menuOption.checkType = QStyleOptionMenuItem::NonExclusive;
    menuOption.checked = m_bindingComboBox->currentIndex() == index.row();
    if (index.data(Qt::AccessibleDescriptionRole).toString()=="separator")//copy from QComboBoxDelegate::isSeparatar
        menuOption.menuItemType = QStyleOptionMenuItem::Separator;
    else
        menuOption.menuItemType = QStyleOptionMenuItem::Normal;

    QVariant variant = index.model()->data(index, Qt::DecorationRole);
    switch (variant.type()) {
        case QVariant::Icon:
            menuOption.icon = qvariant_cast<QIcon>(variant);
            break;
        case QVariant::Color: {
            static QPixmap pixmap(option->decorationSize);
            pixmap.fill(qvariant_cast<QColor>(variant));
            menuOption.icon = pixmap;
            break; }
        default:
            menuOption.icon = qvariant_cast<QPixmap>(variant);
            break;
    }
    if (index.data(Qt::BackgroundRole).canConvert<QBrush>()) {
        menuOption.palette.setBrush(QPalette::All, QPalette::Background,
                                    qvariant_cast<QBrush>(index.data(Qt::BackgroundRole)));
    }
    menuOption.text = index.model()->data(index, Qt::DisplayRole).toString()
            .replace(QLatin1Char('&'), QLatin1String("&&"));
    menuOption.tabWidth = 0;
    menuOption.maxIconWidth =  option->decorationSize.width() + 4;
    menuOption.menuRect = option->rect;
    menuOption.rect = option->rect;

    // Make sure fonts set on the model or on the combo box, in
    // that order, also override the font for the popup menu.
    QVariant fontRoleData = index.data(Qt::FontRole);
    if (fontRoleData.isValid()) {
        menuOption.font = fontRoleData.value<QFont>();
    } else if (m_bindingComboBox->testAttribute(Qt::WA_SetFont)
               || m_bindingComboBox->testAttribute(Qt::WA_MacSmallSize)
               || m_bindingComboBox->testAttribute(Qt::WA_MacMiniSize)
               || m_bindingComboBox->font() != qApp->font("QComboBox")) {
        menuOption.font = m_bindingComboBox->font();

    } else {
        menuOption.font = qApp->font("QComboBoxMenuItem");
    }

    menuOption.fontMetrics = QFontMetrics(menuOption.font);

    return menuOption;
}
