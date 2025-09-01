/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiran-widgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

static QTranslator* g_translator = nullptr;

// 在QCoreApplication构造期间调用的初始化函数
static void initKiranWidgetsTranslation()
{
    g_translator = new QTranslator();
    if ( g_translator->load(QLocale(), "kiranwidgets-qt5", ".",
                   "/usr/share/kiranwidgets-qt5/translations/", ".qm"))
    {
        QCoreApplication::installTranslator(g_translator);
    }
    else
    {
        qWarning("Failed to load translation for kiranwidgets-qt5");
        delete g_translator;
        g_translator = nullptr;
    }
}

// 使用qAddPreRoutine注册初始化函数
Q_COREAPP_STARTUP_FUNCTION(initKiranWidgetsTranslation)