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
