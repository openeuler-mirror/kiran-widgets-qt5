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

    /// 派生需要事件该方法，获取当前的字体
    /// \return 当前字体
    virtual QFont currentFont() = 0;

private:
    /// 派生类需提供该方法，判断是否在当前桌面环境生效
    /// \return 是否可用
    static bool isVaild(){
        return false;
    }

    /// 派生类需提供该方法，初始化
    /// \return 初始化是否成功
    virtual bool initMonitor() = 0;

signals:
    /// 监控到字体发生变化时，发出该信号
    /// \param font
    void fontChanged(QFont font);

};

class FontMonitorFactory {
private:
    FontMonitorFactory() = default;
public:
    /// 创建当前桌面环境应用程序字体监控器
    /// 不需要时需要delete
    /// \return 字体监控
    static FontMonitor* createAppFontMonitor();

    /// 创建当前桌面环境标题栏字体监控器
    /// 不需要时需要delete
    /// \return 字体监控
    static FontMonitor* createAppTitleFontMonitor();
};

#endif //FONT_MONITOR_FACTORY_H
