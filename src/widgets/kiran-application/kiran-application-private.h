//
// Created by lxh on 2020/11/10.
//

#ifndef QAPPLICATIONDEMO_KIRAN_APPLICATION_PRIVATE_H
#define QAPPLICATIONDEMO_KIRAN_APPLICATION_PRIVATE_H

#include "kiran-application.h"

#include <QObject>

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
