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
 
#include "style-detail-fetcher.h"

#include <QMap>
#include <QDebug>
#include <QFile>
#include <QMetaEnum>
#include <QStyle>

using namespace QCss;

static const QMap<quint64, QString> pseudoMap = {
        {PseudoClass_Unknown,          "unknow"},
        {PseudoClass_Enabled,          "enabled"},
        {PseudoClass_Disabled,         "disabled"},
        {PseudoClass_Pressed,          "pressed"},
        {PseudoClass_Focus,            "focus"},
        {PseudoClass_Hover,            "hover"},
        {PseudoClass_Checked,          "checked"},
        {PseudoClass_Unchecked,        "unchecked"},
        {PseudoClass_Indeterminate,    "indeterminate"},
        {PseudoClass_Unspecified,      "unspecifie"},
        {PseudoClass_Selected,         "selected"},
        {PseudoClass_Horizontal,       "horizontal"},
        {PseudoClass_Vertical,         "vertical"},
        {PseudoClass_Window,           "window"},
        {PseudoClass_Children,         "chindren"},
        {PseudoClass_Sibling,          "sibling"},
        {PseudoClass_Default,          "default"},
        {PseudoClass_First,            "first"},
        {PseudoClass_Last,             "last"},
        {PseudoClass_Middle,           "middle"},
        {PseudoClass_OnlyOne,          "only one"},
        {PseudoClass_PreviousSelected, "previousSelected"},
        {PseudoClass_NextSelected,     "NextSelected"},
        {PseudoClass_Flat,             "flat"},
        {PseudoClass_Left,             "left"},
        {PseudoClass_Right,            "right"},
        {PseudoClass_Top,              "top"},
        {PseudoClass_Bottom,           "bottom"},
        {PseudoClass_Exclusive,        "exclusive"},
        {PseudoClass_NonExclusive,     "nonExclusive"},
        {PseudoClass_Frameless,        "frameless"},
        {PseudoClass_ReadOnly,         "readOnly"},
        {PseudoClass_Active,           "active"},
        {PseudoClass_Closable,         "closable"},
        {PseudoClass_Movable,          "movable"},
        {PseudoClass_Floatable,        "floatable"},
        {PseudoClass_Minimized,        "minimized"},
        {PseudoClass_Maximized,        "maximized"},
        {PseudoClass_On,               "on"},
        {PseudoClass_Off,              "off"},
        {PseudoClass_Editable,         "editable"},
        {PseudoClass_Item,             "item"},
        {PseudoClass_Closed,           "closed"},
        {PseudoClass_Open,             "open"},
        {PseudoClass_EditFocus,        "editFocus"},
        {PseudoClass_Alternate,        "alternate"},
        {PseudoClass_Any,              "any"},
};

Kiran::StyleDetailFetcher::StyleDetailFetcher(Kiran::StyleEnum styleType, QObject *parent)
        : QObject(parent),
          m_styleEnum(styleType)
{
    load();
}

Kiran::StyleDetailFetcher::~StyleDetailFetcher()
{

}

void Kiran::StyleDetailFetcher::load()
{
    static QMap<StyleEnum, QString> styleDetailFileMap = {
            {KIRAN_BLACK, ":/kiranwidgets-test/style-detail/kiran-dark.css"},
    };

    auto detailFileIter = styleDetailFileMap.find(m_styleEnum);
    if (detailFileIter == styleDetailFileMap.end()) {
        qWarning() << "StyleDetailFetcher: can't find style detail file";
        return;
    }

    QCss::Parser parser(detailFileIter.value(), true);
    if (!parser.parse(&m_styleDetail)) {
        qWarning() << "parse style detail failed," << parser.errorSymbol().text;
        return;
    }

    qDebug() << "load style detail:" << detailFileIter.value() << "success!";
}

QVariant Kiran::StyleDetailFetcher::fetchStyleDetail(const QWidget *widget, const QStyleOption *styleOption,
                                                     Kiran::StyleDetailFetcher::StyleDetailPropertyName selector,
                                                     StyleDetailValueType valueType,
                                                     quint64 specialqseudo)
{
    /// 获取没伪选择器的样式
    QVariant defaultValue = fetchStyleDetail(selector, QCss::PseudoClass_Unspecified,valueType);

    /// 获取当前窗口的其他状态 用于辅助增加伪状态选择匹配的准确性
    quint64 styleOptionPseudoClass = convertStyleOption2Pseudo(widget, styleOption);
    quint64 extendPresudoClass = styleOptionPseudoClass|specialqseudo;

    ///　关键状态,做为匹配的关键因素
    quint64 keyClass = 0;
    if (!(styleOption->state & QStyle::State_Enabled)) {/// disable状态
        keyClass = QCss::PseudoClass_Disabled;
    } else if (styleOption->state & QStyle::State_Sunken) {/// 凹陷或按下
        keyClass = QCss::PseudoClass_Pressed;
    } else if (styleOption->state & QStyle::State_MouseOver) {/// 鼠标悬浮
        keyClass = QCss::PseudoClass_Hover;
    } else if (styleOption->state & QStyle::State_HasFocus) {/// 聚焦　
        keyClass = QCss::PseudoClass_Focus;
    }

#if 0
    QMetaEnum enumInfo = QMetaEnum::fromType<StyleDetailPropertyName>();
    qInfo() << "fetch style detail:" << "\n"
            << "    widget:        "   << widget->objectName() << "\n"
            << "    selector:      "   << enumInfo.valueToKey(selector) << "\n"
            << "    special pseudo:"   << pseudoClassString(specialqseudo) << "\n"
            << "    key pseudo:    "   << pseudoClassString(keyClass) << "\n"
            << "    extend pseudo: "   << pseudoClassString(extendPresudoClass);
#endif

    if( keyClass!=0 ){
        QVariant bestFitVar = fetchStyleDetail(selector,keyClass|extendPresudoClass,valueType);
        if(bestFitVar.isValid()){
            return bestFitVar;
        }
        QVariant keyVar = fetchStyleDetail(selector,keyClass,valueType);
        if(keyVar.isValid()){
            return keyVar;
        }
    }

    if( extendPresudoClass!=0 ){
        QVariant extentVar = fetchStyleDetail(selector,extendPresudoClass,valueType);
        if(extentVar.isValid()){
            return extentVar;
        }
    }

    if( specialqseudo!=0 ){
        QVariant specialVar = fetchStyleDetail(selector,specialqseudo,valueType);
        if(specialVar.isValid()){
            return  specialVar;
        }
    }

    return fetchStyleDetail(selector,QCss::PseudoClass_Unspecified,valueType);
}

QVariant Kiran::StyleDetailFetcher::fetchStyleDetail(StyleDetailPropertyName selector,
                                                     quint64 pseudoClass,
                                                     StyleDetailValueType valueType)
{
    QVariant var = findFromCache(selector, pseudoClass);
    if (var.isValid()) {
        return var;
    }

    //使用元对象中的信息将selector转换成字符串
    QMetaEnum metaEnum = QMetaEnum::fromType<StyleDetailPropertyName>();
    QString strSelector = metaEnum.valueToKey(selector);

    //将字符串拆分成类型选择器和属性名进行匹配
    const QStringList selectors = strSelector.split("_");
    const QString typeName = selectors.at(0);
    const QString propertyName = selectors.at(1);

    auto values = m_styleDetail.nameIndex.values(typeName);

    for (const StyleRule &rule : values) {
        if (!FuzzyMatch(rule.selectors, pseudoClass)) {
            continue;
        }
        for (const Declaration &declartion : rule.declarations) {
            if (declartion.d->property != propertyName) {
                continue;
            }
            QVariant propertyValue;
            switch(valueType){
                case VALUE_TYPE_COLOR:
                    propertyValue = declartion.colorValue();
                    break;
                case VALUE_TYPE_BRUSH:
                    propertyValue = declartion.brushValue();
                    break;
                case VALUE_TYPE_INT:
                {
                    int i = 0;
                    declartion.intValue(&i);
                    propertyValue = i;
                    break;
                }
                case VALUE_TYPE_URL:
                    propertyValue = declartion.uriValue();
                    break;
                case VALUE_TYPE_REAL:
                {
                    qreal real = 0.0;
                    declartion.realValue(&real);
                    propertyValue = real;
                    break;
                }
                default:
                    qWarning() << "this type is not supported at this time";
                    continue;
            }
            appendToCache(selector,pseudoClass,propertyValue);
            return propertyValue;
        }
    }

    appendToCache(selector,pseudoClass,QVariant());
    return QVariant();
}

void Kiran::StyleDetailFetcher::dump()
{
    QMultiHash<QString, StyleRule>::iterator iter;
    for (iter = m_styleDetail.nameIndex.begin();
         iter != m_styleDetail.nameIndex.end();
         iter++) {
        qInfo() << "name:" << iter.key();
        StyleRule rule = iter.value();
        for (auto iter : rule.selectors) {
            qInfo() << "    selector:" << pseudoClassString(iter.pseudoClass());
        }
        for (const Declaration declaration : rule.declarations) {
            qInfo() << "    declaration:";
            qInfo() << "        propertyName:" << declaration.d->property;
            qInfo() << "        values:";
            for (const Value &value : declaration.d->values) {
                qInfo() << "            type:" << value.type;
                qInfo() << "            variant:" << value.variant;
            }
        }
    }
}

void Kiran::StyleDetailFetcher::appendToCache(StyleDetailPropertyName selector,
                                              quint64 pseudoStatus,
                                              QVariant var)
{
    //使用元对象中的信息将selector转换成字符串
    QMetaEnum metaEnum = QMetaEnum::fromType<StyleDetailPropertyName>();
    QString strSelector = metaEnum.valueToKey(selector);

    //将字符选择器和伪选择器拼接作为Key
    QString key = QString("%1:%2").arg(strSelector).arg(pseudoStatus);

    if (m_styleDetailsCache.find(key) == m_styleDetailsCache.end()) {
        m_styleDetailsCache.insert(key, var);
    }
}

QVariant Kiran::StyleDetailFetcher::findFromCache(StyleDetailPropertyName selector,
                                                  quint64 pseudoStatus)
{

    //使用元对象中的信息将selector转换成字符串
    QMetaEnum metaEnum = QMetaEnum::fromType<StyleDetailPropertyName>();
    QString strSelector = metaEnum.valueToKey(selector);

    //将字符选择器和伪选择器拼接作为Key
    QString key = QString("%1:%2").arg(strSelector).arg(pseudoStatus);

    QVariant var;
    auto iter = m_styleDetailsCache.find(key);
    if (iter != m_styleDetailsCache.end()) {
        var = iter.value();
    }
    return var;
}

bool Kiran::StyleDetailFetcher::FuzzyMatch(const QVector<QCss::Selector> &selectors, quint64 pseudoClass)
{
    bool isMatch = false;

    ///完整匹配
    for (const Selector &selector:selectors) {
        if (selector.pseudoClass() == pseudoClass) {
            isMatch = true;
            break;
        }
    }

    ///包含
    if (!isMatch) {
        for (const Selector &selector:selectors) {
            if ((selector.pseudoClass() | pseudoClass) == pseudoClass) {
                isMatch = true;
                break;
            }
        }
    }

    return isMatch;
}

quint64 Kiran::StyleDetailFetcher::convertStyleOption2Pseudo(const QWidget *widget,
                                                             const QStyleOption *styleOption)
{
    quint64 pesudoClass = 0;

    if (styleOption->state & QStyle::State_Enabled) {
        pesudoClass |= QCss::PseudoClass_Enabled;
    }

    if (styleOption->state & QStyle::State_Active)
        pesudoClass |= QCss::PseudoClass_Active;

    if (styleOption->state & QStyle::State_Window)
        pesudoClass |= QCss::PseudoClass_Window;

    if (styleOption->state & QStyle::State_On)
        pesudoClass |= (QCss::PseudoClass_On | QCss::PseudoClass_Checked);

    if (styleOption->state & QStyle::State_Off)
        pesudoClass |= (QCss::PseudoClass_Off | QCss::PseudoClass_Unchecked);

    if (styleOption->state & QStyle::State_NoChange)
        pesudoClass |= QCss::PseudoClass_Indeterminate;

    if (styleOption->state & QStyle::State_Selected)
        pesudoClass |= QCss::PseudoClass_Selected;

    if (styleOption->state & QStyle::State_Horizontal)
        pesudoClass |= QCss::PseudoClass_Horizontal;
    else
        pesudoClass |= QCss::PseudoClass_Vertical;

    if (styleOption->state & (QStyle::State_Open | QStyle::State_On | QStyle::State_Sunken))
        pesudoClass |= QCss::PseudoClass_Open;
    else
        pesudoClass |= QCss::PseudoClass_Closed;

    if (styleOption->state & QStyle::State_Children)
        pesudoClass |= QCss::PseudoClass_Children;

    if (styleOption->state & QStyle::State_Sibling)
        pesudoClass |= QCss::PseudoClass_Sibling;

    if (styleOption->state & QStyle::State_ReadOnly)
        pesudoClass |= QCss::PseudoClass_ReadOnly;

    if (styleOption->state & QStyle::State_Item)
        pesudoClass |= QCss::PseudoClass_Item;

    return pesudoClass;
}

#define PALETTE_BRUSH(palette, colorRole) \
    palette->setColor(QPalette::All,QPalette::colorRole,getColor(Palette_##colorRole,QCss::PseudoClass_Unspecified))

#define PALETTE_DISABLED_BRUSH(palette, colorRole) \
    palette->setColor(QPalette::Disabled,QPalette::colorRole,getColor(Palette_##colorRole,QCss::PseudoClass_Disabled))

void Kiran::StyleDetailFetcher::polish(QPalette *palette)
{
    PALETTE_BRUSH(palette, Base);
    PALETTE_BRUSH(palette, Text);
    PALETTE_BRUSH(palette, Window);
    PALETTE_BRUSH(palette, WindowText);
    PALETTE_BRUSH(palette, Highlight);
    PALETTE_BRUSH(palette, HighlightedText);
    PALETTE_BRUSH(palette, Button);
    PALETTE_BRUSH(palette, ButtonText);

    PALETTE_DISABLED_BRUSH(palette, Text);
    PALETTE_DISABLED_BRUSH(palette, WindowText);
    PALETTE_DISABLED_BRUSH(palette, Highlight);
    PALETTE_DISABLED_BRUSH(palette, HighlightedText);
    PALETTE_DISABLED_BRUSH(palette,ButtonText);
}

template<class ValueType>
ValueType Kiran::StyleDetailFetcher::getValue(const QWidget* widget, const QStyleOption* styleOption,
                                              StyleDetailPropertyName selector, StyleDetailValueType valueTypeEnum, quint64 specialqseudo){
    QVariant var;
    var = fetchStyleDetail(widget, styleOption, selector, valueTypeEnum, specialqseudo);
    return var.value<ValueType>();
}

template<class ValueType>
ValueType Kiran::StyleDetailFetcher::getValue(StyleDetailPropertyName selector,quint64 qseudoClass
        ,StyleDetailValueType valueTypeEnum){
    QVariant var;
    var = fetchStyleDetail(selector, qseudoClass, valueTypeEnum);
    return var.value<ValueType>();
}

QColor Kiran::StyleDetailFetcher::getColor( const QWidget* widget,const QStyleOption* styleOption,
                                            StyleDetailPropertyName selector ,quint64 specialqseudo){
    return getValue<QColor>(widget,styleOption,selector,VALUE_TYPE_COLOR,specialqseudo);
}

QColor Kiran::StyleDetailFetcher::getColor( StyleDetailPropertyName selector,quint64 pseudoClass ){
    return getValue<QColor>(selector,pseudoClass,VALUE_TYPE_COLOR);
}

QBrush Kiran::StyleDetailFetcher::getBrush( const QWidget* widget,const QStyleOption* styleOption,
                                            StyleDetailPropertyName selector,quint64 specialqseudo ){
    return getValue<QBrush>(widget,styleOption,selector,VALUE_TYPE_BRUSH,specialqseudo);
}

QBrush Kiran::StyleDetailFetcher::getBrush( StyleDetailPropertyName selector,
                                            quint64 pseudoClass ){
    return getValue<QBrush>(selector,pseudoClass,VALUE_TYPE_BRUSH);
}

int Kiran::StyleDetailFetcher::getInt( const QWidget* widget,const QStyleOption* styleOption,
                                       StyleDetailPropertyName selector,quint64 specialqseudo ){
    return getValue<int>(widget,styleOption,selector,VALUE_TYPE_INT,specialqseudo);
}

int Kiran::StyleDetailFetcher::getInt( StyleDetailPropertyName selector,
                                       quint64 pseudoClass ){
    return getValue<int>(selector,pseudoClass,VALUE_TYPE_INT);
}

QString Kiran::StyleDetailFetcher::getUrl( const QWidget* widget,const QStyleOption* styleOption,
                                        StyleDetailPropertyName selector,quint64 specialqseudo){
    return getValue<QString>(widget,styleOption,selector,VALUE_TYPE_URL,specialqseudo);
}

QString Kiran::StyleDetailFetcher::getUrl( StyleDetailPropertyName selector,
                                        quint64 pseudoClass ){
    return getValue<QString>(selector,pseudoClass,VALUE_TYPE_URL);
}

qreal Kiran::StyleDetailFetcher::getReal( const QWidget* widget,const QStyleOption* styleOption,
                                          StyleDetailPropertyName selector,quint64 specialqseudo){
    return getValue<qreal>(widget,styleOption,selector,VALUE_TYPE_REAL,specialqseudo);
}

qreal Kiran::StyleDetailFetcher::getReal( StyleDetailPropertyName selector,
                                          quint64 pseudoClass ){
    return getValue<qreal>(selector,pseudoClass,VALUE_TYPE_REAL);
}

QString Kiran::StyleDetailFetcher::pseudoClassString(quint64 pseudoClass)
{
    QStringList pseudoClassList;
    for (auto iter = pseudoMap.begin();
         iter != pseudoMap.end();
         iter++) {
        if (pseudoClass & iter.key()) {
            pseudoClassList.append(iter.value());
        }
    }
    return pseudoClassList.join(",");
}

int Kiran::StyleDetailFetcher::textFlags()
{
#if 1
    return Qt::TextShowMnemonic;
#else
    return Qt::TextHideMnemonic;
#endif
}
