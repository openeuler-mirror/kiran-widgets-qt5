//
// Created by lxh on 2020/11/27.
//

#ifndef KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H
#define KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H

#include <QRect>

class QStyle;
class QStyleOption;
class QPainter;
class QWidget;
class QStyleOptionFrame;
namespace Kiran{
    class Style;
    class StyleDetailFetcher;
    namespace DrawLineEditHelper {
        QSize lineEditSizeFromContents(const Style* style,const QStyleOption *option,
                                       const QSize &contentsSize, const QWidget *widget);
        QRect lineEditContentsRect(const Style* style,const QStyleOption* opt,const QWidget* widget);
        bool drawFrameLineEditPrimitive(const Style* style ,const QStyleOption* opt,QPainter* painter,
                                        StyleDetailFetcher* detaulFetcher,const QWidget* widget);
    };
}

#endif //KIRANSTYLE_DRAW_LINE_EDIT_HELPER_H
