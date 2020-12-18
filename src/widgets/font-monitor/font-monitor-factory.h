/*
 * @file   font-monitor-factory.h
 * @brief  字体监控
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRAN_ACCOUNT_MANAGER_FONT_MONITOR_FACTORY_H
#define KIRAN_ACCOUNT_MANAGER_FONT_MONITOR_FACTORY_H

#include <QObject>
#include <QFont>

class FontMonitor : public QObject{
    Q_OBJECT
    friend class FontMonitorFactory;
public:
    explicit FontMonitor(QObject *parent = nullptr):QObject(parent){};
    virtual ~FontMonitor() = default;
    
    /* 派生需实现事件该方法，获取当前的字体 */
    virtual QFont currentFont() = 0;

private:
    /* 派生类需提供该方法，判断是否在当前桌面环境生效 */
    static bool isVaild(){
        return false;
    }

    /* 派生类需提供该方法，初始化，返回是否初始化成功 */
    virtual bool initMonitor() = 0;

signals:
    /* 监控到字体发生变化信号 */
    void fontChanged(QFont font);
};

class FontMonitorFactory {
private:
    FontMonitorFactory() = default;
public:

    /**
     * @brief 创建当前桌面环境应用程序字体监控器,不需要时需要delete
     * @return 字体监控器
     */
    static FontMonitor* createAppFontMonitor();

    /**
     * @brief 创建当前桌面环境标题栏字体监控器,不需要时需要delete
     * @return 字体监控
     */
    static FontMonitor* createAppTitleFontMonitor();
};

#endif //FONT_MONITOR_FACTORY_H
