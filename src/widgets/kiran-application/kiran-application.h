//
// Created by lxh on 2020/11/10.
//

#ifndef QAPPLICATIONDEMO_KIRAN_APPLICATION_H
#define QAPPLICATIONDEMO_KIRAN_APPLICATION_H

#include <QApplication>

///监控字体变化设置应用程序字体
///若有的控件不使用全局字体需突出或缩小,则得通过installEventFilter过滤ApplicationFontChange事件或重写event方法根据全局字体设置相应的字体

//TODO:监控全局主题的变化，加载全局主题，发送主题变化事件，应用程序接收后可在样式后追加特殊样式


/// 重新定义qApp宏，转换QCoreApplication全局单例为KiranApplication, 只在KiranApplication时有效
#if defined(qApp)
#undef qApp
#endif

class KiranApplication;
#define qApp (static_cast<KiranApplication*>(QCoreApplication::instance()))

class KiranApplicationPrivate;
class Q_DECL_EXPORT KiranApplication : public QApplication {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranApplication)
    Q_DISABLE_COPY(KiranApplication)
public:
    KiranApplication(int &argc, char **argv, int appFlags= ApplicationFlags);
    ~KiranApplication();

private:
    KiranApplicationPrivate *d_ptr;
};


#endif //KIRAN_APPLICATION_H
