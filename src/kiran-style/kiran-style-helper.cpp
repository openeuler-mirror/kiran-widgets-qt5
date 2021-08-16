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
