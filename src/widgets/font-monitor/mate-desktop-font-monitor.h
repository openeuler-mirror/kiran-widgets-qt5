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
 
#ifndef KIRAN_ACCOUNT_MANAGER_MATE_DESKTOP_FONT_MONITOR_H
#define KIRAN_ACCOUNT_MANAGER_MATE_DESKTOP_FONT_MONITOR_H

#include "font-monitor-factory.h"

#include <QSharedPointer>

class QGSettings;
/* mate桌面字体监控 */
class MateDesktopFontMonitor : public FontMonitor{
    Q_OBJECT
public:
    friend class FontMonitorFactory;
    MateDesktopFontMonitor();
    ~MateDesktopFontMonitor();

    QFont currentFont() override;

private:
    static bool isVaild();
    bool initMonitor() override;

private slots:
    void handlerChanged(const QString &key);

private:
    QGSettings *mateInterfaceSettings = nullptr;

};


#endif //MATE_DESKTOP_FONT_MONITOR_H
