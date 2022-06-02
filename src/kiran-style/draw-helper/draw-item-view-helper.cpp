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

#include "draw-item-view-helper.h"
#include "draw-common-helper.h"
#include "style-detail-fetcher.h"
#include "style.h"

#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QAbstractItemView>

using namespace Kiran;

QSize DrawItemViewHelper::kiranSidebarItemSizeFromContent(const Style *style, const QStyleOption *opt,
                                                          const QSize &contentsSize, const QWidget *w,
                                                          StyleDetailFetcher *fetcher)
{
    auto optionViewItem = qstyleoption_cast<const QStyleOptionViewItem *>(opt);
    if (optionViewItem == nullptr) {
        return contentsSize;
    }

    int height = fetcher->getInt(StyleDetailFetcher::KiranSiderbarItem_Height, QCss::PseudoClass_Unspecified);
    return QSize(contentsSize.width(), height);
}

void kiranSidebarItemLayout(const Style *style, const QStyleOption *opt, const QWidget *w, QRect &checkRect,
                            QRect &decorationRect, QRect &textRect, QRect &itemStatusRect, QRect &selectedArrow)
{
    auto optionViewItem = qstyleoption_cast<const QStyleOptionViewItem *>(opt);
    if (optionViewItem == nullptr) {
        return;
    }

    //TODO:判断是否是账户管理的需要特别处理的类型
    bool inAccountManager = true;

    ///去掉两边留白内容区域
    QRect contentsRect(opt->rect.adjusted(Metrics::KiranSidebarItem_LeftRightMargin, 1,
                                          -Metrics::KiranSidebarItem_LeftRightMargin,
                                          -1));

    ///预留给当前项的箭头
    selectedArrow = QRect(contentsRect.right() - Metrics::KiranSidebarItem_SelectedArrowSize,
                          contentsRect.top() +
                          (contentsRect.height() - Metrics::KiranSidebarItem_SelectedArrowSize) / 2,
                          Metrics::KiranSidebarItem_SelectedArrowSize,
                          Metrics::KiranSidebarItem_SelectedArrowSize);
    contentsRect.setRight(selectedArrow.left());

    ///账户管理的特殊绘制加入item状态显示
    if (inAccountManager) {
        auto itemView = qobject_cast<const QAbstractItemView *>(w);
        auto modelIndex = itemView->indexAt(opt->rect.center());
        auto itemModel = itemView->model();
        QVariant accountStateVar;
        if (modelIndex.isValid() && itemModel) {
            accountStateVar = itemModel->data(modelIndex, Kiran::ItemStatus_Role);
        }
        if (accountStateVar.isValid()) {
            QString accountState = accountStateVar.toString();
            QFontMetrics fontMetrics = opt->fontMetrics;
            QSize textSize = fontMetrics.size(Qt::AlignCenter|Qt::TextHideMnemonic,accountState);
            itemStatusRect = QRect(contentsRect.right() - textSize.width() - Metrics::KiranSidebarItem_contentsSpacing,
                                   contentsRect.top()+(contentsRect.height()-textSize.height())/2,
                                   textSize.width(),
                                   textSize.height());
            contentsRect.setRight(itemStatusRect.left() - Metrics::KiranSidebarItem_contentsSpacing);
        }
    }

    const bool hasCheckIndicator = (optionViewItem->features & QStyleOptionViewItem::HasCheckIndicator);

    //check indicator
    if (hasCheckIndicator) {
        QSize checkIndicatorSize(style->pixelMetric(QStyle::PM_IndicatorWidth, opt, w),
                                 style->pixelMetric(QStyle::PM_IndicatorHeight, opt, w));
        checkRect = QRect(contentsRect.left(), contentsRect.top(), checkIndicatorSize.width(),
                          checkIndicatorSize.height());
        contentsRect.setLeft(checkRect.right() + Metrics::KiranSidebarItem_contentsSpacing);

        checkRect = QStyle::visualRect(opt->direction, opt->rect, checkRect);
    } else {
        checkRect = QRect(0, 0, 0, 0);
    }

    //icon,text
    QSize iconSize = optionViewItem->decorationSize;

    //图片绘制位置
    switch (optionViewItem->decorationPosition) {
        case QStyleOptionViewItem::Left:
            decorationRect = QRect(contentsRect.left(),
                                   contentsRect.top() + (contentsRect.height() - iconSize.height()) / 2,
                                   iconSize.width(), iconSize.height());
            contentsRect.setLeft(decorationRect.right() + Metrics::KiranSidebarItem_contentsSpacing);

            textRect = contentsRect;
            break;
        case QStyleOptionViewItem::Right:
            decorationRect = QRect(contentsRect.right() - iconSize.width(),
                                   contentsRect.top() + (contentsRect.height() - iconSize.height()) / 2,
                                   iconSize.width(), iconSize.height());
            contentsRect.setRight(decorationRect.left() - Metrics::KiranSidebarItem_contentsSpacing);

            textRect = contentsRect;
            break;
        case QStyleOptionViewItem::Top:
            decorationRect = QRect(contentsRect.left(), contentsRect.top(), contentsRect.width(), iconSize.height());
            contentsRect.setTop(decorationRect.bottom() + Metrics::KiranSidebarItem_contentsSpacing);

            textRect = contentsRect;
            break;
        case QStyleOptionViewItem::Bottom:
            decorationRect = QRect(contentsRect.left(), contentsRect.bottom() - iconSize.height(), contentsRect.width(),
                                   iconSize.height());
            contentsRect.setBottom(decorationRect.bottom() - Metrics::KiranSidebarItem_contentsSpacing);

            textRect = contentsRect;
            break;
        default:
            break;
    }
    decorationRect = QStyle::visualRect(opt->direction, opt->rect, decorationRect);
    textRect = QStyle::visualRect(opt->direction, opt->rect, textRect);
}

QRect DrawItemViewHelper::kiranSidebarItemCheckIndicatorRect(const Style *style,
                                                             const QStyleOption *opt,
                                                             const QWidget *w)
{
    return style->subElementRect(QStyle::SE_CheckBoxIndicator, opt, w);
}

QRect DrawItemViewHelper::kiranSiderbarItemDecorationRect(const Style *style,
                                                          const QStyleOption *opt,
                                                          const QWidget *w)
{
    QRect checkRect, decorationRect, textRect, itemStatusRect, selectedIndicatorRect;
    kiranSidebarItemLayout(style, opt, w, checkRect,
                           decorationRect, textRect,
                           itemStatusRect, selectedIndicatorRect);

    return decorationRect;
}

QRect DrawItemViewHelper::kiranSiderbarItemTextRect(const Style *style,
                                                    const QStyleOption *opt,
                                                    const QWidget *w)
{
    QRect checkRect, decorationRect, textRect, itemStatusRect, selectedIndicatorRect;
    kiranSidebarItemLayout(style, opt, w, checkRect,
                           decorationRect, textRect,
                           itemStatusRect, selectedIndicatorRect);

    return textRect;
}

bool DrawItemViewHelper::drawPanelKianSidebarItem(const Style *style, const QStyleOption *opt,
                                                  QPainter *p, StyleDetailFetcher *fetcher,
                                                  const QWidget *widget)
{
    auto optionViewItem = qstyleoption_cast<const QStyleOptionViewItem *>(opt);
    if (optionViewItem == nullptr) {
        return true;
    }
    const QStyle::State &state(opt->state);
    const QAbstractItemView *abstractItemView = qobject_cast<const QAbstractItemView *>(widget);
    bool selected(state & QStyle::State_Selected);
    bool enabled(state & QStyle::State_Enabled);
    bool mouseOver((state & QStyle::State_Active) && (state & QStyle::State_MouseOver) &&
                   (!abstractItemView || abstractItemView->selectionMode() != QAbstractItemView::NoSelection));

    int pseudoClass = QCss::PseudoClass_Unspecified;

    if (!enabled) {
        pseudoClass |= QCss::PseudoClass_Disabled;
    }
    if (selected) {
        pseudoClass |= QCss::PseudoClass_Selected;
    }
    if (mouseOver) {
        pseudoClass |= QCss::PseudoClass_Hover;
    }

    ///绘制背景
    int radius = fetcher->getInt(StyleDetailFetcher::KiranSiderbarItem_Radius, pseudoClass);
    QColor backgroundColor = fetcher->getColor(StyleDetailFetcher::KiranSiderbarItem_BackgroundColor, pseudoClass);
    DrawCommonHelper::drawFrame(p, opt->rect, radius, 0, backgroundColor, QColor());

    QRect checkRect,decorationRect,textRect,itemStatusRect,arrowRect;
    kiranSidebarItemLayout(style,opt,widget,checkRect,
                           decorationRect,textRect,
                           itemStatusRect,arrowRect);

    if( itemStatusRect.isValid() ){
        const QAbstractItemView* itemView = qobject_cast<const QAbstractItemView*>(widget);
        QModelIndex modelIndex = itemView->indexAt(opt->rect.center());
        const QAbstractItemModel* itemModel = itemView->model();
        if( modelIndex.isValid() && itemModel ){
            QVariant statusVar = itemModel->data(modelIndex,ItemStatus_Role);
            QVariant colorVar = itemModel->data(modelIndex,ItemStatusColor_Role);
            if( statusVar.isValid() && statusVar.type()==QVariant::String ){
                QString status = statusVar.toString();
                QColor statusColor = colorVar.value<QColor>();
                p->save();
                if( !selected && statusColor.isValid() ){
                    p->setPen(statusColor);
                }else{
                    p->setPen(opt->palette.color(QPalette::WindowText));
                }
                p->drawText(itemStatusRect,Qt::AlignCenter,status);
                p->restore();
            }
        }
    }

    ///绘制当前项的箭头的标示
    if (selected) {
        QStyleOption temp(*opt);
        temp.rect = arrowRect;
        DrawCommonHelper::drawArrow(fetcher, p, &temp, widget, ArrowRight);
    }

    return true;
}

bool DrawItemViewHelper::drawIndicatorKiranSidebarItemCheck(const Style *style, const QStyleOption *opt,
                                                            QPainter *p, StyleDetailFetcher *fetcher,
                                                            const QWidget *widget)
{
    return false;
}