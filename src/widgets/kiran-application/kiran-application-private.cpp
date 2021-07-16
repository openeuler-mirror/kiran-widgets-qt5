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
 
#include "kiran-application-private.h"
#include "../font-monitor/font-monitor-factory.h"
#include "style.h"

#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>

KiranApplicationPrivate::KiranApplicationPrivate(KiranApplication *ptr) {

}

KiranApplicationPrivate::~KiranApplicationPrivate() {
    delete m_appFontMonitor;
}

void KiranApplicationPrivate::init() {
    setupTranslations();
}

void KiranApplicationPrivate::updateAppFont() {
    if( m_appFontMonitor!= nullptr ){
        QApplication::setFont(m_appFontMonitor->currentFont(),"QObject");
    }
}

void KiranApplicationPrivate::setAdaptiveAppFont(bool enable) {
    if( enable == m_adaptiveAppFontEnable ){
        return;
    }
    if( enable ){
        m_appFontMonitor = FontMonitorFactory::createAppFontMonitor();
        connect(m_appFontMonitor,&FontMonitor::fontChanged,
                this,&KiranApplicationPrivate::handlerFontChanged);
        updateAppFont();
    }else{
        disconnect(m_appFontMonitor,&FontMonitor::fontChanged,
                this,&KiranApplicationPrivate::handlerFontChanged);
        delete m_appFontMonitor;
    }
    m_adaptiveAppFontEnable = enable;
}

bool KiranApplicationPrivate::adaptiveAppFont() {
    return m_adaptiveAppFontEnable;
}

void KiranApplicationPrivate::handlerFontChanged(QFont font) {
    Q_UNUSED(font)
    auto fm = qobject_cast<FontMonitor*>(sender());
    if( fm == m_appFontMonitor ){
        updateAppFont();
    }
}

void KiranApplicationPrivate::initKiranStyle()
{
    qApp->setStyle(new Kiran::Style(Kiran::KIRAN_BLACK));
}

void KiranApplicationPrivate::setupTranslations()
{
    QTranslator* translator = new QTranslator(this);
    if(translator->load("qt_"+QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        QCoreApplication::installTranslator(translator);
    }
    else
    {
        delete translator;
    }
}
