//
// Created by lxh on 2020/11/10.
//

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
