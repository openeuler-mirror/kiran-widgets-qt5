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
