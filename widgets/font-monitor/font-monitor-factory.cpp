//
// Created by lxh on 2020/11/10.
//

#include "font-monitor-factory.h"
#include "mate-desktop-font-monitor.h"
#include "marco-title-font-monitor.h"

#include <QDebug>

FontMonitor *FontMonitorFactory::createAppFontMonitor() {
    FontMonitor *fontMonitor = nullptr;

    if (MateDesktopFontMonitor::isVaild()) {
        fontMonitor = new MateDesktopFontMonitor();
    } else {
        qWarning() << "This desktop environment is not supported application font monitor";
        return nullptr;
    }

    if (!fontMonitor->initMonitor()) {
        delete fontMonitor;
        qWarning() << "init font monitor failed";
        return nullptr;
    }

    return fontMonitor;
}

FontMonitor *FontMonitorFactory::createAppTitleFontMonitor() {
    FontMonitor *fontMonitor = nullptr;

    if( MarcoTitleFontMonitor::isVaild() ){
        fontMonitor = new MarcoTitleFontMonitor();
    }else{
        qWarning() << "This desktop environment is not supported titlebar font monitor";
        return nullptr;
    }

    if (!fontMonitor->initMonitor()) {
        delete fontMonitor;
        qWarning() << "init font monitor failed";
        return nullptr;
    }

    return fontMonitor;
}
