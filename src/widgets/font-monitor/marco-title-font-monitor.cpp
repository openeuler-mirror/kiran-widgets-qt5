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
 
#include "marco-title-font-monitor.h"

#include <QGSettings>
#include <QFontDatabase>
#include <QVariant>
#include <QDebug>

#define MARCO_GENERAL_SCHEMA            "org.mate.Marco.general"
#define MARCO_GENERAL_KEY_TITLE_FONT    "titlebarFont"

MarcoTitleFontMonitor::MarcoTitleFontMonitor() :FontMonitor(nullptr){

}

MarcoTitleFontMonitor::~MarcoTitleFontMonitor() {
    delete marcoSettings;
}

#include <QApplication>
QFont MarcoTitleFontMonitor::currentFont() {
    if( marcoSettings == nullptr ){
        return QFont();
    }
    QVariant var = marcoSettings->get(MARCO_GENERAL_KEY_TITLE_FONT);
    QString titleFontValue = var.toString();
    QStringList splitRes = titleFontValue.split(" ",QString::SkipEmptyParts);
    if(splitRes.size() < 3){
        return QFont();
    }

    QString fontPtSize = splitRes.takeLast();
    int fontPtSizeInt = fontPtSize.toInt();

    /*NOTE: marco 设置字体时如果是general，使用gsettings更新值时不会将General写入值中，导致解析失败*/
    QFontDatabase fontDatabase;
    QString fontStyle;
    QString fontFamily = splitRes.join(' ');
    if( fontDatabase.hasFamily(fontFamily) ){
        fontStyle = "Regular";
    }else{
        fontStyle = splitRes.takeLast();
        fontFamily = splitRes.join(' ');
    }

    return fontDatabase.font(fontFamily, fontStyle, fontPtSizeInt);
}

bool MarcoTitleFontMonitor::initMonitor() {
    if( marcoSettings!= nullptr ){
        return true;
    }
    marcoSettings = new QGSettings(MARCO_GENERAL_SCHEMA);
    connect(marcoSettings,&QGSettings::changed,
            this,&MarcoTitleFontMonitor::handlerChanged);
    return true;
}

bool MarcoTitleFontMonitor::isVaild() {
    return QGSettings::isSchemaInstalled(MARCO_GENERAL_SCHEMA);
}

void MarcoTitleFontMonitor::handlerChanged(const QString &key) {
    if( key == MARCO_GENERAL_KEY_TITLE_FONT ){
        qDebug() << "MarcoTitleFont changed:" << currentFont();
        emit fontChanged(currentFont());
    }
}



