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
