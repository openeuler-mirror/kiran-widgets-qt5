#ifndef XLIBHELPER_H
#define XLIBHELPER_H

#include <QX11Info>

#include "global_define.h"

namespace XLibHelper {
    bool sendWMMoveEvent(Display* display,quint64 xid,int x,int y);
    bool sendResizeEvent(Display* display,Kiran::CursorPositionEnums  postion,quint64 xid,int x,int y);
    int  SetShadowWidth(Display *xdisplay,quint64 xid,int left,int right,int top,int bottom);
}

#endif // XLIBHELPER_H
