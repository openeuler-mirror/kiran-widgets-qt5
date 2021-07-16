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
