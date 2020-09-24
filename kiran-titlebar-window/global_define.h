#ifndef GLOBAL_DEFINE_H
#define GLOBAL_DEFINE_H

#include <QObject>

#define SHADOW_BORDER_WIDTH 10

namespace Kiran {

    enum CursorPositionEnum{
        CursorPosition_None        = 0x00000000,
        CursorPosition_Top         = 0x00000001,
        CursorPosition_Bottom      = 0x00000010,
        CursorPosition_Left        = 0x00000100,
        CursorPosition_Right       = 0x00001000,
        CursorPosition_LeftTop     = CursorPosition_Left|CursorPosition_Top,
        CursorPosition_RightTop    = CursorPosition_Right|CursorPosition_Top,
        CursorPosition_LeftBottom  = CursorPosition_Left|CursorPosition_Bottom,
        CursorPosition_RightBottom = CursorPosition_Right|CursorPosition_Bottom
    };
    Q_FLAGS(CursorPositionEnums)
    Q_DECLARE_FLAGS(CursorPositionEnums, CursorPositionEnum)
    Q_DECLARE_OPERATORS_FOR_FLAGS(Kiran::CursorPositionEnums)

    /*copy from xcb/xcb_ewmh.h*/
    enum EwmhMoveResizeDirection{
        /** Resizing applied on the top left edge */
        WM_MOVERESIZE_SIZE_TOPLEFT = 0,
        /** Resizing applied on the top edge */
        WM_MOVERESIZE_SIZE_TOP = 1,
        /** Resizing applied on the top right edge */
        WM_MOVERESIZE_SIZE_TOPRIGHT = 2,
        /** Resizing applied on the right edge */
        WM_MOVERESIZE_SIZE_RIGHT = 3,
        /** Resizing applied on the bottom right edge */
        WM_MOVERESIZE_SIZE_BOTTOMRIGHT = 4,
        /** Resizing applied on the bottom edge */
        WM_MOVERESIZE_SIZE_BOTTOM = 5,
        /** Resizing applied on the bottom left edge */
        WM_MOVERESIZE_SIZE_BOTTOMLEFT = 6,
        /** Resizing applied on the left edge */
        WM_MOVERESIZE_SIZE_LEFT = 7,
        /* Movement only */
        WM_MOVERESIZE_MOVE = 8,
        /* Size via keyboard */
        WM_MOVERESIZE_SIZE_KEYBOARD = 9,
        /* Move via keyboard */
        WM_MOVERESIZE_MOVE_KEYBOARD = 10,
        /* Cancel operation */
        WM_MOVERESIZE_CANCEL = 11
    };

}

#endif // GLOBAL_DEFINE_H
