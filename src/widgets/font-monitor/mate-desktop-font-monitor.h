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
