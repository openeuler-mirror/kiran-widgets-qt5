//
// Created by lxh on 2021/1/26.
//

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
