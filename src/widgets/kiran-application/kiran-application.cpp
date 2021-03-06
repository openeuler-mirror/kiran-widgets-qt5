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
 
#include "kiran-application.h"
#include "kiran-application-private.h"

KiranApplication::KiranApplication(int &argc, char **argv, int appFlags)
    : QApplication(argc,argv,appFlags),d_ptr(new KiranApplicationPrivate(this)){
    d_ptr->init();
    d_ptr->setAdaptiveAppFont(true);
    d_ptr->initKiranStyle();
};

KiranApplication::~KiranApplication(){
    delete d_ptr;
}