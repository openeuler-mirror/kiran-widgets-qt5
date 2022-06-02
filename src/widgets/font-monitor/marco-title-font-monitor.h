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
