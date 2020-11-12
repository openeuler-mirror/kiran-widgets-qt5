//
// Created by lxh on 2020/11/10.
//

#include "marco-title-font-monitor.h"

#include <QGSettings>
#include <QFontDatabase>
#include <QVariant>

#define MARCO_GENERAL_SCHEMA            "org.mate.interface"
#define MARCO_GENERAL_KEY_TITLE_FONT    "titlebar-font"

MarcoTitleFontMonitor::MarcoTitleFontMonitor() :FontMonitor(nullptr){

}

MarcoTitleFontMonitor::~MarcoTitleFontMonitor() {
    delete marcoSettings;
}

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
    QString fontStyle = splitRes.takeLast();
    QString fontFamily = splitRes.join(' ');
    int fontPtSizeInt = fontPtSize.toInt();

    QFontDatabase database;
    return database.font(fontFamily, fontStyle, fontPtSizeInt);
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
        emit fontChanged(currentFont());
    }
}



