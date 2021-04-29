//
// Created by lxh on 2020/12/29.
//

#include "kiran-style-helper.h"
#include <style.h>

using namespace Kiran;
void Kiran::StyleHelper::drawPrimitive(Kiran::KiranPrimitiveElement pe,
                                       const QStyleOption *opt, QPainter *p,
                                       const QWidget *w)
{
    if (!Style::isKiranStyle())
    {
        return;
    }
    auto kiranStyle = Style::castToKiranStyle();
    kiranStyle->drawPrimitive(pe, opt, p, w);
}

void StyleHelper::drawControl(KiranControlElement ce, const QStyleOption *opt,
                              QPainter *p, const QWidget *w)
{
    if (!Style::isKiranStyle())
    {
        return;
    }
    auto kiranStyle = Style::castToKiranStyle();
    kiranStyle->drawControl(ce, opt, p, w);
}

QRect StyleHelper::subElementRect(KiranSubElement se, const QStyleOption *opt,
                                  const QWidget *widget)
{
    if (!Style::isKiranStyle())
    {
        return QRect();
    }
    auto kiranStyle = Style::castToKiranStyle();
    return kiranStyle->subElementRect(se, opt, widget);
}

QSize StyleHelper::sizeFromContents(KiranContentsType   ct,
                                    const QStyleOption *opt,
                                    const QSize &       contentsSize,
                                    const QWidget *     widget)
{
    if (!Style::isKiranStyle())
    {
        return QSize();
    }
    auto kiranStyle = Style::castToKiranStyle();
    return kiranStyle->sizeFromContents(ct, opt, contentsSize, widget);
}
