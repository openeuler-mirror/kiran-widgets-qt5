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
 
#ifndef QAPPLICATIONDEMO_KIRAN_APPLICATION_PRIVATE_H
#define QAPPLICATIONDEMO_KIRAN_APPLICATION_PRIVATE_H

#include "kiran-application.h"

#include <QObject>
#include <QFont>

class FontMonitor;
class KiranApplicationPrivate : public QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranApplication);
public:
    KiranApplicationPrivate(KiranApplication* ptr);
    ~KiranApplicationPrivate();

public:
    void init();

private:
    void setupTranslations();
    void updateAppFont();

    //NOTE:暂时不向外提供设置是否自适应字体的接口
    void setAdaptiveAppFont(bool enable);
    void initKiranStyle();
    bool adaptiveAppFont();

private slots:
    void handlerFontChanged(QFont font);

private:
    KiranApplication *q_ptr;
    bool m_adaptiveAppFontEnable = false;
    FontMonitor *m_appFontMonitor = nullptr;
};

#endif //KIRAN_APPLICATION_PRIVATE_H
