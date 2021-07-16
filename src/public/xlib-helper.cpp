 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */
 
#include "xlib-helper.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <unistd.h>
#include <memory.h>

using namespace Kiran;

bool sendWMMoveResizeEvent(Display* display,EwmhMoveResizeDirection direction,quint64 xid,int x,int y)
{
    Atom netMoveResize = XInternAtom(display, "_NET_WM_MOVERESIZE", False);
    XEvent xEvent;

    memset(&xEvent, 0, sizeof(XEvent));
    xEvent.xclient.type = ClientMessage;
    xEvent.xclient.message_type = netMoveResize;
    xEvent.xclient.display = display;
    xEvent.xclient.window = xid;
    xEvent.xclient.format = 32;
    xEvent.xclient.data.l[0] = x;
    xEvent.xclient.data.l[1] = y;
    xEvent.xclient.data.l[2] = direction;
    xEvent.xclient.data.l[3] = Button1;
    xEvent.xclient.data.l[4] = 0;

    XUngrabPointer(display, QX11Info::appTime());
    Status sendEvRes = XSendEvent(display, QX11Info::appRootWindow(QX11Info::appScreen()),
                                  False, SubstructureNotifyMask | SubstructureRedirectMask,
                                  &xEvent);
    XFlush(display);
    return sendEvRes;
}

bool XLibHelper::sendWMMoveEvent(Display *display, quint64 xid, int x, int y)
{
    return sendWMMoveResizeEvent(display,WM_MOVERESIZE_MOVE,xid,x,y);
}

bool XLibHelper::sendResizeEvent(Display *display,
                                 CursorPositionEnums postion,
                                 quint64 xid,
                                 int x, int y)
{
    EwmhMoveResizeDirection direction = WM_MOVERESIZE_CANCEL;
    switch (postion) {
    case CursorPosition_LeftTop:
        direction = WM_MOVERESIZE_SIZE_TOPLEFT;
        break;
    case CursorPosition_RightTop:
        direction = WM_MOVERESIZE_SIZE_TOPRIGHT;
        break;
    case CursorPosition_LeftBottom:
        direction = WM_MOVERESIZE_SIZE_BOTTOMLEFT;
        break;
    case CursorPosition_RightBottom:
        direction = WM_MOVERESIZE_SIZE_BOTTOMRIGHT;
        break;
    case CursorPosition_Top:
        direction = WM_MOVERESIZE_SIZE_TOP;
        break;
    case CursorPosition_Bottom:
        direction = WM_MOVERESIZE_SIZE_BOTTOM;
        break;
    case CursorPosition_Left:
        direction = WM_MOVERESIZE_SIZE_LEFT;
        break;
    case CursorPosition_Right:
        direction = WM_MOVERESIZE_SIZE_RIGHT;
        break;
    }
    return sendWMMoveResizeEvent(display,direction,xid,x,y);
}

int XLibHelper::SetShadowWidth(Display *xdisplay,
                               quint64 xid,
                               int left,
                               int right,
                               int top,
                               int bottom)
{
    Atom atom;
    long frames[4];

    atom = XInternAtom(xdisplay, "_GTK_FRAME_EXTENTS", 0);

    frames[0] = left;
    frames[1] = right;
    frames[2] = top;
    frames[3] = bottom;
    int s = XChangeProperty(xdisplay,
                               xid,
                               atom,
                               XA_CARDINAL,
                               32,
                               PropModeReplace,
                               (unsigned char *)frames,
                               4);
    XFlush(xdisplay);

    return s;
}

bool XLibHelper::cancelWMMove(Display* display,quint64 xid,int x, int y)
{
    return sendWMMoveResizeEvent(display,WM_MOVERESIZE_CANCEL,xid,x,y);
}