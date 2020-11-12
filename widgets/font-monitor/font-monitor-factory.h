//
// Created by lxh on 2020/11/10.
//

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

    virtual QFont currentFont() = 0;

private:
    /// 工厂判断是否有效,子类需覆盖该方法，实现检测桌面环境
    static bool isVaild(){
        return false;
    }
    virtual bool initMonitor() = 0;

signals:
    void fontChanged(QFont font);

};

class FontMonitorFactory {
private:
    FontMonitorFactory() = default;
public:
    static FontMonitor* createAppFontMonitor();
    static FontMonitor* createAppTitleFontMonitor();
};

#endif //FONT_MONITOR_FACTORY_H
