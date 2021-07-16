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
 
#include "draw-image-selector-helper.h"
#include "style.h"
#include "style-detail-fetcher.h"
#include "draw-common-helper.h"

#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QDebug>

void Kiran::DrawImageSelectorHelper::drawPEKiranImageSelector(const Kiran::Style *style, const QStyleOption *opt,
                                                              QPainter *p, Kiran::StyleDetailFetcher *fetcher,
                                                              const QWidget *widget) {
    QRect rect(opt->rect);
    int radius = style->pixelMetric(Kiran::PM_KiranImageSelectorRadius);
    QColor color = fetcher->getColor(widget,opt,StyleDetailFetcher::KiranImageSelector_BorderColor);
    DrawCommonHelper::drawFrame(p,rect,radius,1,QColor("#191919"),color);
}

void
Kiran::DrawImageSelectorHelper::drawPEKiranImageSelectorButtonFrame(const Kiran::Style *style, const QStyleOption *opt,
                                                                    QPainter *p, Kiran::StyleDetailFetcher *fetcher,
                                                                    const QWidget *widget) {
    p->setRenderHint(QPainter::Antialiasing,true);

    QRect rect(opt->rect);
    int radius = style->pixelMetric(Kiran::PM_KiranImageSelectorRadius);
    QColor color = fetcher->getColor(widget,opt,StyleDetailFetcher::KiranImageSelector_ButtonColor);
    bool isAnchorLeft = (widget->mapToParent(QPoint(0,0)).x() == 0);
    QPainterPath painterPath = DrawCommonHelper::getRoundedRectanglePath(rect.adjusted(1,1,-1,-1),
                                              isAnchorLeft?radius:0,
                                              isAnchorLeft?0:radius,
                                              isAnchorLeft?radius:0,
                                              isAnchorLeft?0:radius);
    p->setBrush(color);
    p->setPen(Qt::NoPen);
    p->drawPath(painterPath);
}

void Kiran::DrawImageSelectorHelper::drawPEKiranImageSelectorPrevButtonArrow(const Kiran::Style *style,
                                                                             const QStyleOption *opt, QPainter *p,
                                                                             Kiran::StyleDetailFetcher *fetcher,
                                                                             const QWidget *widget) {
    DrawCommonHelper::drawArrow(fetcher,p,opt,widget,ArrowLeft,14);
}

void Kiran::DrawImageSelectorHelper::drawPEKiranImageSelectorNextButtonArrow(const Kiran::Style *style,
                                                                             const QStyleOption *opt, QPainter *p,
                                                                             Kiran::StyleDetailFetcher *fetcher,
                                                                             const QWidget *widget) {
    DrawCommonHelper::drawArrow(fetcher,p,opt,widget,ArrowRight,14);
}
