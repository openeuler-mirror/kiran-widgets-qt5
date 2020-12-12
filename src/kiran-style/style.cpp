//
// Created by lxh on 2020/11/16.
//

#include "style.h"
#include "style-data/style-detail-fetcher.h"

#include "style-helper/draw-common-helper.h"
#include "style-helper/draw-frame-helper.h"
#include "style-helper/draw-line-edit-helper.h"
#include "style-helper/draw-button-helper.h"
#include "style-helper/draw-spinbox-helper.h"
#include "style-helper/draw-menu-helper.h"
#include "style-helper/draw-combo-box-helper.h"
#include "style-helper/draw-scroll-bar-helper.h"
#include "style-helper/draw-tab-bar-helper.h"
#include "style-helper/draw-search-box-helper.h"
#include "style-helper/draw-progress-bar-helper.h"

#include "delegate/combo-box-item-delegate.h"

#include <QMap>
#include <QDebug>
#include <QPainter>
#include <QtWidgets/QStyleOption>
#include <QAbstractScrollArea>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QToolButton>
#include <QFormLayout>
#include <QAbstractItemView>
#include <QGraphicsView>
#include <QMainWindow>
#include <QCheckBox>
#include <QRadioButton>
#include <QApplication>
#include <QComboBox>
#include <QListView>
#include <private/qstyleanimation_p.h>

using namespace Kiran;

Style::Style(StyleEnum type)
        : ParentStyleClass("fusion"),
          m_styleType(type),
          m_detailFetcher(new StyleDetailFetcher(type, this))
{
    setObjectName("kiran-style");
}

Style::~Style(){
    for(auto iter=animations.begin();iter!=animations.end();iter++){
        delete iter.value();
    }
};

void Style::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption *opt,
                          QPainter *p, const QWidget *w) const
{
    typedef bool (*DrawPrimitiveFunc)(const Style *, const QStyleOption *, QPainter *, StyleDetailFetcher *,
                                      const QWidget *);

    static const QMap<QStyle::PrimitiveElement, DrawPrimitiveFunc> drawPrimitiveFuncMap = {
            {PE_Frame,                 DrawFrameHelper::drawFramePrimitive},
            {PE_FrameLineEdit,         DrawLineEditHelper::drawFrameLineEditPrimitive},

            {PE_PanelButtonTool,       DrawButtonHelper::drawPanelButtonToolPrimitive},

            {PE_IndicatorRadioButton,  DrawButtonHelper::drawIndicatorRadioButton},
            {PE_IndicatorCheckBox,     DrawButtonHelper::drawIndicatorCheckBox},

            {PE_PanelMenu,             DrawMenuHelper::drawPanelMenuPrimitive},

            {PE_PanelScrollAreaCorner, DrawScrollBarHelper::drawScrollAreaCornerPrimitive},

            {PE_IndicatorTabClose,     DrawTabBarHelper::drawIndicatorTabClosePrimitive},
            {PE_IndicatorTabTearLeft,  DrawTabBarHelper::drawIndicatorTabTearLeft},
            {PE_IndicatorTabTearRight, DrawTabBarHelper::drawIndicatorTabTearRight},

            {PE_IndicatorArrowUp,      DrawCommonHelper::drawIndicatorArrowUpPrimitive},
            {PE_IndicatorArrowDown,    DrawCommonHelper::drawIndicatorArrowDownPrimitive},
            {PE_IndicatorArrowLeft,    DrawCommonHelper::drawIndicatorArrowLeftPrimitive},
            {PE_IndicatorArrowRight,   DrawCommonHelper::drawIndicatorArrowRightPrimitive},

            {PE_FrameFocusRect,        nullptr}
    };

    auto iter = drawPrimitiveFuncMap.find(pe);

    p->save();
    if (iter == drawPrimitiveFuncMap.end()) {
        ParentStyleClass::drawPrimitive(pe, opt, p, w);
    } else {
        if (*iter) {
            (*iter)(this, opt, p, m_detailFetcher, w);
        }
    }
    p->restore();
}

void Style::drawControl(ControlElement element, const QStyleOption *opt,
                        QPainter *p, const QWidget *w) const
{
    typedef bool (*DrawControlFunc)(const Style *, const QStyleOption *, QPainter *, StyleDetailFetcher *,
                                    const QWidget *);
    static const QMap<QStyle::ControlElement, DrawControlFunc> drawControlFuncMap = {

            {CE_PushButtonBevel,  DrawButtonHelper::drawPushButtonBevelControl},
            {CE_PushButtonLabel,  DrawButtonHelper::drawPushButtonLabelControl},
            {CE_PushButton,       DrawButtonHelper::drawPushButtonControl},

            {CE_ToolButtonLabel,  DrawButtonHelper::drawToolButtonLabelControl},

            {CE_CheckBoxLabel,    DrawButtonHelper::drawCheckBoxLabelControl},
            {CE_RadioButtonLabel, DrawButtonHelper::drawCheckBoxLabelControl},

            {CE_MenuBarEmptyArea, DrawMenuHelper::drawMenuBarEmptryAreaControl},
            {CE_MenuBarItem,      DrawMenuHelper::drawMenuBarItemControl},
            {CE_MenuEmptyArea,    DrawMenuHelper::drawMenuEmptryAreaControl},
            {CE_MenuItem,         DrawMenuHelper::drawMenuItemControl},

            {CE_ScrollBarAddLine, DrawScrollBarHelper::drawScrollBarAddLineControl},
            {CE_ScrollBarSubLine, DrawScrollBarHelper::drawScrollBarSubLineControl},
            {CE_ScrollBarAddPage, DrawScrollBarHelper::drawScrollBarAddPageControl},
            {CE_ScrollBarSubPage, DrawScrollBarHelper::drawScrollBarSubPageControl},
            {CE_ScrollBarSlider,  DrawScrollBarHelper::drawScrollBarSliderControl},

            {CE_TabBarTab,        DrawTabBarHelper::drawTabBarTabControl},
            {CE_TabBarTabLabel,   DrawTabBarHelper::drawTabBarTabLabelControl},
            {CE_TabBarTabShape,   DrawTabBarHelper::drawTabBarTabShapeControl},

            {CE_ProgressBar,        DrawProgressBarHelper::drawProgressBarControl},
            {CE_ProgressBarGroove,  DrawProgressBarHelper::drawProgressBarGrooveControl},
            {CE_ProgressBarContents,DrawProgressBarHelper::drawProgressBarContentsControl},
            {CE_ProgressBarLabel,   DrawProgressBarHelper::drawProgressBarLabelControl}
    };

    auto iter = drawControlFuncMap.find(element);
    p->save();
    if (iter == drawControlFuncMap.end()) {
        ParentStyleClass::drawControl(element, opt, p, w);
    } else {
        if (*iter) {
            (*iter)(this, opt, p, m_detailFetcher, w);
        }
    }
    p->restore();
}

QRect Style::subElementRect(QStyle::SubElement se, const QStyleOption *opt,
                            const QWidget *widget) const
{
    switch (se) {
        case SE_LineEditContents:
            return DrawLineEditHelper::lineEditContentsRect(this, opt, widget);

        case SE_CheckBoxContents:
        case SE_RadioButtonContents:
            return DrawButtonHelper::checkBoxContentsRect(this, opt, widget);
        case SE_RadioButtonIndicator:
        case SE_CheckBoxIndicator:
            //fixme:修改
            return ParentStyleClass::subElementRect(SE_CheckBoxIndicator, opt, widget).
                    translated(Metrics::CheckBox_ItemSpacing, 0);

        case SE_TabBarTabLeftButton:
            return DrawTabBarHelper::tabBarTabLeftButtonElementRect(this, opt, widget);
        case SE_TabBarTabRightButton:
            return DrawTabBarHelper::tabBarTabRightButtonElementRect(this, opt, widget);
        case SE_TabBarTabText:
            return DrawTabBarHelper::tabBarTabTabTextElementRect(this, opt, widget);
        case SE_TabBarTearIndicatorLeft:
            return DrawTabBarHelper::tabBarTearIndicatorLeftRect(this, opt, widget);
        case SE_TabBarTearIndicatorRight:
            return DrawTabBarHelper::tabBarTearIndicatorRightRect(this, opt, widget);
        case SE_TabBarScrollLeftButton:
            return DrawTabBarHelper::tabBarScrollLeftButtonRect(this,opt,widget);
        case SE_TabBarScrollRightButton:
            return DrawTabBarHelper::tabBarScrollRightButtonRect(this,opt,widget);

        case SE_ProgressBarGroove:
            return DrawProgressBarHelper::progressBarGrooveRect(this,opt,widget);
        case SE_ProgressBarContents:
            return DrawProgressBarHelper::progressBarContentsRect(this,opt,widget);
        case SE_ProgressBarLabel:
            return DrawProgressBarHelper::progressBarLabelRect(this,opt,widget);

        default:
            return ParentStyleClass::subElementRect(se, opt, widget);
    }
}


void Style::drawComplexControl(QStyle::ComplexControl cc,
                               const QStyleOptionComplex *opt, QPainter *p, const QWidget *w) const
{
    typedef bool (*DrawComplexControlFunc)(const Style *, const QStyleOptionComplex *, StyleDetailFetcher *, QPainter *,
                                           const QWidget *);
    static const QMap<ComplexControl, DrawComplexControlFunc> drawComplexControlFuncMap = {
            {CC_SpinBox,    DrawSpinboxHelper::drawSpinBoxCompleControl},
            {CC_ToolButton, DrawButtonHelper::drawToolButtonComplexControl},
            {CC_ComboBox,   DrawComboBoxHelper::drawComboBoxComplexControl},
            {CC_ScrollBar,  DrawScrollBarHelper::drawScrollBarComplexControl}
    };

    auto iter = drawComplexControlFuncMap.find(cc);

    p->save();
    if (iter == drawComplexControlFuncMap.end()) {
        ParentStyleClass::drawComplexControl(cc, opt, p, w);
    } else {
        if (*iter) {
            (*iter)(this, opt, m_detailFetcher, p, w);
        }
    }
    p->restore();
}

QStyle::SubControl Style::hitTestComplexControl(QStyle::ComplexControl cc,
                                                const QStyleOptionComplex *opt, const QPoint &pt,
                                                const QWidget *w) const
{
    switch (cc) {
        case QStyle::CC_ScrollBar:
            return DrawScrollBarHelper::hitTestScrollBarComplexControl(this, opt, pt, w);
        default:
            return ParentStyleClass::hitTestComplexControl(cc, opt, pt, w);;
    }
}

QRect Style::subControlRect(QStyle::ComplexControl cc,
                            const QStyleOptionComplex *opt, QStyle::SubControl sc,
                            const QWidget *w) const
{
    switch (cc) {
        case QStyle::CC_SpinBox:
            return DrawSpinboxHelper::spinBoxSubControlRect(this, opt, sc, w);
        case QStyle::CC_ComboBox:
            return DrawComboBoxHelper::comboBoxSubControlRect(this, opt, sc, w);
        case QStyle::CC_ScrollBar:
            return DrawScrollBarHelper::scrollBarSubControlRect(this, opt, sc, w);
        default:
            return ParentStyleClass::subControlRect(cc, opt, sc, w);
    }
}

QSize Style::sizeFromContents(QStyle::ContentsType element, const QStyleOption *option,
                              const QSize &size, const QWidget *widget) const
{
    switch (element) {
        case CT_CheckBox:
        case CT_RadioButton:
            return DrawButtonHelper::checkBoxSizeFromContents(this, option, size, widget);
        case CT_LineEdit:
            return DrawLineEditHelper::lineEditSizeFromContents(this, option, size, widget);
        case CT_MenuItem:
            return DrawMenuHelper::menuItemSizeFromContents(this, option, size, widget);
        case CT_TabBarTab:
            return DrawTabBarHelper::tabBarTabSizeFromContents(this, option, size, widget);
        case CT_ProgressBar:
            return DrawProgressBarHelper::progressBarSizeFromContents(this,option,size,widget);
        default:
            return ParentStyleClass::sizeFromContents(element, option, size, widget);
    }
}

QSize Style::sizeFromContents(KiranContentsType ct, const QStyleOption *opt, const QSize &contentsSize,
                              const QWidget *widget) const
{
    switch (ct) {
        case CT_SwitchButton:
            return DrawButtonHelper::switchButtonSizeFromContents(this, opt, contentsSize, widget);
        default:
            return contentsSize;
    }
}

int Style::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option,
                       const QWidget *widget) const
{
    // handle special cases
    switch (metric) {
        // frame width
        case PM_DefaultFrameWidth:
            if (widget && widget->inherits("QComboBoxPrivateContainer")) return 1;
            if (qobject_cast<const QMenu *>(widget)) return Metrics::Menu_FrameWidth;
            if (qobject_cast<const QLineEdit *>(widget) ||
                qobject_cast<const QTextEdit *>(widget) ||
                qobject_cast<const QPlainTextEdit *>(widget))
                return Metrics::LineEdit_FrameWidth;
            if (qobject_cast<const QAbstractScrollArea *>(widget)) return Metrics::ScrollArea_FrameWidth;
            // fallback
            return Metrics::Frame_FrameWidth;
        case PM_ComboBoxFrameWidth: {
            const QStyleOptionComboBox *comboBoxOption(qstyleoption_cast<const QStyleOptionComboBox *>(option));
            return comboBoxOption && comboBoxOption->editable ? Metrics::LineEdit_FrameWidth
                                                              : Metrics::ComboBox_FrameWidth;
        }
        case PM_SpinBoxFrameWidth:
            return Metrics::SpinBox_FrameWidth;
        case PM_ToolBarFrameWidth:
            return Metrics::ToolBar_FrameWidth;
        case PM_ToolTipLabelFrameWidth:
            return Metrics::ToolTip_FrameWidth;
            // layout
        case PM_LayoutLeftMargin:
        case PM_LayoutTopMargin:
        case PM_LayoutRightMargin:
        case PM_LayoutBottomMargin: {
            /*
             * use either Child margin or TopLevel margin,
             * depending on  widget type
             */
            if ((option && (option->state & QStyle::State_Window)) || (widget && widget->isWindow())) {
                return Metrics::Layout_TopLevelMarginWidth;
            } else if (widget && widget->inherits("KPageView")) {
                return 0;
            } else {
                return Metrics::Layout_ChildMarginWidth;
            }
        }
        case PM_LayoutHorizontalSpacing:
            return Metrics::Layout_DefaultSpacing;
        case PM_LayoutVerticalSpacing:
            return Metrics::Layout_DefaultSpacing;
            // buttons
        case PM_ButtonMargin: {
            // needs special case for kcalc buttons, to prevent the application to set too small margins
            if (widget && widget->inherits("KCalcButton")) return Metrics::Button_MarginWidth + 4;
            else return Metrics::Button_MarginWidth;
        }
        case PM_ButtonDefaultIndicator:
            return 0;
        case PM_ButtonShiftHorizontal:
            return 0;
        case PM_ButtonShiftVertical:
            return 0;
        case PM_MenuBarPanelWidth:
            return 0;
        case PM_MenuBarHMargin:
            return 0;
        case PM_MenuBarVMargin:
            return 0;
        case PM_MenuBarItemSpacing:
            return 0;
        case PM_MenuDesktopFrameWidth:
            return 0;
        case PM_MenuButtonIndicator:
            return Metrics::MenuButton_IndicatorWidth;
        case PM_MenuVMargin:
            if (qobject_cast<const QComboBox *>(widget))
                return 0;
            else
                return 6;
        case PM_MenuHMargin:
            return 1;
        case PM_ToolBarHandleExtent:
            return Metrics::ToolBar_HandleExtent;
        case PM_ToolBarSeparatorExtent:
            return Metrics::ToolBar_SeparatorWidth;
        case PM_ToolBarExtensionExtent:
            return pixelMetric(PM_SmallIconSize, option, widget) + 2 * Metrics::ToolButton_MarginWidth;
        case PM_ToolBarItemMargin:
            return 0;
        case PM_ToolBarItemSpacing:
            return Metrics::ToolBar_ItemSpacing;
            // tabbars
        case PM_TabBarTabShiftVertical:
            return 0;
        case PM_TabBarTabShiftHorizontal:
            return 0;
        case PM_TabBarTabOverlap:
            return Metrics::TabBar_TabOverlap;
        case PM_TabBarBaseOverlap:
            return Metrics::TabBar_BaseOverlap;
        case PM_TabBarTabHSpace:
            return 2 * Metrics::TabBar_TabMarginWidth;
        case PM_TabBarTabVSpace:
            return 2 * Metrics::TabBar_TabMarginHeight;
        case PM_TabCloseIndicatorWidth:
        case PM_TabCloseIndicatorHeight:
            return pixelMetric(PM_SmallIconSize, option, widget);
        ///TabBar Tab过多时 需左右移动显示的滚动条的按钮宽度
        case PM_TabBarScrollButtonWidth:
            return Metrics::TabBar_ScrollButtonWidth;
        ///scrollbars
        case PM_ScrollBarExtent:
            return Metrics::ScrollBar_Extend;
        case PM_ScrollBarSliderMin:
            return Metrics::ScrollBar_MinSliderHeight;
        ///title bar
        case PM_TitleBarHeight:
            return 2 * Metrics::TitleBar_MarginWidth + pixelMetric(PM_SmallIconSize, option, widget);
        ///sliders
        case PM_SliderThickness:
            return Metrics::Slider_ControlThickness;
        case PM_SliderControlThickness:
            return Metrics::Slider_ControlThickness;
        case PM_SliderLength:
            return Metrics::Slider_ControlThickness;
        // checkboxes and radio buttons
        case PM_IndicatorWidth:
            return Metrics::CheckBox_Size;
        case PM_IndicatorHeight:
            return Metrics::CheckBox_Size;
        case PM_ExclusiveIndicatorWidth:
            return Metrics::CheckBox_Size;
        case PM_ExclusiveIndicatorHeight:
            return Metrics::CheckBox_Size;
        // list heaaders
        case PM_HeaderMarkSize:
            return Metrics::Header_ArrowSize;
        case PM_HeaderMargin:
            return Metrics::Header_MarginWidth;
        // dock widget
        // return 0 here, since frame is handled directly in polish
        case PM_DockWidgetFrameWidth:
            return 0;
        case PM_DockWidgetTitleMargin:
            return Metrics::Frame_FrameWidth;
        case PM_DockWidgetTitleBarButtonMargin:
            return Metrics::ToolButton_MarginWidth;
        case PM_SplitterWidth:
            return Metrics::Splitter_SplitterWidth;
        case PM_DockWidgetSeparatorExtent:
            return Metrics::Splitter_SplitterWidth;
        case PM_ScrollView_ScrollBarOverlap:
            return 0;
        case PM_ScrollView_ScrollBarSpacing:
            return 0;
        default:
            return ParentStyleClass::pixelMetric(metric, option, widget);
    }
}

int Style::styleHint(QStyle::StyleHint sh, const QStyleOption *opt,
                     const QWidget *w, QStyleHintReturn *shret) const
{
    switch (sh) {
        case SH_RubberBand_Mask: {
            if (QStyleHintReturnMask *mask = qstyleoption_cast<QStyleHintReturnMask *>(shret)) {
                mask->region = opt->rect;
                /*
                 * need to check on widget before removing inner region
                 * in order to still preserve rubberband in MainWindow and QGraphicsView
                 * in QMainWindow because it looks better
                 * in QGraphicsView because the painting fails completely otherwise
                 */
                if (w && (
                        qobject_cast<const QAbstractItemView *>(w->parent()) ||
                        qobject_cast<const QGraphicsView *>(w->parent()) ||
                        qobject_cast<const QMainWindow *>(w->parent()))) { return true; }

                // also check if widget's parent is some itemView viewport
                if (w && w->parent() &&
                    qobject_cast<const QAbstractItemView *>(w->parent()->parent()) &&
                    static_cast<const QAbstractItemView *>( w->parent()->parent())->viewport() ==
                    w->parent()) { return true; }

                // mask out center
                mask->region -= DrawCommonHelper::insideMargin(opt->rect, 1);

                return true;
            }
            return false;
        }
        case SH_ComboBox_ListMouseTracking:
            return true;
        case SH_ComboBox_Popup:
            return true;
        case SH_MenuBar_MouseTracking:
            return true;
        case SH_Menu_MouseTracking:
            return true;
        case SH_Menu_SubMenuPopupDelay:
            return 150;
        case SH_Menu_SloppySubMenus:
            return true;
        case SH_Widget_Animate:
            return true;
        case SH_Menu_SupportsSections:
            return true;
        case SH_DialogButtonBox_ButtonsHaveIcons:
            return false;
        case SH_GroupBox_TextLabelVerticalAlignment:
            return Qt::AlignVCenter;
        case SH_TabBar_Alignment:
            return Qt::AlignVCenter | Qt::AlignLeft;
        case SH_TabBar_CloseButtonPosition:
            return QTabBar::RightSide;
        case SH_ToolBox_SelectedPageTitleBold:
            return false;
        case SH_ScrollBar_MiddleClickAbsolutePosition:
            return true;
        case SH_ScrollView_FrameOnlyAroundContents:
            return false;
        case SH_FormLayoutFormAlignment:
            return Qt::AlignLeft | Qt::AlignTop;
        case SH_FormLayoutLabelAlignment:
            return Qt::AlignRight;
        case SH_FormLayoutFieldGrowthPolicy:
            return QFormLayout::ExpandingFieldsGrow;
        case SH_FormLayoutWrapPolicy:
            return QFormLayout::DontWrapRows;
        case SH_MessageBox_TextInteractionFlags:
            return Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse;
        case SH_ProgressDialog_CenterCancelButton:
            return false;
        case SH_MessageBox_CenterButtons:
            return false;
        case SH_RequestSoftwareInputPanel:
            return RSIP_OnMouseClick;
        case SH_TitleBar_NoBorder:
            return true;
        case SH_DockWidget_ButtonsHaveFrame:
            return false;
        default:
            return ParentStyleClass::styleHint(sh, opt, w, shret);
    }
}

QIcon Style::standardIcon(QStyle::StandardPixmap standardIcon,
                          const QStyleOption *opt, const QWidget *widget) const
{
    if (m_iconCache.contains(standardIcon)) {
        return m_iconCache.value(standardIcon);
    }

    QIcon icon;
    switch (standardIcon) {

        case SP_TitleBarNormalButton:
        case SP_TitleBarMinButton:
        case SP_TitleBarMaxButton:
        case SP_TitleBarCloseButton:
        case SP_DockWidgetCloseButton:
            icon = titleBarButtonIcon(m_detailFetcher, standardIcon, opt, widget);
            break;

//        case SP_ToolBarHorizontalExtensionButton:
//        case SP_ToolBarVerticalExtensionButton:
//            icon = toolBarExtensionIcon(standardIcon, opt, widget);
//            break;
    }

    if (!icon.isNull()) {
        IconCache *cache = const_cast<IconCache *>(&m_iconCache);
        cache->insert(standardIcon, icon);
        return icon;
    }

    return ParentStyleClass::standardIcon(standardIcon, opt, widget);
}

QIcon Style::titleBarButtonIcon(StyleDetailFetcher *fetcher,
                                QStyle::StandardPixmap standardIcon,
                                const QStyleOption *opt, const QWidget *widget) const
{
    TitleBarButtonType buttonType;
    switch (standardIcon) {
        case SP_TitleBarNormalButton:
            buttonType = ButtonRestore;
            break;
        case SP_TitleBarMinButton:
            buttonType = ButtonMinimize;
            break;
        case SP_TitleBarMaxButton:
            buttonType = ButtonMaximize;
            break;
        case SP_TitleBarCloseButton:
        case SP_DockWidgetCloseButton:
            buttonType = ButtonClose;
            break;
        default:
            return QIcon();
    }

    struct IconData {
        QColor _color;
        QIcon::Mode _mode;
        QIcon::State _state;
    };

    QColor disabledColor = fetcher->getColor(StyleDetailFetcher::TitleBarButtonIcon_SignDisabledColor);
    QColor pressedColor = fetcher->getColor(StyleDetailFetcher::TitleBarButtonIcon_SignPressedColor);
    QColor hoverColor = fetcher->getColor(StyleDetailFetcher::TitleBarButtonIcon_SignHoverColor);
    QColor normalColor = fetcher->getColor(StyleDetailFetcher::TitleBarButtonIcon_SignNormalColor);

    ///QIcon::State
    ///     QIcon::On  按钮按下
    ///     QIcon::Off 按钮没被按下
    ///QIcon::Mode
    ///     QIcon::Normal    默认状态
    ///     QIcon::Selected  选中
    ///     QIcon::Active    悬浮
    ///     QIocn::Disabled  按钮禁用
    QList<IconData> iconTypes = {
            {normalColor,   QIcon::Normal,   QIcon::Off},
            {hoverColor,    QIcon::Selected, QIcon::Off},
            {hoverColor,    QIcon::Active,   QIcon::Off},
            {disabledColor, QIcon::Disabled, QIcon::Off},

            {pressedColor,  QIcon::Normal,   QIcon::On},
            {pressedColor,  QIcon::Selected, QIcon::On},
            {pressedColor,  QIcon::Active,   QIcon::On},
            {disabledColor, QIcon::Disabled, QIcon::On}
    };

    static const QList<int> iconSizes = {8, 16, 22, 32, 48};

    // output icon
    QIcon icon;
    for (const IconData &iconData: iconTypes) {
        for (const int &iconSize: iconSizes) {
            // create pixmap
            QPixmap pixmap(iconSize, iconSize);
            pixmap.fill(Qt::transparent);

            // create painter and render
            QPainter painter(&pixmap);
            DrawCommonHelper::drawDecorationButton(&painter, pixmap.rect(), iconData._color, buttonType);
            painter.end();

            // store
            icon.addPixmap(pixmap, iconData._mode, iconData._state);
        }
    }

    return icon;
}

void Style::polish(QPalette &palette)
{
    m_detailFetcher->polish(&palette);
}

void Style::polish(QApplication *app)
{
    ParentStyleClass::polish(app);
}

void Style::polish(QWidget *widget)
{
    ParentStyleClass::polish(widget);

    if (!widget) {
        return;
    }

    if (qobject_cast<QSpinBox *>(widget) ||
        qobject_cast<QDateTimeEdit *>(widget) ||
        qobject_cast<QPushButton *>(widget) ||
        qobject_cast<QToolButton *>(widget) ||
        qobject_cast<QCheckBox *>(widget) ||
        qobject_cast<QRadioButton *>(widget) ||
        qobject_cast<QMenu *>(widget) ||
        widget->inherits("QComboBoxPrivateContainer") ||
        qobject_cast<QTabBar *>(widget)) {
        widget->setAttribute(Qt::WA_Hover);
    }

    if (qobject_cast<QMenu *>(widget) ||
        widget->inherits("QComboBoxPrivateContainer")) {
        widget->setAttribute(Qt::WA_TranslucentBackground);
    }

    if (QComboBox *comboBox = qobject_cast<QComboBox *>(widget)) {
        comboBox->setItemDelegate(new ComboBoxItemDelegate(comboBox, comboBox->view()));
    }

    if (auto toolBtn = qobject_cast<QToolButton *>(widget)) {
        if (toolBtn->autoRaise()) {
            //对于平面工具按钮，相应地调整前景和背景角色
            widget->setBackgroundRole(QPalette::NoRole);
            widget->setForegroundRole(QPalette::WindowText);
        }
    }

}

void Style::unpolish(QWidget *widget)
{
    ParentStyleClass::unpolish(widget);
}

void Style::unpolish(QApplication *application)
{
    ParentStyleClass::unpolish(application);
}

bool Style::isKiranStyle()
{
    return qobject_cast<Style *>(qApp->style());
}

Style *Style::castToKiranStyle()
{
    return qobject_cast<Style *>(qApp->style());
}

void Style::drawControl(KiranControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    p->save();
    switch (ce) {
        case CE_SwitchButton:
            DrawButtonHelper::drawSwitchButtonControl(this, opt, p, m_detailFetcher, w);
            break;
        default:
            break;
    }
    p->restore();
}

void Style::drawPrimitive(KiranPrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    p->save();
    switch (pe) {
        case PE_SwitchButtonIndicator:
            DrawButtonHelper::drawSwitchButtonIndicatorPrimitive(this, opt, p, m_detailFetcher, w);
            break;
        case PE_SearchBoxIndicator:
            DrawSearchBoxHelper::drawSearchBoxIndicatorPrimitive(this, opt, p, m_detailFetcher, w);
            break;
        default:
            break;
    }
    p->restore();
}

QRect Style::subElementRect(KiranSubElement se, const QStyleOption *opt, const QWidget *widget) const
{
    switch (se) {
        case SE_SwitchButtonContents:
            return DrawButtonHelper::switchButtonContetnsRect(this, opt, widget);
        case SE_SwitchButtonIndicator:
            return DrawButtonHelper::switchButtonIndicatorRect(this, opt, widget);
        default:
            return opt->rect;
    }
}

QList<const QObject *> Style::animationTargets() const
{
    return animations.keys();
}

QStyleAnimation *Style::animation(const QObject *target) const
{
    return animations.value(target);
}

void Style::removeAnimation()
{
    QObject *animation = sender();
    if (animation)
        animations.remove(animation->parent());
}

void Style::startAnimation(QStyleAnimation *animation) const
{
    stopAnimation(animation->target());
    connect(animation, SIGNAL(destroyed()), SLOT(removeAnimation()), Qt::UniqueConnection);
    animations.insert(animation->target(), animation);
    animation->start();
}

void Style::stopAnimation(const QObject *target) const
{
    QStyleAnimation *animation = animations.take(target);
    if (animation) {
        animation->stop();
        delete animation;
    }
}
