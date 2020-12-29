/*
 * @file   draw-frame-helper.h
 * @brief  绘制QFrame和其派生类的相关方法
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANSTYLE_DRAW_FRAME_HELPER_H
#define KIRANSTYLE_DRAW_FRAME_HELPER_H

#include <QStyle>
#include <QStyleOption>

#include "style-detail-fetcher.h"

namespace Kiran{
    class Style;
    namespace DrawFrameHelper {
        bool drawFramePrimitive(const Style* style ,const QStyleOption* opt,QPainter* painter,StyleDetailFetcher* detaulFetcher,const QWidget* widget);
    };
}

#endif //KIRANSTYLE_DRAW_FRAME_HELPER_H
