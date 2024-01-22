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

#include "xlib-helper.h"

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <memory.h>
#include <unistd.h>
#include <QMap>

using namespace Kiran;

bool sendWMMoveResizeEvent(Display* display, EwmhMoveResizeDirection direction, quint64 xid, int x, int y)
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
    xEvent.xclient.data.l[4] = 1;

    XUngrabPointer(display, QX11Info::appTime());
    Status sendEvRes = XSendEvent(display, QX11Info::appRootWindow(QX11Info::appScreen()),
                                  False, SubstructureNotifyMask | SubstructureRedirectMask,
                                  &xEvent);
    XFlush(display);
    return sendEvRes;
}

bool XLibHelper::sendWMMoveEvent(Display* display, quint64 xid, int x, int y)
{
    return sendWMMoveResizeEvent(display, WM_MOVERESIZE_MOVE, xid, x, y);
}

bool XLibHelper::sendResizeEvent(Display* display,
                                 CursorPositionEnums postion,
                                 quint64 xid,
                                 int x, int y)
{
    EwmhMoveResizeDirection direction = WM_MOVERESIZE_CANCEL;
    switch (postion)
    {
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
    return sendWMMoveResizeEvent(display, direction, xid, x, y);
}

int XLibHelper::SetShadowWidth(Display* xdisplay,
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
                            (unsigned char*)frames,
                            4);
    XFlush(xdisplay);

    return s;
}

bool XLibHelper::cancelWMMove(Display* display, quint64 xid, int x, int y)
{
    return sendWMMoveResizeEvent(display, WM_MOVERESIZE_CANCEL, xid, x, y);
}

void reloadNetSupportedAtoms(Display* xdisplay, QMap<QString, Atom>& atomsMap)
{
    atomsMap.clear();

    // get _NET_SUPPORTED atom
    Atom netSupportedAtom = XInternAtom(xdisplay, "_NET_SUPPORTED", 1);
    if (netSupportedAtom == None)
    {
        return;
    }

    // get _NET_SUPPORTED atom value from root window
    Window rootWindow = QX11Info::appRootWindow(QX11Info::appScreen());
    Atom type;
    int format;
    unsigned long after;
    unsigned long natoms;
    Atom* atoms;
    XGetWindowProperty(xdisplay, rootWindow, netSupportedAtom, 0, LONG_MAX, False, XA_ATOM, &type, &format, &natoms, &after, (unsigned char**)&atoms);
    if (type != XA_ATOM || atoms == nullptr)
    {
        return;
    }

    // cache root window _NET_SUPPORTED property
    for (int i = 0; i < natoms; i++)
    {
        char* atomName = XGetAtomName(xdisplay, atoms[i]);
        atomsMap.insert(atomName, atoms[i]);

        XFree(atomName);
    }

    XFree(atoms);
}

bool checkNetWmHintSupported(Display* xdisplay, const char* atomName)
{
    static QMap<QString, Atom> supportedAtomMap;

    if (supportedAtomMap.isEmpty())
    {
        reloadNetSupportedAtoms(xdisplay, supportedAtomMap);
    }

    if (supportedAtomMap.contains(atomName))
    {
        return true;
    }

    return false;
}

// _GTK_SHOW_WINDOW_MENU支持情况
// marco >= 1.20支持
// kwin >= 5.26支持
#define ATOM_WINDOW_SHOW_WINDOW_MENU "_GTK_SHOW_WINDOW_MENU"
bool XLibHelper::showWindowMenuRequest(Display* xdisplay, quint64 xid, int root_x, int root_y)
{
    if (!checkNetWmHintSupported(xdisplay, ATOM_WINDOW_SHOW_WINDOW_MENU))
    {
        return false;
    }

    Atom showWindowMenuAtom = XInternAtom(xdisplay, ATOM_WINDOW_SHOW_WINDOW_MENU, 1);

    XEvent xEvent;
    memset(&xEvent, 0, sizeof(XEvent));
    xEvent.xclient.type = ClientMessage;
    xEvent.xclient.message_type = showWindowMenuAtom;
    xEvent.xclient.display = xdisplay;
    xEvent.xclient.window = xid;
    xEvent.xclient.format = 32;
    xEvent.xclient.data.l[0] = 0;         /*GTK device ID(unused)*/
    xEvent.xclient.data.l[1] = root_x;    /* X coordinate relative to root */
    xEvent.xclient.data.l[2] = root_y; /* Y coordinate relative to root */

    XSendEvent(xdisplay, QX11Info::appRootWindow(QX11Info::appScreen()),
               False, SubstructureNotifyMask | SubstructureRedirectMask,
               &xEvent);
    XFlush(xdisplay);
    return true;
}