//
// Created by lxh on 2020/11/10.
//

#ifndef KIRAN_ACCOUNT_MANAGER_MARCO_TITLE_FONT_MONITOR_H
#define KIRAN_ACCOUNT_MANAGER_MARCO_TITLE_FONT_MONITOR_H

#include "font-monitor-factory.h"

class QGSettings;

/**
 * @brief Marco标题栏字体监控
 * @fixme marco字体设置成regular情况下, org.mate.Marco.general titlebar-font值为＂Noto Sans CJK SC　10＂不存在Style("Blod","Reqular"等值),导致解析失败
 */
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
