//
// Created by lxh on 2020/11/10.
//

#include "kiran-application-private.h"
#include "../font-monitor/font-monitor-factory.h"
#include "style.h"

#include <QDebug>

KiranApplicationPrivate::KiranApplicationPrivate(KiranApplication *ptr) {

}

KiranApplicationPrivate::~KiranApplicationPrivate() {
    delete m_appFontMonitor;
}

void KiranApplicationPrivate::init() {

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
