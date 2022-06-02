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
 
#include "widget.h"

#include "kiran-application.h"
#include "kiran-single-application.h"

int main(int argc, char *argv[])
{
    KiranSingleApplication a(argc, argv);
    /**
     *         AA_UseDesktopOpenGL = 15,
        AA_UseOpenGLES = 16,
        AA_UseSoftwareOpenGL = 17,
     */
    Widget w;
    w.show();

    return KiranApplication::exec();
}
