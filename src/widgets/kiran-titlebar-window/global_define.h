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
 
#ifndef GLOBAL_DEFINE_H
#define GLOBAL_DEFINE_H

#include <QObject>

#define SHADOW_BORDER_WIDTH 10
#define DEFAULT_THEME_PATH ":/kiranwidgets-qt5/themes/kiran-titlebar-window_black.qss"

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
