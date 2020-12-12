//
// Created by lxh on 2020/11/30.
//

#include "draw-combo-box-helper.h"
#include "style-data/style-detail-fetcher.h"
#include "draw-common-helper.h"
#include "style.h"

#include <QComboBox>
#include <QDebug>
#include <QAbstractItemView>

using namespace Kiran;

bool DrawComboBoxHelper::drawComboBoxComplexControl(const Kiran::Style *style, const QStyleOptionComplex *opt,
                                                    Kiran::StyleDetailFetcher *fetcher, QPainter *p,
                                                    const QWidget *w)
{
    const QStyleOptionComboBox *comboBoxOption(qstyleoption_cast<const QStyleOptionComboBox *>(opt));
    if (!comboBoxOption)
        return true;

    // rect and palette
    const QRect &rect(opt->rect);
    const QPalette &palette(opt->palette);

    // state
    const QStyle::State &state(opt->state);
    bool enabled(state & QStyle::State_Enabled);
    bool windowActive(state & QStyle::State_Active);
    bool editable(comboBoxOption->editable);
    bool arrowActive(comboBoxOption->activeSubControls & QStyle::SC_ComboBoxArrow);
    bool flat(!comboBoxOption->frame);
    bool mouseOver;
    bool hasFocus;
    bool sunken;

    if (editable) {
        mouseOver = windowActive && arrowActive && enabled && (state & QStyle::State_MouseOver);
        hasFocus = enabled && (state & (QStyle::State_HasFocus | QStyle::State_Sunken));
        sunken = arrowActive && enabled && (state & (QStyle::State_On | QStyle::State_Sunken));
    } else {
        mouseOver = windowActive && enabled && (state & QStyle::State_MouseOver);
        hasFocus = enabled && (state & (QStyle::State_HasFocus | QStyle::State_Sunken));
        sunken = enabled && (state & (QStyle::State_On | QStyle::State_Sunken));
    }

    int borderWidth = fetcher->getInt(w, opt, StyleDetailFetcher::ComboBox_BorderWidth);
    int radius = fetcher->getInt(w, opt, StyleDetailFetcher::ComboBox_BorderRadius);
    QColor borderColor = fetcher->getColor(w, opt, StyleDetailFetcher::ComboBox_BorderColor);
    QColor bgColor = fetcher->getColor(w, opt, StyleDetailFetcher::ComboBox_Background);
    QColor indicatorColor = fetcher->getColor(w, opt, StyleDetailFetcher::ComboBox_ArrowIndicatorColor);

    if (enabled && editable && hasFocus) {
        //获取输入焦点时边框颜色
        borderColor = fetcher->getColor(w, opt, StyleDetailFetcher::ComboBox_EditBorderColor);
    }

    if (opt->subControls & QStyle::SC_ComboBoxFrame) {
        DrawCommonHelper::drawFrame(p, opt->rect, radius, borderWidth, bgColor, borderColor);
    }

    if (opt->subControls & QStyle::SC_ComboBoxArrow) {
        QRect arrowRect = style->subControlRect(QStyle::CC_ComboBox, opt, QStyle::SC_ComboBoxArrow, w);
        QStyleOption tempOption;
        tempOption.rect = arrowRect;
        tempOption.direction = opt->direction;
        tempOption.state = opt->state;
        DrawCommonHelper::drawArrow(fetcher,p, &tempOption, w, ArrowDown);
    }

    return true;
}

QRect DrawComboBoxHelper::comboBoxSubControlRect(const Kiran::Style *style, const QStyleOptionComplex *opt,
                                                 QStyle::SubControl subControl, const QWidget *w)
{
    QRect rect(opt->rect);

    switch (subControl) {
        case QStyle::SC_ComboBoxFrame:
            return rect;
        case QStyle::SC_ComboBoxListBoxPopup:
            return rect;
        case QStyle::SC_ComboBoxArrow: {
            QRect arrowRect(
                    rect.right() - Metrics::ComboBox_ItemSpacing - Metrics::ComboBox_ArrowSize,
                    rect.top()+(rect.height()-Metrics::ComboBox_ArrowSize)/2,
                    Metrics::ComboBox_ArrowSize,
                    Metrics::ComboBox_ArrowSize);
            return arrowRect;
        }
        case QStyle::SC_ComboBoxEditField: {
            QRect labelRect;
            int frameWidth(style->pixelMetric(QStyle::PM_ComboBoxFrameWidth, opt, w));
            labelRect = QRect(
                    rect.left(), rect.top(),
                    rect.width() - rect.height() - 4,
                    rect.height());
            labelRect.adjust(frameWidth, frameWidth, 0, -frameWidth);
            return style->visualRect(opt->direction, opt->rect, labelRect);
        }
        default:
            break;
    }

    return style->subControlRect(QStyle::CC_ComboBox, opt, subControl, w);
}

bool DrawComboBoxHelper::drawComboBoxMenuItem(const Kiran::Style *style, const QStyleOption *opt, QPainter *p,
                                              Kiran::StyleDetailFetcher *fetcher, const QWidget *widget)
{
    //TODO:判断当前项
    const QStyleOptionMenuItem *optionMenuItem = qstyleoption_cast<const QStyleOptionMenuItem *>(opt);
    const QComboBox *combobox = qobject_cast<const QComboBox *>(widget);

    const QStyle::State &state = opt->state;
    bool enabled(state & QStyle::State_Enabled);
    bool selected(enabled && (state & QStyle::State_Selected));
    bool sunken(enabled && (state & (QStyle::State_On | QStyle::State_Sunken)));
    bool reverseLayout(opt->direction == Qt::RightToLeft);

    QColor separatorColor = fetcher->getColor(widget, opt, StyleDetailFetcher::ComboBoxContainer_SeparatorColor);

    p->setRenderHint(QPainter::Antialiasing,true);

    QModelIndex modelIndex = combobox->view()->indexAt(opt->rect.topLeft());
    bool isFirstItem = (modelIndex.row() == 0);
    bool isLastItem = (modelIndex.row() == combobox->count() - 1);

    //最后一个选项不绘制分隔线
    if (!isLastItem) {
        p->save();
        QPen pen(separatorColor);
        pen.setWidth(1);
        p->setPen(pen);
        p->drawLine(opt->rect.bottomLeft(), opt->rect.bottomRight());
        p->restore();
    }

    QColor bgColor = fetcher->getColor(widget, opt, StyleDetailFetcher::ComboBoxItem_Background);
    if (bgColor.isValid()) {
        p->save();
        if (isFirstItem || isLastItem) {
            int radius = 0;
            if (DrawCommonHelper::isCompositingManagerRuning()) {
                radius = fetcher->getInt(widget, opt, StyleDetailFetcher::ComboBox_BorderRadius);
            }
            QPainterPath painterPath = DrawCommonHelper::getRoundedRectanglePath(opt->rect,
                                                                    isFirstItem ? radius : 0,
                                                                    isFirstItem ? radius : 0,
                                                                    isLastItem ? radius : 0,
                                                                    isLastItem ? radius : 0);
            p->setClipPath(painterPath);
        }

        p->fillRect(opt->rect, bgColor);
        p->restore();
    }

    int comboboxFrameWidth = style->pixelMetric(Style::PM_ComboBoxFrameWidth, opt, widget);
    int itemSpacing = Metrics::ComboBox_ItemSpacing;
    QRect contentsRect = DrawCommonHelper::insideMargin(opt->rect, comboboxFrameWidth);

    //icon
    bool itemsHasIcon = false;
    for (int i = 0; i < combobox->count(); i++) {
        QIcon icon = combobox->itemIcon(i);
        if (!icon.isNull()) {
            itemsHasIcon = true;
            break;
        }
    }

    ///锚定好图标位置
    if (itemsHasIcon) {
        QSize iconSize(optionMenuItem->maxIconWidth,
                       optionMenuItem->maxIconWidth);

        QRect iconRect(contentsRect.left(),
                       contentsRect.top() + (contentsRect.height() - iconSize.height()) / 2,
                       iconSize.width(),
                       iconSize.height());

        contentsRect.setLeft(iconRect.right() + itemSpacing);

        iconRect = style->visualRect(opt->direction,opt->rect,iconRect);

        QIcon::Mode iconMode;
        // icon mode
        QIcon::Mode mode;
        if (selected) mode = QIcon::Selected;
        else if (enabled) mode = QIcon::Normal;
        else mode = QIcon::Disabled;

        // icon state
        const QIcon::State iconState(sunken ? QIcon::On : QIcon::Off);
        QPixmap icon = optionMenuItem->icon.pixmap(iconRect.size(), mode, iconState);
        p->drawPixmap(iconRect, icon);
    }

    //锚定好勾选标志
    if(optionMenuItem->menuHasCheckableItems){
        QRect checkedIndicatorRect(contentsRect.right()-Metrics::MenuItem_ItemSpacing-Metrics::MenuItem_CheckedIndicatorSize,
                                   contentsRect.top()+(contentsRect.height()-Metrics::MenuItem_CheckedIndicatorSize)/2,
                                   Metrics::MenuItem_CheckedIndicatorSize,
                                   Metrics::MenuItem_CheckedIndicatorSize);

        contentsRect.setRight(checkedIndicatorRect.left()+Metrics::MenuItem_ItemSpacing);

        checkedIndicatorRect = style->visualRect(opt->direction,opt->rect,checkedIndicatorRect);

        if( optionMenuItem->checked ){
            QColor indicatorBgColor = fetcher->getColor(widget,opt,StyleDetailFetcher::Menu_CheckedIndicatorBackground);
            QColor indicatorSignColor = fetcher->getColor(widget,opt,StyleDetailFetcher::Menu_CheckedIndicatorSignColor);
            DrawCommonHelper::drawMenuCheckedIndicator(p,checkedIndicatorRect,indicatorBgColor,indicatorSignColor);
        }
    }

    //text
    if (!optionMenuItem->text.isEmpty()) {
        QString text = optionMenuItem->text;
        QFontMetrics fontMetrics = optionMenuItem->fontMetrics;
        int textflags = Qt::AlignVCenter | (reverseLayout ? Qt::AlignRight : Qt::AlignLeft);

        QSize textSize = fontMetrics.size(textflags, text);

        QRect textRect = QRect(contentsRect.left(),
                               contentsRect.top() + (contentsRect.height() - textSize.height()) / 2,
                               textSize.width(),
                               textSize.height());

        textRect = style->visualRect(opt->direction, opt->rect, textRect);
        textRect = opt->fontMetrics.boundingRect(textRect, textflags, text);

        style->drawItemText(p, textRect, textflags, opt->palette, enabled, text);
    }

    return true;
}