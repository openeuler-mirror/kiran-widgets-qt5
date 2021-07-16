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