//
// Created by lxh on 2020/11/10.
//

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