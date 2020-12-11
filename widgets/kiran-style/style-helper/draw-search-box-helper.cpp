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

bool DrawSearchBoxHelper::drawSearchBoxIndicatorPrimitive(const Style *style,
                                                          const QStyleOption *opt,
                                                          QPainter *p,
                                                          StyleDetailFetcher *fetcher,
                                                          const QWidget *widget)
{
    bool enabled(opt->state & QStyle::State_Enabled);

    QRect rect(opt->rect);
    rect.moveLeft(Metrics::LineEdit_FrameWidth/2);
    rect.setWidth(opt->rect.height());
    QString searchIcon = fetcher->getUrl(StyleDetailFetcher::SearchBox_Icon,
                                         enabled?QCss::PseudoClass_Unspecified:QCss::PseudoClass_Disabled);
    QSvgRenderer renderer(searchIcon);

    p->setRenderHint(QPainter::Antialiasing,true);

    renderer.render(p,rect.adjusted(12,12,-12,-12));

    return true;
}
