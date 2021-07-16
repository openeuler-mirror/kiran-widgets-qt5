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
 
#include "draw-search-box-helper.h"
#include "style.h"
#include "style-detail-fetcher.h"
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
