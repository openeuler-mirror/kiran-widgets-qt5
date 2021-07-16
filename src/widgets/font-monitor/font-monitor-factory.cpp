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
