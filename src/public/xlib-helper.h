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

#ifndef XLIBHELPER_H
#define XLIBHELPER_H

#include <QX11Info>

#include "../widgets/kiran-titlebar-window/global_define.h"

namespace XLibHelper {
    bool cancelWMMove(Display* display,quint64 xid,int x, int y);
    bool sendWMMoveEvent(Display* display,quint64 xid,int x,int y);
    bool sendResizeEvent(Display* display,Kiran::CursorPositionEnums  postion,quint64 xid,int x,int y);
    int  SetShadowWidth(Display *xdisplay,quint64 xid,int left,int right,int top,int bottom);
}

#endif // XLIBHELPER_H
