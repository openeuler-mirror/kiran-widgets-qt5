//
// Created by lxh on 2020/12/7.
//

#include "draw-tab-bar-helper.h"
#include "style.h"
#include "draw-common-helper.h"

#include <QPainter>
#include <QDebug>
#include <QtWidgets/QStyleOption>

using namespace Kiran;

static bool isVertiacalTab(const QStyleOptionTab *option)
{
    QTabBar::Shape shape = option->shape;
    bool isVertiacal = ( shape == QTabBar::RoundedEast    ||
                         shape == QTabBar::RoundedWest    ||
                         shape == QTabBar::TriangularEast ||
                         shape == QTabBar::TriangularWest  );
    return isVertiacal;
}

//FIXME:需要和sizeFromContents获取的大小对应
void tabLayout(const Style *style, const QStyleOptionTab *opt, const QWidget *widget, QRect *textRect, QRect *iconRect)
{
    QRect tr = opt->rect;
    bool verticalTabs = isVertiacalTab(opt);

    if (verticalTabs)
        tr.setRect(0, 0, tr.height(), tr.width()); // 0, 0 as we will have a translate transform

    /// 垂直和水平偏移量,以突出当前选中的Tab标签
    int verticalShift = style->pixelMetric(QStyle::PM_TabBarTabShiftVertical, opt, widget);
    int horizontalShift = style->pixelMetric(QStyle::PM_TabBarTabShiftHorizontal, opt, widget);

    int hpadding = style->pixelMetric(QStyle::PM_TabBarTabHSpace, opt, widget) / 2;
    int vpadding = style->pixelMetric(QStyle::PM_TabBarTabVSpace, opt, widget) / 2;

    if (opt->shape == QTabBar::RoundedSouth || opt->shape == QTabBar::TriangularSouth)
        verticalShift = -verticalShift;

    tr.adjust(hpadding, verticalShift - vpadding, horizontalShift - hpadding, vpadding);
    bool selected = opt->state & QStyle::State_Selected;
    if (selected) {
        tr.setTop(tr.top() - verticalShift);
        tr.setRight(tr.right() - horizontalShift);
    }

    // left widget
    if (!opt->leftButtonSize.isEmpty()) {
        tr.setLeft(tr.left() + 4 +
                   (verticalTabs ? opt->leftButtonSize.height() : opt->leftButtonSize.width()));
    }
    // right widget
    if (!opt->rightButtonSize.isEmpty()) {
        tr.setRight(tr.right() - 4 -
                    (verticalTabs ? opt->rightButtonSize.height() : opt->rightButtonSize.width()));
    }

    // icon
    if (!opt->icon.isNull()) {
        QSize iconSize = opt->iconSize;
        if (!iconSize.isValid()) {
            int iconExtent = style->pixelMetric(QStyle::PM_SmallIconSize);
            iconSize = QSize(iconExtent, iconExtent);
        }
        QSize tabIconSize = opt->icon.actualSize(iconSize,
                                                 (opt->state & QStyle::State_Enabled) ? QIcon::Normal : QIcon::Disabled,
                                                 (opt->state & QStyle::State_Selected) ? QIcon::On : QIcon::Off);
        // High-dpi icons do not need adjustment; make sure tabIconSize is not larger than iconSize
        tabIconSize = QSize(qMin(tabIconSize.width(), iconSize.width()), qMin(tabIconSize.height(), iconSize.height()));

        *iconRect = QRect(tr.left(), tr.center().y() - tabIconSize.height() / 2,
                          tabIconSize.width(), tabIconSize.height());
        if (!verticalTabs)
            *iconRect = style->visualRect(opt->direction, opt->rect, *iconRect);
        tr.setLeft(tr.left() + tabIconSize.width() + 4);
    }

    if (!verticalTabs)
        tr = style->visualRect(opt->direction, opt->rect, tr);

    *textRect = tr;
}

bool DrawTabBarHelper::drawTabBarTabControl(const Style *style,
                                            const QStyleOption *opt,
                                            QPainter *p,
                                            StyleDetailFetcher *fetcher,
                                            const QWidget *widget)
{
    const QStyleOptionTab *tabOption(qstyleoption_cast<const QStyleOptionTab *>(opt));
    if (tabOption == nullptr) {
        return true;
    }

    bool vertiacal = isVertiacalTab(tabOption);
    QStyleOptionTab newTabOption = *tabOption;
    switch (tabOption->position) {
        case QStyleOptionTab::Beginning:
        case QStyleOptionTab::Middle:
            if (vertiacal)
                newTabOption.rect.adjust(0, 0, 0, -Metrics::TabBar_TabSpacing);
            else
                newTabOption.rect.adjust(0, 0, -Metrics::TabBar_TabSpacing, 0);
            break;
        case QStyleOptionTab::End:
        case QStyleOptionTab::OnlyOneTab:
            break;
    }

    style->drawControl(QStyle::CE_TabBarTabShape, &newTabOption, p, widget);
    style->drawControl(QStyle::CE_TabBarTabLabel, &newTabOption, p, widget);

    return true;
}

/// 绘制TabBar Tab中的文字和图标
bool DrawTabBarHelper::drawTabBarTabLabelControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                 StyleDetailFetcher *fetcher, const QWidget *widget)
{
    const QStyleOptionTab *tabOption(qstyleoption_cast<const QStyleOptionTab *>(opt));
    if (!tabOption) return true;

    bool enabled(opt->state & QStyle::State_Enabled);
    int textFlags = Qt::AlignLeft | Qt::AlignVCenter | Qt::TextHideMnemonic;
    bool isVertiacal = isVertiacalTab(tabOption);

    QRect rect(opt->rect);

    QRect iconRect, textRect;
    tabLayout(style, tabOption, widget, &textRect, &iconRect);
    textRect = style->subElementRect(QStyle::SE_TabBarTabText, opt, widget);

    ///垂直Tabs的坐标系的旋转平移转换
    QTransform vertiacalTransform;
    if (isVertiacal) {
        QPointF axisOriginPoint;
        qreal rotateAngle = 0.0;
        if (tabOption->shape == QTabBar::RoundedEast ||
            tabOption->shape == QTabBar::TriangularEast) {/// tabs显示在右侧,以矩形位置右上为原点，顺时针旋转坐标系90°
            axisOriginPoint = rect.topRight();
            rotateAngle = 90;
        } else {/// tabs显示在左侧,以矩形左下为原点，逆时针旋转坐标系90°
            axisOriginPoint = rect.bottomLeft();
            rotateAngle = -90;
        }
        vertiacalTransform = QTransform::fromTranslate(axisOriginPoint.x(), axisOriginPoint.y());
        vertiacalTransform.rotate(rotateAngle);
    }

    if (isVertiacal) {
        p->save();
        p->setTransform(vertiacalTransform);
    }

    if (!tabOption->icon.isNull()) {
        QPixmap tabIcon = tabOption->icon.pixmap(tabOption->iconSize,
                                                 (tabOption->state & QStyle::State_Enabled) ? QIcon::Normal
                                                                                            : QIcon::Disabled,
                                                 (tabOption->state & QStyle::State_Selected) ? QIcon::On
                                                                                             : QIcon::Off);
        p->drawPixmap(iconRect.x(), iconRect.y(), tabIcon);
    }

    style->drawItemText(p, textRect, textFlags, opt->palette, enabled, tabOption->text, QPalette::WindowText);

    if (isVertiacal) {
        p->restore();
    }

    return true;
}

bool DrawTabBarHelper::drawTabBarTabShapeControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                 StyleDetailFetcher *fetcher, const QWidget *widget)
{
    const QStyleOptionTab *tabOption(qstyleoption_cast<const QStyleOptionTab *>(opt));
    if (!tabOption) return true;

    p->setRenderHint(QPainter::Antialiasing, true);

    const QPalette &palette(opt->palette);
    const QStyle::State &state(opt->state);
    bool enabled(state & QStyle::State_Enabled);
    bool selected(state & QStyle::State_Selected);
    bool mouseOver(state & QStyle::State_MouseOver);

    int pseudoClass = QCss::PseudoClass_Unspecified;

    if (!enabled) {
        pseudoClass = QCss::PseudoClass_Disabled;
    } else if (selected) {
        pseudoClass = QCss::PseudoClass_Selected;
    } else if (mouseOver) {
        pseudoClass = QCss::PseudoClass_Hover;
    }

    //NOTE:忽略了styleoption中的shape

    QColor bgColor = fetcher->getColor(StyleDetailFetcher::TabBarTab_Background, pseudoClass);


    QPainterPath painterPath = DrawCommonHelper::getRoundedRectanglePath(opt->rect,
                                                                         Metrics::TabBar_TabItemRadius,
                                                                         Metrics::TabBar_TabItemRadius,
                                                                         0, 0);

    if (bgColor.isValid()) {
        p->fillPath(painterPath, bgColor);
    }

    return false;
}

QRect DrawTabBarHelper::tabBarTabLeftButtonElementRect(const Style *style,
                                                       const QStyleOption *opt,
                                                       const QWidget *w)
{
    const QStyleOptionTab *tabOption = qstyleoption_cast<const QStyleOptionTab *>(opt);
    if (!tabOption || tabOption->rightButtonSize.isEmpty()) return QRect();

    const QRect &tabRect(opt->rect);
    const QSize &buttonSize(tabOption->leftButtonSize);
    QRect buttonRect(QPoint(0, 0), buttonSize);

    switch (tabOption->shape) {

        case QTabBar::RoundedNorth:
        case QTabBar::TriangularNorth:
        case QTabBar::RoundedSouth:
        case QTabBar::TriangularSouth:
            buttonRect.moveLeft(tabRect.left() + Metrics::TabBar_TabItemSpacing);
            buttonRect.moveTop((tabRect.height() - buttonSize.height()) / 2);
            buttonRect = QStyle::visualRect(opt->direction, opt->rect, buttonRect);
            break;

        case QTabBar::RoundedWest:
        case QTabBar::TriangularWest:
            buttonRect.moveBottom(tabRect.bottom() - Metrics::TabBar_TabMarginWidth);
            buttonRect.moveLeft((tabRect.width() - buttonRect.width()) / 2);
            break;

        case QTabBar::RoundedEast:
        case QTabBar::TriangularEast:
            buttonRect.moveTop(tabRect.top() + Metrics::TabBar_TabMarginWidth);
            buttonRect.moveLeft((tabRect.width() - buttonRect.width()) / 2);
            break;

        default:
            break;
    }

    return buttonRect;
}

//获取TabBar Tab的右侧控件绘制位置
QRect DrawTabBarHelper::tabBarTabRightButtonElementRect(const Style *style,
                                                        const QStyleOption *opt,
                                                        const QWidget *w)
{
    const QStyleOptionTab *tabOption(qstyleoption_cast<const QStyleOptionTabV3 *>(opt));
    if (!tabOption || tabOption->rightButtonSize.isEmpty()) return QRect();

    QRect tabRect(opt->rect);
    QSize buttonSize(tabOption->rightButtonSize);
    QRect buttonRect(QPoint(0, 0), buttonSize);

    switch (tabOption->shape) {
        case QTabBar::RoundedNorth:
        case QTabBar::TriangularNorth:
        case QTabBar::RoundedSouth:
        case QTabBar::TriangularSouth:
            buttonRect.moveRight(tabRect.right() - Metrics::TabBar_TabMarginWidth);
            buttonRect.moveTop((tabRect.height() - buttonRect.height()) / 2);
            buttonRect = QStyle::visualRect(opt->direction, opt->rect, buttonRect);
            break;

        case QTabBar::RoundedWest:
        case QTabBar::TriangularWest:
            buttonRect.moveTop(tabRect.top() + Metrics::TabBar_TabMarginWidth);
            buttonRect.moveLeft((tabRect.width() - buttonRect.width()) / 2);
            break;

        case QTabBar::RoundedEast:
        case QTabBar::TriangularEast:
            buttonRect.moveBottom(tabRect.bottom() - Metrics::TabBar_TabMarginWidth);
            buttonRect.moveLeft((tabRect.width() - buttonRect.width()) / 2);
            break;

        default:
            break;
    }

    return buttonRect;
}

//获取TabBar文本绘制矩形
QRect DrawTabBarHelper::tabBarTabTabTextElementRect(const Style *style,
                                                    const QStyleOption *opt,
                                                    const QWidget *w)
{
    QRect iconRect, textRect;

    const QStyleOptionTab *optionTab = qstyleoption_cast<const QStyleOptionTab *>(opt);
    if (!optionTab) {
        return QRect();
    }

    tabLayout(style, optionTab, w, &textRect, &iconRect);

    return textRect;
}

//获取TabBarTab该有的大小
QSize DrawTabBarHelper::tabBarTabSizeFromContents(const Style *style,
                                                  const QStyleOption *opt,
                                                  const QSize &contentsSize,
                                                  const QWidget *w)
{
    const QStyleOptionTab *tabOption(qstyleoption_cast<const QStyleOptionTab *>(opt));
    if (tabOption == nullptr) {
        return contentsSize;
    }

    bool hasText(!tabOption->text.isEmpty());
    bool hasIcon(!tabOption->icon.isNull());
    bool hasLeftButton(tabOption->leftButtonSize.isEmpty());
    bool hasRightButton(tabOption->rightButtonSize.isEmpty());

    ///宽度增量
    int widthIncrement = 0;
    if (hasIcon && !(hasText || hasLeftButton || hasRightButton)) widthIncrement -= 4;
    if (hasText && hasIcon) widthIncrement += Metrics::TabBar_TabItemSpacing;
    if (hasLeftButton && (hasText || hasIcon)) widthIncrement += Metrics::TabBar_TabItemSpacing;
    if (hasRightButton && (hasText || hasIcon || hasLeftButton)) widthIncrement += Metrics::TabBar_TabItemSpacing;

    if (hasText) {
        widthIncrement += opt->fontMetrics.width(tabOption->text) * 0.2;
    }

    QSize tabBarTabSize(contentsSize);
    if (isVertiacalTab(tabOption)) {
        tabBarTabSize.rheight() += widthIncrement;
        if (hasIcon && !hasText)
            tabBarTabSize = tabBarTabSize.expandedTo(QSize(Metrics::TabBar_TabMinHeight, 0));
        else
            tabBarTabSize = tabBarTabSize.expandedTo(QSize(Metrics::TabBar_TabMinHeight, Metrics::TabBar_TabMinWidth));
    } else {
        tabBarTabSize.rwidth() += widthIncrement;
        if (hasIcon && !hasText)
            tabBarTabSize = tabBarTabSize.expandedTo(QSize(0, Metrics::TabBar_TabMinHeight));
        else
            tabBarTabSize = tabBarTabSize.expandedTo(QSize(Metrics::TabBar_TabMinWidth, Metrics::TabBar_TabMinHeight));
    }

    return tabBarTabSize;
}

bool DrawTabBarHelper::drawIndicatorTabClosePrimitive(const Style *style,
                                                      const QStyleOption *opt,
                                                      QPainter *painter,
                                                      StyleDetailFetcher *detaulFetcher,
                                                      const QWidget *widget)
{
    // get icon and check
    QIcon icon(style->standardIcon(QStyle::SP_TitleBarCloseButton, opt, widget));
    if (icon.isNull()) return false;


    // store state
    const QStyle::State &state(opt->state);
    bool enabled(state & QStyle::State_Enabled);
    bool active(state & QStyle::State_Raised);
    bool sunken(state & QStyle::State_Sunken);

    // decide icon mode and state
    QIcon::Mode iconMode;
    QIcon::State iconState;
    if (!enabled) {
        iconMode = QIcon::Disabled;
        iconState = QIcon::Off;

    } else {

        if (active) iconMode = QIcon::Active;
        else iconMode = QIcon::Normal;

        iconState = sunken ? QIcon::On : QIcon::Off;
    }

    // icon size
    int iconWidth(style->pixelMetric(QStyle::PM_SmallIconSize, opt, widget));
    QSize iconSize(iconWidth, iconWidth);


    // get pixmap
    QPixmap pixmap(icon.pixmap(iconSize, iconMode, iconState));

    // render
    style->drawItemPixmap(painter, opt->rect, Qt::AlignCenter, pixmap);

    return true;
}