//
// Created by lxh on 2020/11/24.
//

#ifndef KIRANSTYLE_STYLE_DETAIL_FETCHER_H
#define KIRANSTYLE_STYLE_DETAIL_FETCHER_H

#include <QObject>
#include <QPalette>
#include <QStyleOption>
#include <private/qcssparser_p.h>
#include <QUrl>
#include <QMutex>

#include "kiran-private-defines.h"
#include "kiran-public-define.h"

namespace Kiran{
    ///TODO:匹配规则加上特殊匹配,处理特殊情况，例如标题栏聚焦会有按下的样式
    class StyleDetailFetcher : public QObject{
        Q_OBJECT
    public:
        ///选择器和属性名的拼接
        ///eg:例如想取QLineEdit的输入框背景色
        ///   使用LineEdit_Background,会去搜索LineEdit{Background:xxx}的值
        enum StyleDetailPropertyName{
            Palette_Base,
            Palette_Text,
            Palette_Window,
            Palette_WindowText,
            Palette_Highlight,
            Palette_HighlightedText,
            Palette_Button,
            Palette_ButtonText,

            ///Frame,Edit,Spinbox
            Frame_Background,
            Frame_Radius,
            Frame_BorderColor,
            Frame_BorderWidth,

            ///Spinbox
            Spinbox_ArrowBackground,///按钮背景色
            Spinbox_ArrowSignColor,///按钮符号的颜色

            ///Button
            Button_TextColor,
            Button_Radius,
                //平面按钮flat
            Button_FlatTextColor,
            Button_FlatBackground,
            Button_FlatBorderWidth,
            Button_FlatBorderColor,
                //普通按钮
            Button_NormalBackground,
            Button_NormalBorderWidth,
            Button_NormalBorderColor,
                //默认按钮
            Button_DefaultBackground,
            Button_DefaultBorderWidth,
            Button_DefaultBorderColor,
                ///警告按钮
            Button_WarningBackground,
            Button_WarningBorderWidth,
            Button_WarningBorderColor,

            ///特殊的QDockWidget标题栏ToolButton
            ToolButton_Background,

            /// raido
            RadioButton_IndicatorColor,

            /// checkbox
            CheckBox_BorderColor,
            CheckBox_IndicatorBackground,
            CheckBox_IndicatorSign,

            /// menu
            Menu_BorderRadius,
            Menu_BorderColor,
            Menu_BorderWidth,
            Menu_Background,
            Menu_SeparatorWidth,
            Menu_SeparatorColor,
            Menu_CheckedIndicatorSignColor,
            Menu_CheckedIndicatorBackground,
            Menu_SubMenuArrowColor,
            Menu_ItemBackground,
            Menu_ItemSiderColor,

            /// combobo
            ComboBox_BorderColor,
            ComboBox_EditBorderColor,
            ComboBox_BorderWidth,
            ComboBox_BorderRadius,
            ComboBox_Background,
            ComboBox_ArrowIndicatorColor,
            ComboBoxContainer_BorderColor,
            ComboBoxContainer_SeparatorColor,
            ComboBoxItem_Background,

            SwitchButton_BorderWidth,
            SwitchButton_BorderColor,
            SwitchButton_Background,
            SwitchButton_IndicatorCircularBackground,

            ScrollBarSlider_Background,

            TabBarTab_Background,

            TitleBarButtonIcon_SignPressedColor,
            TitleBarButtonIcon_SignHoverColor,
            TitleBarButtonIcon_SignNormalColor,
            TitleBarButtonIcon_SignDisabledColor,

            SearchBox_Icon,
            SearchBox_Background,
            SearchBox_BorderRadius,
            SearchBox_BorderWidth,
            SearchBox_BorderColor,

            IndicatorArrow_Icon,

            ProgressBar_GrooveColor,
            ProgressBar_ContentColor
        };
        Q_ENUM(StyleDetailPropertyName)

    private:
        enum StyleDetailValueType{
            VALUE_TYPE_COLOR,
            VALUE_TYPE_BRUSH,
            VALUE_TYPE_INT,
            VALUE_TYPE_URL,
            VALUE_TYPE_REAL
        };
    public:
        StyleDetailFetcher(StyleEnum styleType,QObject *parent= nullptr);
        ~StyleDetailFetcher();

        /// 初始化主题调色板
        /// \param palette  调色板，用于绘制
        void polish(QPalette *palette);

        template<class ValueType>
        ValueType getValue(const QWidget* widget,const QStyleOption* styleOption,
                                  StyleDetailPropertyName selector,StyleDetailValueType valueType,
                                  quint64 specialqseudo = 0);
        template<class ValueType>
        ValueType getValue(StyleDetailPropertyName selector,quint64 qseudoClass,StyleDetailValueType valueType);

        QColor getColor( const QWidget* widget,const QStyleOption* styleOption,
                         StyleDetailPropertyName selector,quint64 specialqseudo = 0);
        QColor getColor( StyleDetailPropertyName selector,quint64 pseudoClass = QCss::PseudoClass_Unspecified);

        QBrush getBrush( const QWidget* widget,const QStyleOption* styleOption
                         ,StyleDetailPropertyName selector,quint64 specialqseudo = 0);
        QBrush getBrush( StyleDetailPropertyName selector,quint64 pseudoClass );

        int getInt( const QWidget* widget,const QStyleOption* styleOption,
                    StyleDetailPropertyName selector,quint64 specialqseudo = 0);
        int getInt( StyleDetailPropertyName selector,quint64 pseudoClass );

        QString getUrl( const QWidget* widget,const QStyleOption* styleOption,
                     StyleDetailPropertyName selector,quint64 specialqseudo = 0);
        QString getUrl( StyleDetailPropertyName selector,quint64 pseudoClass );

        qreal getReal( const QWidget* widget,const QStyleOption* styleOption,
                       StyleDetailPropertyName selector,quint64 specialqseudo = 0);
        qreal getReal( StyleDetailPropertyName selector,quint64 pseudoClass );

        int textFlags();
    private:
        ///　通过StyleEnum加载不同风格的样式细节
        void load();

        /// 输出加载到内存中的CSS
        void dump();

        /// 获取指定控件样式详细值
        /// \param widget           指定控件
        /// \param styleOption      控件当前绘制的选项
        /// \param selector         属性名的枚举
        /// \param valueType        值的类型
        /// \param specialqseudo    特殊的伪状态,需要加入匹配选项的
        /// \return 属性值
        QVariant fetchStyleDetail(const QWidget* widget,
                                  const QStyleOption* styleOption,
                                  StyleDetailPropertyName selector,
                                  StyleDetailValueType valueType,
                                  quint64 specialqseudo = QCss::PseudoClass_Unspecified);

        /// 获取指定控件样式详细值
        /// \param selector 选择器
        /// \param pseudoClass 伪状态
        /// \param valueType 值类型
        /// \return 样式详细值
        QVariant fetchStyleDetail(StyleDetailPropertyName selector,
                                  quint64 pseudoClass,
                                  StyleDetailValueType valueType);

        /// 将伪类转成字符串
        /// \param qseudoClass　伪类
        /// \return 字符串描述
        QString pseudoClassString(quint64 qseudoClass);

        ///　模糊匹配,优先完全匹配,再着判断待匹配伪状态包含选择器的伪状态
        /// \param selectors    选择器
        /// \param pseudoClass  待匹配的伪状态
        /// \return 是否匹配
        bool FuzzyMatch(const QVector<QCss::Selector>& selectors, quint64 pseudoClass);

        /// 转换QStyleOption成伪状态选择器
        /// \param widget       控件,特别控件需要添加伪状态
        /// \param styleOption  样式选项，判断控件伪状态
        /// \return 转换后的伪状态
        quint64 convertStyleOption2Pseudo(const QWidget* widget,
                                          const QStyleOption* styleOption);

        /// 存入缓存
        /// \param selector       选择器
        /// \param pseudoStatus   伪状态
        /// \param var            属性值
        void appendToCache(StyleDetailPropertyName selector,
                           quint64 pseudoStatus,
                           QVariant var);

        /// 查找缓存
        /// \param selector     选择器
        /// \param pseudoStatus 伪状态
        /// \return             属性值
        QVariant findFromCache(StyleDetailPropertyName selector,
                               quint64 pseudoStatus);

    private:
        StyleEnum m_styleEnum;
        QCss::StyleSheet m_styleDetail;
        QMutex m_cacheMutex;
        QMap<QString,QVariant> m_styleDetailsCache;
    };
}

#endif //KIRANSTYLE_STYLE_DETAIL_FETCHER_H
