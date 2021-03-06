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
 
#ifndef QAPPLICATIONDEMO_KIRAN_APPLICATION_H
#define QAPPLICATIONDEMO_KIRAN_APPLICATION_H

#include <QApplication>

/* 重新定义qApp宏，转换QCoreApplication全局单例为KiranApplication, 只在KiranApplication时有效 */
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<KiranApplication*>(QCoreApplication::instance()))

class KiranApplication;
class KiranApplicationPrivate;

/**
 * @brief Kiran对于QApplication的一层封装
 *
 *    实现了以下功能
 *  - 监控字体变化，字体变化时设置应用程序字体,如果有的控件不使用全局字体(需突出显示或者比较小)，
 *    需要通过installEventFilter过滤ApplicationFontChange事件或重写event方法根据全局字体设置相应的字体
 *  - 设置QStyle为KiranStyle,KiranStyle为大部分控件提供了定制,让界面统一
 *
 * 使用说明
 *
 * 　安装 **kiranwidgets-qt5-examples**,详情见/usr/share/kiranwidgets-qt5/examples/kiran-application/
 *
 *  @since 2.1.0
 *  @see QApplication
 *  @todo 监听桌面环境主题变更，主题变化切换Style
 */
class Q_DECL_EXPORT KiranApplication : public QApplication {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranApplication)
    Q_DISABLE_COPY(KiranApplication)
public:
    /**
     * @brief KiranApplication构造方法
     * @param argc     同QApplication::QApplication(int &, char **)中argc
     * @param argv     同QApplication::QApplication(int &, char **)中argv
     * @param appFlags 同QApplication::QApplication(int &, char **)中appFlags
     * @see QApplication::QApplication(int &, char **)
     */
    KiranApplication(int &argc, char **argv, int appFlags= ApplicationFlags);

    /**
     * @brief KiranApplication析构方法
     */
    ~KiranApplication();


private:
    /* KiranApplicationPrivate私有类指针 */
    KiranApplicationPrivate *d_ptr;
};


#endif //KIRAN_APPLICATION_H
