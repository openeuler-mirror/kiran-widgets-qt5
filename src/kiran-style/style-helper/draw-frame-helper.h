//
// Created by lxh on 2020/11/27.
//

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
