//
// Created by lxh on 2020/12/9.
//

#include "draw-search-box-helper.h"
#include "style.h"
#include "style-data/style-detail-fetcher.h"
#include "draw-common-helper.h"

#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QSvgRenderer>

using namespace Kiran;

bool DrawSearchBoxHelper::drawSearchBoxFramePrimitive(const Style *style,
                                                      const QStyleOption *opt,
                                                      QPainter *p,
                                                      StyleDetailFetcher *fetcher,
                                                      const QWidget *widget)
{
    const QStyle::State & state = opt->state;

    QColor backgroundColor = fetcher->getColor(widget,opt,StyleDetailFetcher::SearchBox_Background);
    QColor borderColor = fetcher->getColor(widget,opt,StyleDetailFetcher::SearchBox_BorderColor);
    int radius = fetcher->getInt(widget,opt,StyleDetailFetcher::SearchBox_BorderRadius);
    int borderWidth = fetcher->getInt(widget,opt,StyleDetailFetcher::SearchBox_BorderWidth);

    DrawCommonHelper::drawFrame(p,opt->rect,radius,borderWidth,backgroundColor,borderColor);
    return true;
}

bool DrawSearchBoxHelper::drawSearchBoxIndicatorPrimitive(const Style *style,
                                                          const QStyleOption *opt,
                                                          QPainter *p,
                                                          StyleDetailFetcher *fetcher,
                                                          const QWidget *widget)
{
    bool enabled(opt->state & QStyle::State_Enabled);

    QRect rect(opt->rect);
    rect.moveLeft(Metrics::LineEdit_FrameWidth/2);
    QString searchIcon = fetcher->getUrl(StyleDetailFetcher::SearchBox_Icon,
                                         enabled?QCss::PseudoClass_Unspecified:QCss::PseudoClass_Disabled);
    QSvgRenderer renderer(searchIcon);

    p->setRenderHint(QPainter::Antialiasing,true);

    renderer.render(p,rect.adjusted(12,12,-12,-12));

    return true;
}
