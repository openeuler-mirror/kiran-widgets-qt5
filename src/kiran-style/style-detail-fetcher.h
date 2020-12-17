/*
 * @file   style-detail-fetcher.h
 * @brief  从Css配置文件中获取相关绘制细节的类
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */

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

namespace Kiran {
    /**
     * @brief 提供从Css配置文件中取出相关绘制细节的接口
     */
    class StyleDetailFetcher : public QObject {
    Q_OBJECT
    public:
        /**
         * @brief 提供相关绘制细节属性名称,绘制细节类型名称格式为"Class_Property"格式
         * 需要声明Q_ENUMS,获取过程中会将该枚举值转换成字符串并切割
         */
        enum StyleDetailPropertyName {
            /* 初始化Style Palette的相关属性 */
            Palette_Base,
            Palette_Text,
            Palette_Window,
            Palette_WindowText,
            Palette_Highlight,
            Palette_HighlightedText,
            Palette_Button,
            Palette_ButtonText,

            /* Frame,Edit,Spinbox */
            Frame_Background,
            Frame_Radius,
            Frame_BorderColor,
            Frame_BorderWidth,

            /* Spinbox */
            Spinbox_ArrowBackground,
            Spinbox_ArrowSignColor,

            /* Button */
            Button_TextColor,
            Button_Radius,
            /* Flat Button */
            Button_FlatTextColor,
            Button_FlatBackground,
            Button_FlatBorderWidth,
            Button_FlatBorderColor,
            /* Normal Button */
            Button_NormalBackground,
            Button_NormalBorderWidth,
            Button_NormalBorderColor,
            /* Default Button */
            Button_DefaultBackground,
            Button_DefaultBorderWidth,
            Button_DefaultBorderColor,
            /* Warning Button */
            Button_WarningBackground,
            Button_WarningBorderWidth,
            Button_WarningBorderColor,

            /* QDockWidget下的QToolButton样式 */
            ToolButton_Background,

            /* QRadioButton */
            RadioButton_IndicatorColor,

            /* QCheckBox */
            CheckBox_BorderColor,
            CheckBox_IndicatorBackground,
            CheckBox_IndicatorSign,

            /* menu */
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

            /* combobo */
            ComboBox_BorderColor,
            ComboBox_EditBorderColor,
            ComboBox_BorderWidth,
            ComboBox_BorderRadius,
            ComboBox_Background,
            ComboBox_ArrowIndicatorColor,
            ComboBoxContainer_BorderColor,
            ComboBoxContainer_SeparatorColor,
            ComboBoxItem_Background,

            /* switch button */
            SwitchButton_BorderWidth,
            SwitchButton_BorderColor,
            SwitchButton_Background,
            SwitchButton_IndicatorCircularBackground,

            /* 滑动条滑块 */
            ScrollBarSlider_Background,

            /* QTabBar的Tab页 */
            TabBarTab_Background,

            /* 标题栏按钮图标绘制细节 */
            TitleBarButtonIcon_SignPressedColor,/** < 按下的颜色 */
            TitleBarButtonIcon_SignHoverColor,/** < 悬浮的颜色 */
            TitleBarButtonIcon_SignNormalColor,/** < 正常情况的颜色 */
            TitleBarButtonIcon_SignDisabledColor,/** < 禁用情况的颜色 */

            /* 搜索框 */
            SearchBox_Icon,
            SearchBox_Background,
            SearchBox_BorderRadius,
            SearchBox_BorderWidth,
            SearchBox_BorderColor,

            /* 箭头指示器 */
            IndicatorArrow_Icon,

            /* 进度条 */
            ProgressBar_GrooveColor,
            ProgressBar_ContentColor,

            /* KiranSidebarWidget的Item */
            KiranSiderbarItem_Height,
            KiranSiderbarItem_BackgroundColor,
            KiranSiderbarItem_Radius
        };

        Q_ENUM(StyleDetailPropertyName)

    private:
        /* Css值属性类型枚举 */
        enum StyleDetailValueType {
            VALUE_TYPE_COLOR, /** < 颜色类型 */
            VALUE_TYPE_BRUSH, /** < 画刷类型 */
            VALUE_TYPE_INT,   /** < 整数类型 */
            VALUE_TYPE_URL,   /** < URL类型 */
            VALUE_TYPE_REAL   /** < 浮点数类型 */
        };
    public:
        /**
         * @brief 样式细节获取类构造方法
         * @param styleType　样式类型，该类型决定了加载的CSS文件，影响绘制的细节
         * @param parent 父对象，建议设置，影响该对象的释放
         */
        StyleDetailFetcher(StyleEnum styleType, QObject *parent = nullptr);

        ~StyleDetailFetcher();


        /**
         * @brief 通过从CSS文件中取出相关属性来对画板进行初始化
         * @param palette 需要初始化的画板
         */
        void polish(QPalette *palette);

        /**
         * @brief 通过widget指针和绘制选项加入合适的伪选择器,再对CSS文件中的值进行匹配
         * @tparam ValueType   　属性值模板
         * @param widget       　控件指针，可能需要对其进行类型判断特殊处理
         * @param styleOption  　绘制选项，需要用到其中的State来加入伪选择器，提高匹配的准确性
         * @param selector     　属性类型枚举,通过metaEnum转换成字符串进行分割得到类名和属性名
         * @param valueTypeEnum  值类型枚举,通过该枚举将QCss::Declaration转换为特定的类型
         * @param specialqseudo　特殊的伪选择器
         * @return 取出来的绘制细节的值
         */
        template<class ValueType>
        ValueType getValue(const QWidget *widget,
                           const QStyleOption *styleOption,
                           StyleDetailPropertyName selector,
                           StyleDetailValueType valueTypeEnum,
                           quint64 specialqseudo = 0);

        /**
         * @brief 通过属性枚举和伪选择器集合和值类型进行属性匹配
         * @tparam ValueType    属性值模板
         * @param selector      属性类型枚举,通过metaEnum转换成字符串进行分割得到类名和属性名
         * @param qseudoClass   伪选择器集合
         * @param valueTypeEnum 值类型枚举,通过该枚举将QCss::Declaration转换为特定的类型
         * @return 取出来的绘制细节的值
         */
        template<class ValueType>
        ValueType getValue(StyleDetailPropertyName selector,
                           quint64 qseudoClass,
                           StyleDetailValueType valueTypeEnum);

        /**
         * @brief 通过widget指针和绘制选项加入合适的伪选择器,再对CSS文件中的值进行匹配,获取绘制颜色
         * @param widget        控件指针，可能需要对其进行类型判断特殊处理
         * @param styleOption   绘制选项，需要用到其中的State来加入伪选择器，提高匹配的准确性
         * @param selector      属性类型枚举,通过metaEnum转换成字符串进行分割得到类名和属性名
         * @param specialqseudo 特殊的伪选择器
         * @return 绘制的颜色
         */
        QColor getColor(const QWidget *widget, const QStyleOption *styleOption,
                        StyleDetailPropertyName selector, quint64 specialqseudo = 0);

        /**
         * @brief 通过属性枚举和伪选择器集合和值类型进行属性匹配，获取绘制颜色
         * @param selector    属性类型枚举,通过metaEnum转换成字符串进行分割得到类名和属性名
         * @param pseudoClass 伪选择器集合
         * @return 绘制的颜色
         */
        QColor getColor(StyleDetailPropertyName selector, quint64 pseudoClass = QCss::PseudoClass_Unspecified);

         /**
          * @brief 通过widget指针和绘制选项加入合适的伪选择器,再对CSS文件中的值进行匹配，获取画刷属性
          * @see getColor(const QWidget *, const QStyleOption *,StyleDetailPropertyName, quint64)
          */
        QBrush getBrush(const QWidget *widget, const QStyleOption *styleOption, StyleDetailPropertyName selector,
                        quint64 specialqseudo = 0);

        /**
         * @brief 通过属性枚举和伪选择器集合和值类型进行属性匹配，获取画刷属性
         * @see getColor(StyleDetailPropertyName, quint64)
         */
        QBrush getBrush(StyleDetailPropertyName selector, quint64 pseudoClass);

        /**
         * @brief 通过widget指针和绘制选项加入合适的伪选择器,再对CSS文件中的值进行匹配，获取Int属性
         * @see getColor(const QWidget *, const QStyleOption *,StyleDetailPropertyName, quint64)
         */
        int getInt(const QWidget *widget, const QStyleOption *styleOption,
                   StyleDetailPropertyName selector, quint64 specialqseudo = 0);

        /**
         * @brief  通过属性枚举和伪选择器集合和值类型进行属性匹配，获取Int属性
         * @see getColor(StyleDetailPropertyName, quint64)
         */
        int getInt(StyleDetailPropertyName selector, quint64 pseudoClass);

        /**
         * @brief 通过widget指针和绘制选项加入合适的伪选择器,再对CSS文件中的值进行匹配，获取Url属性
         * @see getColor(const QWidget *, const QStyleOption *,StyleDetailPropertyName, quint64)
         */
        QString getUrl(const QWidget *widget, const QStyleOption *styleOption,
                       StyleDetailPropertyName selector, quint64 specialqseudo = 0);

        /**
         * @brief 通过属性枚举和伪选择器集合和值类型进行属性匹配，获取Url属性
         * @see getColor(StyleDetailPropertyName, quint64)
         */
        QString getUrl(StyleDetailPropertyName selector, quint64 pseudoClass);

        /**
         * @brief 通过widget指针和绘制选项加入合适的伪选择器,再对CSS文件中的值进行匹配，获取浮点数属性
         * @see getColor(const QWidget *, const QStyleOption *,StyleDetailPropertyName, quint64)
         */
        qreal getReal(const QWidget *widget, const QStyleOption *styleOption,
                      StyleDetailPropertyName selector, quint64 specialqseudo = 0);

        /**
         * @brief 通过属性枚举和伪选择器集合和值类型进行属性匹配，获取浮点数属性
         * @see getColor(StyleDetailPropertyName, quint64)
         */
        qreal getReal(StyleDetailPropertyName selector, quint64 pseudoClass);

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
        QVariant fetchStyleDetail(const QWidget *widget,
                                  const QStyleOption *styleOption,
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
        bool FuzzyMatch(const QVector<QCss::Selector> &selectors, quint64 pseudoClass);

        /// 转换QStyleOption成伪状态选择器
        /// \param widget       控件,特别控件需要添加伪状态
        /// \param styleOption  样式选项，判断控件伪状态
        /// \return 转换后的伪状态
        quint64 convertStyleOption2Pseudo(const QWidget *widget,
                                          const QStyleOption *styleOption);

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
        QMap<QString, QVariant> m_styleDetailsCache;
    };
}

#endif //KIRANSTYLE_STYLE_DETAIL_FETCHER_H
