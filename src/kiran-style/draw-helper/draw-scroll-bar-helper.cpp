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
 
#include "draw-scroll-bar-helper.h"
#include "style.h"

#include <QScrollBar>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>

bool
Kiran::DrawScrollBarHelper::drawScrollBarComplexControl(const Kiran::Style *style, const QStyleOptionComplex *option,
                                                        Kiran::StyleDetailFetcher *fetcher, QPainter *painter,
                                                        const QWidget *widget)
{
    const QStyleOptionSlider * scrollbarOption = qstyleoption_cast<const QStyleOptionSlider *>(option);
    if( !scrollbarOption ){
        return true;
    }

    if( scrollbarOption->subControls & QStyle::SC_ScrollBarSlider ){
        QStyleOptionSlider sliderOption = *scrollbarOption;
        sliderOption.state = scrollbarOption->state;
        sliderOption.rect = style->subControlRect(QStyle::CC_ScrollBar,&sliderOption,QStyle::SC_ScrollBarSlider,widget);
        if( sliderOption.rect.isValid() ){
            style->drawControl(QStyle::CE_ScrollBarSlider,&sliderOption,painter,widget);
        }
    }

    return true;
}

bool
Kiran::DrawScrollBarHelper::drawScrollBarAddLineControl(const Kiran::Style *style, const QStyleOption *opt,
                                                        QPainter *p,Kiran::StyleDetailFetcher *fetcher,
                                                        const QWidget *widget)
{
    return false;
}

bool
Kiran::DrawScrollBarHelper::drawScrollBarSubLineControl(const Kiran::Style *style, const QStyleOption *opt, QPainter *p,
                                                        Kiran::StyleDetailFetcher *fetcher, const QWidget *widget)
{
    return false;
}

bool
Kiran::DrawScrollBarHelper::drawScrollBarAddPageControl(const Kiran::Style *style, const QStyleOption *opt, QPainter *p,
                                                        Kiran::StyleDetailFetcher *fetcher, const QWidget *widget)
{
    return false;
}

bool
Kiran::DrawScrollBarHelper::drawScrollBarSubPageControl(const Kiran::Style *style, const QStyleOption *opt, QPainter *p,
                                                        Kiran::StyleDetailFetcher *fetcher, const QWidget *widget)
{
    return false;
}

bool
Kiran::DrawScrollBarHelper::drawScrollBarSliderControl(const Kiran::Style *style, const QStyleOption *opt, QPainter *p,
                                                       Kiran::StyleDetailFetcher *fetcher, const QWidget *widget)
{
    // cast option and check
    const QStyleOptionSlider *sliderOption( qstyleoption_cast<const QStyleOptionSlider*>( opt ) );
    if( !sliderOption ) return true;

    const QStyle::State& state( opt->state );
    bool enabled( state & QStyle::State_Enabled );
    bool mouseOver( (state & QStyle::State_Active) && enabled && ( state & QStyle::State_MouseOver ) );
    bool handleActive( sliderOption->activeSubControls & QStyle::SC_ScrollBarSlider );

    int pseudoClass = QCss::PseudoClass_Unspecified;
    if( handleActive ){
        pseudoClass = QCss::PseudoClass_Hover;
    }

    if( !enabled ){
        pseudoClass = QCss::PseudoClass_Disabled;
    }

    QColor brushColor = fetcher->getColor(StyleDetailFetcher::ScrollBarSlider_Background,pseudoClass);

    if(brushColor.isValid()){
        p->setRenderHint( QPainter::Antialiasing, true );
        p->setPen(Qt::NoPen);
        p->setBrush(brushColor);
        p->drawRect(opt->rect);
    }

    return true;
}

QRect Kiran::DrawScrollBarHelper::scrollBarSubControlRect(const Kiran::Style *style, const QStyleOptionComplex *opt,
                                                          QStyle::SubControl subControl, const QWidget *w)
{
    const QStyleOptionSlider* sliderOption( qstyleoption_cast<const QStyleOptionSlider*>( opt ) );
    if( !sliderOption ) return QRect();

    bool horizontal( opt->state & QStyle::State_Horizontal );

    switch (subControl) {
        case QStyle::SC_ScrollBarAddLine:return QRect();
        case QStyle::SC_ScrollBarSubLine:return QRect();
        case QStyle::SC_ScrollBarAddPage:return QRect();
        case QStyle::SC_ScrollBarSubPage:return QRect();
        case QStyle::SC_ScrollBarGroove:
        {
            return opt->rect.adjusted(1,1,-1,-1);
        }
        case QStyle::SC_ScrollBarSlider:
        {
            QRect grooveRect = style->subControlRect(QStyle::CC_ScrollBar,opt,QStyle::SC_ScrollBarGroove,w);
            grooveRect.adjust(0, 0, 1, 1);

            if( sliderOption->minimum == sliderOption->maximum ) return grooveRect;

            int space( horizontal? grooveRect.width(): grooveRect.height());
            int sliderSize = space * qreal( sliderOption->pageStep ) / ( sliderOption->maximum - sliderOption->minimum + sliderOption->pageStep );
            sliderSize = qMax( sliderSize, static_cast<int>(Metrics::ScrollBar_MinSliderHeight ) );
            sliderSize = qMin( sliderSize, space );

            // 去掉滑块大小，滑动槽所留的用于显示进度的空间
            space -= sliderSize;
            if( space <= 0 ) return grooveRect;

            // 计算滑块位置
            int pos = qRound( qreal( sliderOption->sliderPosition - sliderOption->minimum ) / ( sliderOption->maximum - sliderOption->minimum )*space );
            if( sliderOption->upsideDown ) pos = space - pos;

            // 滑块位于滑块槽水平中心(垂直滑动条)或滑块槽垂直中心(水平滑动条)
            QRect sliderRect;
            if( horizontal ){
                sliderRect = QRect(grooveRect.left()+pos,
                                     grooveRect.top()+(grooveRect.height()-Metrics::ScrollBar_SliderWidth)/2,
                                     sliderSize,
                                     Metrics::ScrollBar_SliderWidth);
            }else{
                sliderRect = QRect(grooveRect.left()+(grooveRect.width()-Metrics::ScrollBar_SliderWidth)/2,
                                   grooveRect.top()+pos,
                                   Metrics::ScrollBar_SliderWidth,
                                   sliderSize);
            }

            return QStyle::visualRect(opt->direction,opt->rect,sliderRect);
        }
        default:return QRect();
    }
}

QStyle::SubControl Kiran::DrawScrollBarHelper::hitTestScrollBarComplexControl(const Kiran::Style *style, const QStyleOptionComplex *opt,
                                                           const QPoint &pt, const QWidget *w)
{
    bool horizontal = (opt->state & QStyle::State_Horizontal);

    QRect grooveRect = style->subControlRect( QStyle::CC_ScrollBar, opt,
                                              QStyle::SC_ScrollBarGroove, w );
    // 按压在滑块槽中
    if( grooveRect.contains( pt ) )
    {
        // 判断是不是按压在滑块上
        QRect sliderRect = style->subControlRect( QStyle::CC_ScrollBar, opt, QStyle::SC_ScrollBarSlider, w );
        // NOTE:此处不能直接计算滑块矩形包含点击点，例如点击到水平滑动条滑块的上下两侧应该也算点击到滑块
        //if( sliderRect.contains( pt ) )
        //    return QStyle::SC_ScrollBarSlider;
        if( (horizontal  && pt.x()>=sliderRect.left() && pt.x()<=sliderRect.right()) ||
                (!horizontal && pt.y()>=sliderRect.top() && pt.y()<=sliderRect.bottom()) ){
            return QStyle::SC_ScrollBarSlider;
        }

        QStyle::SubControl retSubControl = QStyle::SC_None;

        // 通过判断是否是垂直或水平滑动条和从左右边布局，判断返回上下页
        if( horizontal ){
            if( opt->direction == Qt::LeftToRight ){
                retSubControl = pt.x()<sliderRect.x()?QStyle::SC_ScrollBarSubPage:QStyle::SC_ScrollBarAddPage;
            }else{
                retSubControl = pt.x()<sliderRect.x()?QStyle::SC_ScrollBarAddPage:QStyle::SC_ScrollBarSubPage;
            }
        }else{
            retSubControl = pt.y()<sliderRect.bottom()?QStyle::SC_ScrollBarAddPage:QStyle::SC_ScrollBarSubPage;
        }

        return retSubControl;
    }
    return QStyle::SC_None;
}

bool Kiran::DrawScrollBarHelper::drawScrollAreaCornerPrimitive(const Kiran::Style *style, const QStyleOption *option,
                                                               QPainter *painter, Kiran::StyleDetailFetcher *fetcher,
                                                               const QWidget *w)
{
    //NOTE:不绘制滚动区域垂直水平滚动条相交的区域角落
    return true;
}
