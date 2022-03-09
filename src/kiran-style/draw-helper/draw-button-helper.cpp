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
#include <QStyleOption>
#include <QAbstractButton>
#include <QPushButton>
#include <QDebug>
#include <QPainterPath>

#include "style.h"
#include "draw-common-helper.h"
#include "draw-button-helper.h"
#include "widget-property-helper.h"
#include "style-detail-fetcher.h"

using namespace Kiran;

bool DrawButtonHelper::drawPanelButtonToolPrimitive(const Style *style, const QStyleOption *opt,
                                                    QPainter *p, Kiran::StyleDetailFetcher *fetcher,
                                                    const QWidget *widget)
{
    bool isDockWidgetTitleButton = widget->inherits("QDockWidgetTitleButton");
    bool inTabBar = (widget && widget->parentWidget() && widget->parentWidget()->inherits("QTabBar"));

    if (isDockWidgetTitleButton) {///在DockWidget中的TitleButton特殊绘制
        QColor toolColor = fetcher->getColor(widget, opt, StyleDetailFetcher::ToolButton_Background);
        DrawCommonHelper::drawFrame(p, opt->rect, 0, 0, toolColor, QColor());
    } else if (inTabBar) {///在TabBar中的按钮特殊绘制
        QColor background = opt->palette.color(QPalette::Window);
        p->setPen(Qt::NoPen);
        p->setBrush(background);
        p->drawRect(opt->rect);
    } else {///普通QToolButton
        int borderWidth, borderRadius;
        QColor bgColor, borderColor;
        bgColor = fetcher->getColor(widget, opt, StyleDetailFetcher::Button_NormalBackground);
        borderColor = fetcher->getColor(widget, opt, StyleDetailFetcher::Button_NormalBorderColor);
        borderRadius = fetcher->getInt(widget, opt, StyleDetailFetcher::Button_Radius);
        borderWidth = fetcher->getInt(widget, opt, StyleDetailFetcher::Button_NormalBorderWidth);
        DrawCommonHelper::drawFrame(p, opt->rect, borderRadius, borderWidth, bgColor, borderColor);
    }
    return true;
}

bool DrawButtonHelper::drawIndicatorRadioButton(const Style *style, const QStyleOption *opt, QPainter *p,
                                                StyleDetailFetcher *fetcher, const QWidget *widget)
{
    const QRect &rect(opt->rect);
    bool isOn = opt->state & QStyle::State_On;

    QColor color = fetcher->getColor(widget, opt, StyleDetailFetcher::RadioButton_IndicatorColor);

    DrawCommonHelper::drawRadioButtonIndicator(p, rect, color, isOn);

    return true;
}

bool DrawButtonHelper::drawIndicatorCheckBox(const Style *style, const QStyleOption *opt, QPainter *p,
                                             StyleDetailFetcher *fetcher, const QWidget *widget)
{
    auto optionButton(qstyleoption_cast<const QStyleOptionButton *>(opt));
    if (!optionButton) {
        return true;
    }


    CheckBoxIndicatorState checkState(CheckOff);
    if (opt->state & QStyle::State_NoChange)
        checkState = CheckPartial;
    else if (opt->state & QStyle::State_On)
        checkState = CheckOn;

    QColor bgColor = fetcher->getColor(widget, opt, StyleDetailFetcher::CheckBox_IndicatorBackground);
    QColor signColor = fetcher->getColor(widget, opt, StyleDetailFetcher::CheckBox_IndicatorSign);
    QColor borderColor = fetcher->getColor(widget, opt, StyleDetailFetcher::CheckBox_BorderColor);

    DrawCommonHelper::drawCheckBoxIndicator(p, opt->rect, borderColor, bgColor, signColor, checkState);
    return true;
}

bool DrawButtonHelper::drawPushButtonBevelControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                  StyleDetailFetcher *fetcher, const QWidget *widget)
{
    auto buttonOption = qstyleoption_cast<const QStyleOptionButton *>(opt);
    if (!buttonOption) {
        return true;
    }

    bool on = buttonOption->state & QStyle::State_On;
    bool flat = buttonOption->features & QStyleOptionButton::Flat;

    StyleDetailFetcher::StyleDetailPropertyName bgColorProperty, borderColorProperty, borderWidthProperty;

    if (flat) { //flat button绘制选项
        bgColorProperty = StyleDetailFetcher::Button_FlatBackground;
        borderColorProperty = StyleDetailFetcher::Button_FlatBorderColor;
        borderWidthProperty = StyleDetailFetcher::Button_FlatBorderWidth;
    } else { //根据按钮类型获取绘制选项
        auto btn = qobject_cast<const QPushButton *>(widget);
        if (!btn) {
            return true;
        }
        ButtonType buttonType = WidgetPropertyHelper::getButtonType(btn);
        switch (buttonType) {
            case BUTTON_Default:
                bgColorProperty = StyleDetailFetcher::Button_DefaultBackground;
                borderColorProperty = StyleDetailFetcher::Button_DefaultBorderColor;
                borderWidthProperty = StyleDetailFetcher::Button_DefaultBorderWidth;
                break;
            case BUTTON_Warning:
                bgColorProperty = StyleDetailFetcher::Button_WarningBackground;
                borderColorProperty = StyleDetailFetcher::Button_WarningBorderColor;
                borderWidthProperty = StyleDetailFetcher::Button_WarningBorderWidth;
                break;
            default:
                bgColorProperty = StyleDetailFetcher::Button_NormalBackground;
                borderColorProperty = StyleDetailFetcher::Button_NormalBorderColor;
                borderWidthProperty = StyleDetailFetcher::Button_NormalBorderWidth;
                break;
        }
    }

    /// 获取绘制选项
    int specialPseudo = 0;
    int radius, borderWidth;
    QColor bgColor, borderColor;
    //特殊处理按钮按下激活的状态
    if (on) {
        specialPseudo = QCss::PseudoClass_Pressed;
    }

    radius = fetcher->getInt(widget, opt, StyleDetailFetcher::Button_Radius, specialPseudo);
    borderWidth = fetcher->getInt(widget, opt, borderWidthProperty, specialPseudo);
    bgColor = fetcher->getColor(widget, opt, bgColorProperty, specialPseudo);
    borderColor = fetcher->getColor(widget, opt, borderColorProperty, specialPseudo);

    DrawCommonHelper::drawFrame(p, opt->rect, radius, borderWidth, bgColor, borderColor);
    return true;
}

bool DrawButtonHelper::drawPushButtonLabelControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                  StyleDetailFetcher *fetcher, const QWidget *widget)
{
    auto buttonOption(qstyleoption_cast<const QStyleOptionButton *>(opt));
    if (!buttonOption)
        return true;

    const QStyle::State &state(opt->state);
    const bool enabled(state & QStyle::State_Enabled);
    const bool sunken(state & (QStyle::State_On | QStyle::State_Sunken));
    const bool mouseOver(opt->state & QStyle::State_MouseOver);
    const bool hasFocus(opt->state & QStyle::State_HasFocus);
    const bool flat(buttonOption->features & QStyleOptionButton::Flat);
    const bool hasText(!buttonOption->text.isEmpty());
    const bool hasIcon((flat || !hasText) && !buttonOption->icon.isNull());
    const QSize iconSize = buttonOption->iconSize;
    QRect contentsRect(opt->rect);

    // text
    int textFlags(Qt::AlignCenter);
    const QSize textSize(opt->fontMetrics.size(textFlags, buttonOption->text));

    if (style->styleHint(QStyle::SH_UnderlineShortcut, buttonOption, widget))
        textFlags |= Qt::TextShowMnemonic;
    else
        textFlags |= Qt::TextHideMnemonic;

    QRect iconRect;
    QRect textRect;

    if (hasText && !hasIcon) {
        textRect = contentsRect;
    } else if (hasIcon && !hasText) {
        iconRect = contentsRect;
    } else {
        // 图标和文字一起靠中间
        const int contentsWidth(iconSize.width() + textSize.width() + Metrics::Button_ItemSpacing);
        iconRect = QRect(QPoint(contentsRect.left() + (contentsRect.width() - contentsWidth) / 2,
                                contentsRect.top() + (contentsRect.height() - iconSize.height()) / 2), iconSize);
        textRect = QRect(QPoint(iconRect.right() + Metrics::ToolButton_ItemSpacing + 1,
                                contentsRect.top() + (contentsRect.height() - textSize.height()) / 2), textSize);
    }

    // 处理从右到左的布局方向
    if (iconRect.isValid())
        iconRect = QStyle::visualRect(opt->direction, opt->rect, iconRect);
    if (textRect.isValid())
        textRect = QStyle::visualRect(opt->direction, opt->rect, textRect);

    // 图片居中iconRect
    if (iconRect.isValid()) {
        QRect tempRect = iconRect;
        tempRect.setWidth(iconSize.width());
        tempRect.setHeight(iconSize.height());
        tempRect.moveCenter(iconRect.center());
        iconRect = tempRect;
    }

    // 绘制图标
    if (hasIcon && iconRect.isValid()) {
        const QIcon::State iconState(sunken ? QIcon::On : QIcon::Off);
        QIcon::Mode iconMode;
        if (!enabled) iconMode = QIcon::Disabled;
        else if (!flat && hasFocus) iconMode = QIcon::Selected;
        else if (mouseOver && flat) iconMode = QIcon::Active;
        else iconMode = QIcon::Normal;

        buttonOption->icon.paint(p, iconRect, Qt::AlignCenter, iconMode, iconState);
    }

    // 绘制文本
    if (hasText && textRect.isValid()) {
        int menuButtonIndicatorSize = style->pixelMetric(QStyle::PM_MenuButtonIndicator,buttonOption,widget);
        QColor textColor = fetcher->getColor(widget, opt, flat ? StyleDetailFetcher::Button_FlatTextColor
                                                               : StyleDetailFetcher::Button_TextColor);
        p->setPen(textColor);

        if (buttonOption->features & QStyleOptionButton::HasMenu)
            textRect = textRect.adjusted(0, 0,-menuButtonIndicatorSize, 0);
        //NOTE:需加上Qt::TextShowMnemonic或Qt::TextHideMnemonic才会转换’&‘成下划线标记快捷键
        p->drawText(textRect, textFlags|MnemonicTextFlag, buttonOption->text);
    }

    return true;
}

bool DrawButtonHelper::drawPushButtonControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                             StyleDetailFetcher *fetcher, const QWidget *widget)
{
    auto buttonOption = qstyleoption_cast<const QStyleOptionButton *>(opt);
    if (!buttonOption) {
        return true;
    }

    style->proxy()->drawControl(QStyle::CE_PushButtonBevel, buttonOption, p, widget);

    QStyleOptionButton subOpt = *buttonOption;
    subOpt.rect = style->subElementRect(QStyle::SE_PushButtonContents, buttonOption, widget);

    style->proxy()->drawControl(QStyle::CE_PushButtonLabel, &subOpt, p, widget);
    return true;
}

bool DrawButtonHelper::drawToolButtonLabelControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                  StyleDetailFetcher *fetcher, const QWidget *widget)
{
    auto buttonOption(qstyleoption_cast<const QStyleOptionToolButton *>(opt));
    if (!buttonOption)
        return true;

    const QStyle::State &state(opt->state);
    const bool enabled(state & QStyle::State_Enabled);
    const bool sunken(state & (QStyle::State_On | QStyle::State_Sunken));
    const bool mouseOver(opt->state & QStyle::State_MouseOver);
    const bool hasFocus(opt->state & QStyle::State_HasFocus);
    const bool flat(buttonOption->features & QStyleOptionButton::Flat);

    //存在文本
    const bool hasText(!buttonOption->text.isEmpty());
    //存在图标
    const bool hasIcon((flat || !hasText) && !buttonOption->icon.isNull());
    //显示Arrow
    bool hasArrow(buttonOption->features & QStyleOptionToolButton::Arrow);

    QRect contentsRect(opt->rect);

    const QSize iconSize = buttonOption->iconSize;

    //FIXME:该标志是否写死，文字一直为居中显示
    int textFlags(Qt::AlignCenter);
    const QSize textSize(opt->fontMetrics.size(textFlags, buttonOption->text));

    if (style->styleHint(QStyle::SH_UnderlineShortcut, buttonOption, widget))
        textFlags |= Qt::TextShowMnemonic;
    else
        textFlags |= Qt::TextHideMnemonic;


    //根据配置项，初始化文字和图标所绘的位置
    QRect iconRect;
    QRect textRect;
    if (hasText && !(hasIcon || hasArrow) && buttonOption->toolButtonStyle == Qt::ToolButtonTextOnly) { /// 只绘制文字
        textRect = contentsRect;
    } else if ((hasArrow || hasIcon) &&
               (!hasText || buttonOption->toolButtonStyle == Qt::ToolButtonIconOnly)) { /// 只绘制图标
        iconRect = contentsRect;
    } else if (buttonOption->toolButtonStyle == Qt::ToolButtonTextUnderIcon) { /// 文字图标上下绘制
        int contentsHeight(iconSize.height() + textSize.height() + Metrics::ToolButton_ItemSpacing);
        iconRect = QRect(QPoint(contentsRect.left() + (contentsRect.width() - iconSize.width()) / 2,
                                contentsRect.top() + (contentsRect.height() - contentsHeight) / 2), iconSize);
        textRect = QRect(QPoint(contentsRect.left() + (contentsRect.width() - textSize.width()) / 2,
                                iconRect.bottom() + Metrics::ToolButton_ItemSpacing + 1), textSize);
        textFlags |= Qt::AlignCenter;
    } else { ///文字图标左右绘制
        const int contentsWidth(iconSize.width() + textSize.width() + Metrics::Button_ItemSpacing);
        iconRect = QRect(QPoint(contentsRect.left() + (contentsRect.width() - contentsWidth) / 2,
                                contentsRect.top() + (contentsRect.height() - iconSize.height()) / 2), iconSize);
        textRect = QRect(QPoint(iconRect.right() + Metrics::ToolButton_ItemSpacing + 1,
                                contentsRect.top() + (contentsRect.height() - textSize.height()) / 2), textSize);
    }

    // handle right to left
    if (iconRect.isValid())
        iconRect = style->proxy()->visualRect(opt->direction, opt->rect, iconRect);
    if (textRect.isValid())
        textRect = style->proxy()->visualRect(opt->direction, opt->rect, textRect);

    // 根据图标大小,使图标居中在iconRect中
    if (iconRect.isValid()) {
        QRect tempRect = iconRect;
        tempRect.setWidth(iconSize.width());
        tempRect.setHeight(iconSize.height());
        tempRect.moveCenter(iconRect.center());
        iconRect = tempRect;
    }

    /// 绘制箭头或图标
    if (hasArrow && iconRect.isValid()) {
        QStyleOptionToolButton copy(*buttonOption);
        copy.rect = iconRect;
        switch (buttonOption->arrowType) {
            case Qt::LeftArrow:
                style->drawPrimitive(QStyle::PE_IndicatorArrowLeft, &copy, p, widget);
                break;
            case Qt::RightArrow:
                style->drawPrimitive(QStyle::PE_IndicatorArrowRight, &copy, p, widget);
                break;
            case Qt::UpArrow:
                style->drawPrimitive(QStyle::PE_IndicatorArrowUp, &copy, p, widget);
                break;
            case Qt::DownArrow:
                style->drawPrimitive(QStyle::PE_IndicatorArrowDown, &copy, p, widget);
                break;
            default:
                break;
        }
    } else if (hasIcon && iconRect.isValid()) {
        //图标状态
        const QIcon::State iconState(sunken ? QIcon::On : QIcon::Off);
        QIcon::Mode iconMode;

        if (!enabled) iconMode = QIcon::Disabled;
        else if (!flat && hasFocus) iconMode = QIcon::Selected;
        else if (mouseOver && flat) iconMode = QIcon::Active;
        else iconMode = QIcon::Normal;

        buttonOption->icon.paint(p, iconRect, Qt::AlignCenter, iconMode, iconState);
    }

    // 绘制文字
    if (hasText && textRect.isValid()) {
        QColor textColor = fetcher->getColor(widget, opt, flat ? StyleDetailFetcher::Button_FlatTextColor
                                                               : StyleDetailFetcher::Button_TextColor);
        p->setPen(textColor);

        if (buttonOption->features & QStyleOptionButton::HasMenu)
            textRect = textRect.adjusted(0, 0,
                                         -style->proxy()->pixelMetric(QStyle::PM_MenuButtonIndicator, buttonOption,
                                                                      widget), 0);

        //NOTE:需加上Qt::TextShowMnemonic或Qt::TextHideMnemonic才会转换’&‘成下划线标记快捷键
        p->drawText(textRect, textFlags|MnemonicTextFlag, buttonOption->text);
    }

    return true;
}

bool DrawButtonHelper::drawCheckBoxLabelControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                StyleDetailFetcher *fetcher, const QWidget *widget)
{
    const QStyleOptionButton *buttonOption(qstyleoption_cast<const QStyleOptionButton *>(opt));
    if (!buttonOption) return true;

    const QRect &rect(opt->rect);

    const QStyle::State &state(opt->state);
    bool enabled(state & QStyle::State_Enabled);

    // 是否反向布局从右到左
    bool reverseLayout(opt->direction == Qt::RightToLeft);
    // 文字对齐标志
    int alignmentFlag(Qt::AlignVCenter | (reverseLayout ? Qt::AlignRight : Qt::AlignLeft));

    QRect textRect(rect);
    const QIcon &buttonIcon = buttonOption->icon;

    //图标
    if (!buttonIcon.isNull()) {
        const QIcon::Mode mode(enabled ? QIcon::Normal : QIcon::Disabled);
        QPixmap pixmap(buttonOption->icon.pixmap(buttonOption->iconSize, mode));
        style->drawItemPixmap(p, rect, alignmentFlag, pixmap);
        //重新定位文字绘制矩形
        textRect.setLeft(textRect.left() + buttonOption->iconSize.width() + 4);
        //适配从右往左的布局
        textRect = style->visualRect(opt->direction, opt->rect, textRect);
    }

    //文本
    if (!buttonOption->text.isEmpty()) {
        textRect = opt->fontMetrics.boundingRect(textRect, alignmentFlag, buttonOption->text);
        //NOTE:需加上Qt::TextShowMnemonic或Qt::TextHideMnemonic才会转换’&‘成下划线标记快捷键
        style->drawItemText(p, textRect, alignmentFlag|MnemonicTextFlag, opt->palette, enabled, buttonOption->text,
                            QPalette::WindowText);
        bool hasFocus(enabled && (state & QStyle::State_HasFocus));
    }

    return true;
}

QRect DrawButtonHelper::checkBoxContentsRect(const Style *style, const QStyleOption *opt, const QWidget *w)
{
    return style->visualRect(opt->direction, opt->rect,
                             opt->rect.adjusted(Metrics::CheckBox_Size + 2 * Metrics::CheckBox_ItemSpacing, 0, 0, 0));
}

bool DrawButtonHelper::drawToolButtonComplexControl(const Style *style, const QStyleOptionComplex *opt,
                                                    StyleDetailFetcher *fetcher, QPainter *p, const QWidget *widget)
{
    auto toolButtonOption(qstyleoption_cast<const QStyleOptionToolButton *>(opt));
    if (!toolButtonOption)
        return true;

    // need to alter palette for focused buttons
    const QStyle::State &state(opt->state);
    bool enabled(state & QStyle::State_Enabled);
    bool mouseOver((state & QStyle::State_Active) && enabled && (opt->state & QStyle::State_MouseOver));
    bool hasFocus(enabled && (opt->state & QStyle::State_HasFocus));
    bool sunken(state & (QStyle::State_On | QStyle::State_Sunken));
    bool flat(state & QStyle::State_AutoRaise);

    bool isDockWidgetTitleButton(widget && widget->inherits("QDockWidgetTitleButton"));
    bool inTabBar(widget && qobject_cast<const QTabBar *>(widget->parentWidget()));

    // copy opt and alter palette
    QStyleOptionToolButton copy(*toolButtonOption);

    if (isDockWidgetTitleButton) {
        // 转换类型为按钮，调整StyleOption状态显示正确的按钮
        const QAbstractButton *button(qobject_cast<const QAbstractButton *>(widget));
        if (button->isChecked() || button->isDown()) {
            copy.state |= QStyle::State_Enabled | QStyle::State_On | QStyle::State_Sunken;
        }
        if (button->underMouse()) {
            copy.state |= QStyle::State_Enabled | QStyle::State_MouseOver | QStyle::State_Active;
        }
    }

    bool hasPopupMenu(toolButtonOption->features & QStyleOptionToolButton::MenuButtonPopup);
    const bool hasInlineIndicator(
            toolButtonOption->features & QStyleOptionToolButton::HasMenu
            && toolButtonOption->features & QStyleOptionToolButton::PopupDelay
            && !hasPopupMenu);

    QRect buttonRect(style->subControlRect(QStyle::CC_ToolButton, opt, QStyle::SC_ToolButton, widget));
    QRect menuRect(style->subControlRect(QStyle::CC_ToolButton, opt, QStyle::SC_ToolButtonMenu, widget));

    if (toolButtonOption->subControls & QStyle::SC_ToolButton || isDockWidgetTitleButton) {
        copy.rect = buttonRect;
        ///FIXME: 若QTabBar父控件存在样式表或自身存在样式表，Style为QStyleSheetStyle
        ///      在StyleSheetStyle::drawComplexControl(CC_ToolButton)中
        ///      会直接调用到QWindowsStyle::drawComplexControl导致样式不统一
        ///TODO: 需要把drawToolButtonCoplexComtrol和QCommonStyle中进行统一保证样式统一
        if (inTabBar) {
            QRect rect(opt->rect);
            QColor background("#222222");
            p->setPen(Qt::NoPen);
            p->setBrush(background);
        } else if (sunken && hasPopupMenu && !(toolButtonOption->activeSubControls & QStyle::SC_ToolButton)) {
            QStyleOptionToolButton btn(copy);
            btn.state |= QStyle::State_Raised;
            btn.state &= ~QStyle::State_Sunken;
            btn.state &= ~QStyle::State_AutoRaise;
            style->drawPrimitive(QStyle::PE_PanelButtonTool, &btn, p, widget);
        } else {
            style->drawPrimitive(QStyle::PE_PanelButtonTool, &copy, p, widget);
        }
    }

    // define contents rect
    QRect contentsRect(buttonRect);

    if (hasPopupMenu) {
        copy.rect = menuRect;
        if (!flat || mouseOver || sunken)
            style->drawPrimitive(QStyle::PE_IndicatorButtonDropDown, &copy, p, widget);
        style->drawPrimitive(QStyle::PE_IndicatorArrowDown, &copy, p, widget);
    } else if (hasInlineIndicator) {
        copy.rect = menuRect;
        style->drawPrimitive(QStyle::PE_IndicatorArrowDown, &copy, p, widget);
    }

    if (isDockWidgetTitleButton) {
        // cast to abstract button
        // adjust state to have correct icon rendered
        const QAbstractButton *button(qobject_cast<const QAbstractButton *>(widget));
        if (button->isChecked() || button->isDown()) {
            copy.state |= QStyle::State_Enabled | QStyle::State_On | QStyle::State_Sunken;
        }
        if (button->underMouse()) {
            copy.state |= QStyle::State_Enabled | QStyle::State_MouseOver | QStyle::State_Active;
        }

    } else if (!inTabBar && hasInlineIndicator) {
        int marginWidth(
                flat ? Metrics::ToolButton_MarginWidth : Metrics::Button_MarginWidth + Metrics::Frame_FrameWidth);
        contentsRect = DrawCommonHelper::insideMargin(contentsRect, marginWidth, 0);
        contentsRect.setRight(contentsRect.right() - Metrics::ToolButton_InlineIndicatorWidth);
        contentsRect = style->visualRect(opt->direction, opt->rect, contentsRect);
    }

    style->drawControl(QStyle::CE_ToolButtonLabel, &copy, p, widget);
    return true;
}

QSize DrawButtonHelper::checkBoxSizeFromContents(const Style *style, const QStyleOption *opt, const QSize &contentsSize,
                                                 const QWidget *w,
                                                 StyleDetailFetcher *detailFetcher)
{
    // get contents size
    QSize size(contentsSize);

    // add focus height
    size = DrawCommonHelper::expandSize(size, 0, Metrics::CheckBox_FocusMarginWidth);

    // make sure there is enough height for indicator
    size.setHeight(qMax(size.height(), int(Metrics::CheckBox_Size)));

    // Add space for the indicator and the icon
    size.rwidth() += Metrics::CheckBox_Size + Metrics::CheckBox_ItemSpacing;

    // also add extra space, to leave room to the right of the label
    size.rwidth() += Metrics::CheckBox_ItemSpacing;

    return size;
}

QSize
DrawButtonHelper::switchButtonSizeFromContents(const Style *style, const QStyleOption *opt, const QSize &contentSize,
                                               const QWidget *w)
{
    QSize size(contentSize);

    size.setHeight(qMax(size.height(), int(Metrics::SwitchButton_IndicatorHeight)));

    size = DrawCommonHelper::expandSize(size, 0, Metrics::SwitchButton_FocusMarginWidth);

    size.rwidth() += Metrics::SwitchButton_ItemSpacing;
    size.rwidth() += Metrics::SwitchButton_IndicatorWidth;

    return size;
}

bool DrawButtonHelper::drawSwitchButtonIndicatorPrimitive(const Style *style, const QStyleOption *opt, QPainter *p,
                                                          StyleDetailFetcher *fetcher, const QWidget *widget)
{
    p->setRenderHint(QPainter::Antialiasing, true);

    bool isChecked = opt->state & QStyle::State_On;

    int pseudoStatus = QCss::PseudoClass_Unspecified;

    int radius = opt->rect.height() / 2;
    int borderWidth = fetcher->getInt(widget, opt, StyleDetailFetcher::SwitchButton_BorderWidth);
    int indicatorCircularSize = Metrics::SwitchButton_IndicatorCircularSize;
    int indicatorCircularSpacing = Metrics::SwitchButton_IndicatorCircularSpacing;

    QColor borderColor = fetcher->getColor(widget, opt, StyleDetailFetcher::SwitchButton_BorderColor, pseudoStatus);
    QColor bgColor = fetcher->getColor(widget, opt, StyleDetailFetcher::SwitchButton_Background, pseudoStatus);
    QColor indicatorCircularColor = fetcher->getColor(widget, opt,
                                                      StyleDetailFetcher::SwitchButton_IndicatorCircularBackground,
                                                      pseudoStatus);

    //背景
    if (isChecked) {
        QPainterPath backgroundPath;
        backgroundPath.addRoundedRect(opt->rect, radius, radius);
        p->fillPath(backgroundPath, bgColor);

        //indicator
        QRect indicatorCircularRect(opt->rect.right() - indicatorCircularSpacing - indicatorCircularSize,
                                    opt->rect.y() + (opt->rect.height() - indicatorCircularSize) / 2,
                                    indicatorCircularSize,
                                    indicatorCircularSize);

        QPainterPath painterPath;
        painterPath.addEllipse(indicatorCircularRect);
        p->fillPath(painterPath, indicatorCircularColor);
    } else {
        //border
        p->save();
        QPen pen;
        pen.setColor(borderColor);
        pen.setWidth(borderWidth);
        p->setPen(pen);
        p->drawRoundedRect(opt->rect, radius, radius);
        p->restore();

        //indicator
        QRect indicatorCircularRect(opt->rect.x() + indicatorCircularSpacing,
                                    opt->rect.y() + (opt->rect.height() - indicatorCircularSize) / 2,
                                    indicatorCircularSize,
                                    indicatorCircularSize);

        QPainterPath painterPath;
        painterPath.addEllipse(indicatorCircularRect);
        p->fillPath(painterPath, indicatorCircularColor);
    }

    return true;
}

bool DrawButtonHelper::drawSwitchButtonControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                               StyleDetailFetcher *fetcher, const QWidget *widget)
{
    const QStyleOptionButton *optionButton = qstyleoption_cast<const QStyleOptionButton *>(opt);
    if (!optionButton) {
        return true;
    }

    bool enabled = opt->state & QStyle::State_Enabled;
    bool reverseLayout(opt->direction == Qt::RightToLeft);
    int alignmentFlag(Qt::AlignVCenter | (reverseLayout ? Qt::AlignRight : Qt::AlignLeft));

    QRect indicatorRect, contentsRect;

    indicatorRect = style->subElementRect(SE_SwitchButtonIndicator, opt, widget);
    contentsRect = style->subElementRect(SE_SwitchButtonContents, opt, widget);

    QStyleOptionButton indicatorOption(*optionButton);
    indicatorOption.rect = indicatorRect;
    style->drawPrimitive(PE_SwitchButtonIndicator, &indicatorOption, p, widget);

    style->drawItemText(p, contentsRect, alignmentFlag, opt->palette, enabled, optionButton->text,
                        QPalette::WindowText);

    return true;
}

QRect DrawButtonHelper::switchButtonContetnsRect(const Style *style, const QStyleOption *opt, const QWidget *w)
{
    QRect contentsRect(opt->rect);
    return style->visualRect(opt->direction,
                             opt->rect,
                             contentsRect.adjusted(
                                     Metrics::SwitchButton_ItemSpacing + Metrics::SwitchButton_IndicatorWidth + 1,
                                     0, 0, 0));
}

QRect DrawButtonHelper::switchButtonIndicatorRect(const Style *style, const QStyleOption *opt, const QWidget *w)
{
    return style->visualRect(opt->direction,
                             opt->rect,
                             QRect(opt->rect.x() + 1,
                                   opt->rect.y() + (opt->rect.height() - Metrics::SwitchButton_IndicatorHeight) / 2,
                                   Metrics::SwitchButton_IndicatorWidth,
                                   Metrics::SwitchButton_IndicatorHeight));
}
