//
// Created by lxh on 2020/11/27.
//

#include "draw-menu-helper.h"
#include "style.h"
#include "style-data/style-detail-fetcher.h"
#include "draw-common-helper.h"
#include "draw-button-helper.h"
#include "draw-combo-box-helper.h"

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QComboBox>
#include <QAbstractItemView>
#include <QApplication>
#include <QMenu>

using namespace Kiran;

#define PRIVATE_PROPERTY_ITEMS_HAS_ICON     "_kiran_menu_items_has_icon"
#define PRIVATE_PROPERTY_ITEMS_HAS_SUBMENU  "_kiran_menu_items_has_submenu"

bool DrawMenuHelper::drawMenuBarEmptryAreaControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                  StyleDetailFetcher *fetcher, const QWidget *widget)
{
    return true;
}

bool DrawMenuHelper::drawMenuBarItemControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                            StyleDetailFetcher *fetcher, const QWidget *widget)
{
    return true;
}

bool DrawMenuHelper::drawMenuEmptryAreaControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                               StyleDetailFetcher *fetcher, const QWidget *widget)
{
    return true;
}

QSize DrawMenuHelper::menuItemSizeFromContents(const Style *style, const QStyleOption *option, const QSize &contentsSize,
                                               const QWidget *widget)
{
    const QStyleOptionMenuItem* menuItemOption = qstyleoption_cast<const QStyleOptionMenuItem*>(option);
    if( !menuItemOption ){
        return contentsSize;
    }

    const QMenu* menu = qobject_cast<const QMenu*>(widget);

    bool hasIcon = false,needSubMenuArrow = false,needDrawCheckIndicator = false;

    ///判断是否该Menu所有子条目 是否存在图标,是否存在子菜单，遍历QMenu的Actions并更新到属性中
    for(const QAction*action : menu->actions()){
        if (!hasIcon)
            hasIcon = !action->icon().isNull();
        if(!needSubMenuArrow)
            needSubMenuArrow = action->menu();
        if(hasIcon && needSubMenuArrow){
            break;
        }
    }
    needDrawCheckIndicator = menuItemOption->menuHasCheckableItems;

    {
        QMenu *temp = const_cast<QMenu*>(menu);
        temp->setProperty(PRIVATE_PROPERTY_ITEMS_HAS_ICON,hasIcon);
        temp->setProperty(PRIVATE_PROPERTY_ITEMS_HAS_SUBMENU,needSubMenuArrow);
    }


    switch (menuItemOption->menuItemType) {
        case QStyleOptionMenuItem::Normal:
        case QStyleOptionMenuItem::DefaultItem:
        case QStyleOptionMenuItem::SubMenu:
        {
            QSize size(0,0);

            //icon
            if( hasIcon ){
                int iconSize = menuItemOption->maxIconWidth;
                size.rheight() = qMax(size.height(),iconSize);
                size.rwidth() += iconSize;
                size.rwidth() += Metrics::MenuItem_ItemSpacing;
            }

            //text
            size.rheight() = qMax(size.height(),contentsSize.height());
            size.rwidth() += contentsSize.width();
            size.rwidth() += Metrics::MenuItem_ItemSpacing;

            //checkedIndicator
            if(needDrawCheckIndicator){
                size.rheight() = qMax(size.height(),(int)Metrics::MenuItem_CheckedIndicatorSize);
                size.rwidth() += Metrics::MenuItem_CheckedIndicatorSize;
                size.rwidth() += Metrics::MenuItem_ItemSpacing;
            }

            //submenu arrow
            if(needSubMenuArrow){
                size.rheight() = qMax(size.height(),(int)Metrics::MenuButton_IndicatorWidth);
                size.rwidth() += Metrics::MenuButton_IndicatorWidth;
            }

            return DrawCommonHelper::expandSize(size,Metrics::MenuItem_MarginWidth);
        }
        case QStyleOptionMenuItem::Separator:
        {
            if( menuItemOption->text.isEmpty() && menuItemOption->icon.isNull() ) {
                return DrawCommonHelper::expandSize( QSize(0,1), Metrics::MenuItem_MarginWidth );
            }else{
                QSize size(contentsSize);
                int iconWidth( menuItemOption->maxIconWidth );
                int textHeight( menuItemOption->fontMetrics.height() );
                if( !menuItemOption->icon.isNull() ) size.setHeight( qMax( size.height(), iconWidth ) );
                if( !menuItemOption->text.isEmpty() )
                {
                    size.setHeight( qMax( size.height(), textHeight ) );
                    size.setWidth( qMax( size.width(), menuItemOption->fontMetrics.width( menuItemOption->text ) ) );
                }
                return DrawCommonHelper::expandSize(size,Metrics::MenuItem_MarginWidth);
            }
        }
        default:
            return contentsSize;
    }
}

bool DrawMenuHelper::drawMenuItemControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                         StyleDetailFetcher *fetcher, const QWidget *widget)
{
    if( qobject_cast<const QComboBox*>(widget) ){
        return DrawComboBoxHelper::drawComboBoxMenuItem(style,opt,p,fetcher,widget);
    }

    auto menuItemOption = qstyleoption_cast<const QStyleOptionMenuItem *>(opt);
    if (!menuItemOption) {
        return true;
    }

    if (menuItemOption->menuItemType == QStyleOptionMenuItem::EmptyArea)
        return true;

    const QStyle::State& state( opt->state );
    bool enabled( state & QStyle::State_Enabled );
    bool selected( enabled && (state & QStyle::State_Selected) );
    bool sunken( enabled && (state & (QStyle::State_On|QStyle::State_Sunken) ) );
    bool reverseLayout( opt->direction == Qt::RightToLeft );

    ///分割器绘制
    ///分割器不会绘制图标，只会绘制文字
    if (menuItemOption->menuItemType == QStyleOptionMenuItem::Separator) {
        int separatorWidth = fetcher->getInt(widget, opt, StyleDetailFetcher::Menu_SeparatorWidth);
        QColor separatorColor = fetcher->getColor(widget, opt, StyleDetailFetcher::Menu_SeparatorColor);

        bool hasText = !menuItemOption->text.isEmpty();
        bool hasIcon = !menuItemOption->icon.isNull();

        //NOTE: 不会绘制图标
        if (!hasText && !hasIcon) {//普通分割符
            DrawCommonHelper::drawSeparator(p, opt->rect, separatorColor);
            return true;
        } else {
            QRect separatorRect(opt->rect.bottomLeft() - QPoint(0, Metrics::MenuItem_MarginWidth),
                                QSize(opt->rect.width(), 1));
            DrawCommonHelper::drawSeparator(p, separatorRect, separatorColor);

            p->setFont(menuItemOption->font);
            QRect contentsRect = DrawCommonHelper::insideMargin(menuItemOption->rect, Metrics::MenuItem_MarginWidth);
            style->drawItemText(p, contentsRect, Qt::AlignCenter, menuItemOption->palette, true, menuItemOption->text,
                                QPalette::WindowText);
            return true;
        }
    }

    QColor background = fetcher->getColor(StyleDetailFetcher::Menu_ItemBackground,
                                          selected?QCss::PseudoClass_Hover:QCss::PseudoClass_Unspecified );
    QColor siderColor = fetcher->getColor(StyleDetailFetcher::Menu_ItemSiderColor,
                                          selected?QCss::PseudoClass_Hover:QCss::PseudoClass_Unspecified );

    if( background.isValid() && siderColor.isValid() ){
        p->save();

        QRect siderSignRect(opt->rect.right()-2,
                            opt->rect.top(),
                            2,
                            opt->rect.height());
        QRect backgroundRect(opt->rect.left(),
                             opt->rect.top(),
                             opt->rect.width()-siderSignRect.width(),
                             opt->rect.height());
        p->setRenderHint(QPainter::Antialiasing,true);
        p->fillRect(backgroundRect,background);
        p->fillRect(siderSignRect,siderColor);

        p->restore();
    }

    ///获取绘制选项，尝试从属性中获取出是否留出(图标、子菜单指示器、勾选指示器)空间
    bool itemsHasIcon = false,itemsHasSubMenu = false,itemsHasCheckedIndicator = false;

    QVariant itemsHasIconVar = widget->property(PRIVATE_PROPERTY_ITEMS_HAS_ICON);
    if( itemsHasIconVar.isValid() ){
        itemsHasIcon = itemsHasIconVar.toBool();
    }

    QVariant itemsHasSubMenuVar = widget->property(PRIVATE_PROPERTY_ITEMS_HAS_SUBMENU);
    if( itemsHasSubMenuVar.isValid() ){
        itemsHasSubMenu = itemsHasSubMenuVar.toBool();
    }

    itemsHasCheckedIndicator = menuItemOption->menuHasCheckableItems;

    QRect contentsRect = DrawCommonHelper::insideMargin(opt->rect,Metrics::MenuItem_MarginWidth);

    ///绘制最左的图标，移动内容矩形的左边
    if( itemsHasCheckedIndicator ){
        QRect checkedIndicatorRect(contentsRect.left(),
                                   contentsRect.top()+(contentsRect.height()-Metrics::MenuItem_CheckedIndicatorSize)/2,
                                   Metrics::MenuItem_CheckedIndicatorSize,
                                   Metrics::MenuItem_CheckedIndicatorSize);

        contentsRect.setLeft(checkedIndicatorRect.right()+Metrics::MenuItem_ItemSpacing);

        checkedIndicatorRect = style->visualRect(opt->direction,opt->rect,checkedIndicatorRect);
        if( menuItemOption->checkType == QStyleOptionMenuItem::Exclusive ){
            if( menuItemOption->checked ){
                QColor indicatorBgColor = fetcher->getColor(widget,opt,StyleDetailFetcher::Menu_CheckedIndicatorBackground);
                QColor indicatorSignColor = fetcher->getColor(widget,opt,StyleDetailFetcher::Menu_CheckedIndicatorSignColor);
                DrawCommonHelper::drawMenuCheckedIndicator(p,checkedIndicatorRect,indicatorBgColor,indicatorSignColor);
            }
        } else if( menuItemOption->checkType == QStyleOptionMenuItem::NonExclusive ){
            int pseudoClass = 0;
            pseudoClass |= menuItemOption->checked?QCss::PseudoClass_Checked:QCss::PseudoClass_Unchecked;

            QColor bgColor = fetcher->getColor(StyleDetailFetcher::CheckBox_IndicatorBackground,pseudoClass);
            QColor signColor = fetcher->getColor(StyleDetailFetcher::CheckBox_IndicatorSign,pseudoClass);
            QColor borderColor = fetcher->getColor(StyleDetailFetcher::CheckBox_BorderColor,pseudoClass);
            DrawCommonHelper::drawCheckBoxIndicator(p,checkedIndicatorRect,
                                                    borderColor,bgColor,signColor,
                                                    menuItemOption->checked?CheckOn:CheckOff);
        }

    }


    if (itemsHasIcon) {
        int iconWidth = menuItemOption->maxIconWidth;

        QRect iconRect(contentsRect.left(),
                       contentsRect.top()+(contentsRect.height()-iconWidth)/2,
                       iconWidth,iconWidth);
        contentsRect.setLeft(iconRect.right()+Metrics::MenuItem_ItemSpacing);

        iconRect = style->visualRect(opt->direction,opt->rect,iconRect);

        if( !qApp->testAttribute(Qt::AA_DontShowIconsInMenus)
            && !menuItemOption->icon.isNull()){
            QIcon::Mode iconMode;
            // icon mode
            QIcon::Mode mode;
            if( selected ) mode = QIcon::Selected;
            else if( enabled ) mode = QIcon::Normal;
            else mode = QIcon::Disabled;

            // icon state
            const QIcon::State iconState( sunken ? QIcon::On:QIcon::Off );
            QPixmap icon = menuItemOption->icon.pixmap( iconRect.size(), mode, iconState );
            p->drawPixmap( iconRect, icon );
        }
    }

    ///绘制在右侧的子菜单箭头和勾选指示器,移动内容矩形的右侧
    if( itemsHasSubMenu ){
        QRect subMenuArrowRect(contentsRect.right()-Metrics::MenuButton_IndicatorWidth,
                               contentsRect.top()+(contentsRect.height()-Metrics::MenuButton_IndicatorWidth)/2,
                               Metrics::MenuButton_IndicatorWidth,
                               Metrics::MenuButton_IndicatorWidth);

        contentsRect.setRight(subMenuArrowRect.left());
        subMenuArrowRect = style->visualRect(opt->direction,opt->rect,subMenuArrowRect);

        if( menuItemOption->menuItemType == QStyleOptionMenuItem::SubMenu ){
            // arrow orientation
            ArrowOrientation orientation( reverseLayout ? ArrowLeft:ArrowRight );

            // color
            QColor arrowColor = fetcher->getColor(widget,opt,StyleDetailFetcher::Menu_SubMenuArrowColor);

            // draw
            DrawCommonHelper::drawArrow(p,subMenuArrowRect,arrowColor,orientation);
        }
    }

    if( !menuItemOption->text.isEmpty() ) {
        QString text = menuItemOption->text;
        QFontMetrics fontMetrics = menuItemOption->fontMetrics;
        int textflags = Qt::AlignVCenter|(reverseLayout?Qt::AlignRight:Qt::AlignLeft);

        QSize textSize = fontMetrics.size(textflags,text);

        QRect textRect  = QRect(contentsRect.left(),
                          contentsRect.top()+(contentsRect.height()-textSize.height())/2,
                          textSize.width(),
                          textSize.height());

        textRect = style->visualRect(opt->direction,opt->rect,textRect);
        textRect = opt->fontMetrics.boundingRect( textRect, textflags, text );

        style->drawItemText(p,textRect,textflags,opt->palette,enabled,text);
    }

    return true;
}

bool DrawMenuHelper::drawPanelMenuPrimitive(const Style *style, const QStyleOption *opt, QPainter *p,
                                            StyleDetailFetcher *fetcher, const QWidget *widget)
{
    p->setRenderHint(QPainter::Antialiasing,true);

    int borderWidth, borderRadius;
    QColor borderColor, bgColor;

    borderWidth  = fetcher->getInt(widget, opt, StyleDetailFetcher::Menu_BorderWidth);
    borderRadius = fetcher->getInt(widget, opt, StyleDetailFetcher::Menu_BorderRadius);
    borderColor  = fetcher->getColor(widget, opt, StyleDetailFetcher::Menu_BorderColor);
    bgColor      = fetcher->getColor(widget, opt, StyleDetailFetcher::Menu_Background);

    if( widget->inherits("QComboBoxPrivateContainer") ){
        borderColor = fetcher->getColor(widget,opt,StyleDetailFetcher::ComboBoxContainer_BorderColor);
    }

    DrawCommonHelper::drawFrame(p,
                                opt->rect,
                                DrawCommonHelper::isCompositingManagerRuning()?borderRadius:0,
                                borderWidth,
                                bgColor,borderColor);

    return true;
}