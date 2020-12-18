//
// Created by lxh on 2020/11/10.
//

#ifndef KIRAN_ACCOUNT_MANAGER_MARCO_TITLE_FONT_MONITOR_H
#define KIRAN_ACCOUNT_MANAGER_MARCO_TITLE_FONT_MONITOR_H

#include "font-monitor-factory.h"

class QGSettings;

/* Marco标题栏字体监控 */
class MarcoTitleFontMonitor : public FontMonitor{
    Q_OBJECT
public:
    friend class FontMonitorFactory;
    MarcoTitleFontMonitor();
    ~MarcoTitleFontMonitor();

    QFont currentFont() override;

private:
    static bool isVaild();
    bool initMonitor() override;

private slots:
    void handlerChanged(const QString &key);

private:
    QGSettings *marcoSettings = nullptr;
};

#endif //MARCO_TITLE_FONT_MONITOR_H
