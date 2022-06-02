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
#include "kiran-application-private.h"
#include "style.h"

#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>

KiranApplicationPrivate::KiranApplicationPrivate(KiranApplication *ptr) {

}

KiranApplicationPrivate::~KiranApplicationPrivate() {
}

void KiranApplicationPrivate::init() {
    setupTranslations();
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
