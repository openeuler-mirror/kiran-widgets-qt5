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
 
#include "mate-desktop-font-monitor.h"

#include <QGSettings>
#include <QVariant>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

#define MATE_INTERFACE_SCHEMA   "org.mate.interface"
#define MATE_INTERFACE_KEY_FONT "fontName"

MateDesktopFontMonitor::MateDesktopFontMonitor()
        : FontMonitor(nullptr) {

}

MateDesktopFontMonitor::~MateDesktopFontMonitor() {
    /* NOTE:delete nullptr no effect */
    delete mateInterfaceSettings;
}

bool MateDesktopFontMonitor::isVaild() {
    return QGSettings::isSchemaInstalled(MATE_INTERFACE_SCHEMA);
}

QFont MateDesktopFontMonitor::currentFont() {
    if( mateInterfaceSettings == nullptr ){
        return QFont();
    }

    QVariant var = (*mateInterfaceSettings).get(MATE_INTERFACE_KEY_FONT);
    QString fontNameValue = var.toString();
    QStringList splitRes = fontNameValue.split(" ",QString::SkipEmptyParts);
    if( splitRes.size() < 3 ){
        return QFont();
    }

    QString fontPtSize = splitRes.takeLast();
    QString fontStyle = splitRes.takeLast();
    QString fontName = splitRes.join(' ');
    int fontPtSizeInt = fontPtSize.toInt();

    QFontDatabase fontDatabase;
    return fontDatabase.font(fontName,fontStyle,fontPtSizeInt);
}

bool MateDesktopFontMonitor::initMonitor() {
    if( mateInterfaceSettings!= nullptr ){
        return true;
    }
    mateInterfaceSettings = new QGSettings(MATE_INTERFACE_SCHEMA);
    connect(mateInterfaceSettings,&QGSettings::changed,
            this,&MateDesktopFontMonitor::handlerChanged);
    return true;
}

void MateDesktopFontMonitor::handlerChanged(const QString &key) {
    if( key == MATE_INTERFACE_KEY_FONT ){
        qDebug() << "MateDesktopFont changed:" << currentFont();
        emit fontChanged(currentFont());
    }
};