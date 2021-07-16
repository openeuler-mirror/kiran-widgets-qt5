 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd. 
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
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



