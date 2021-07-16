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
 
#include "draw-progress-bar-helper.h"
#include "draw-common-helper.h"
#include "style.h"
#include "widget-property-helper.h"

#include <QStyleOption>
#include <QDebug>
#include <QProgressBar>
#include <QPainter>
#include <private/qstyleanimation_p.h>

using namespace Kiran;

QSize DrawProgressBarHelper::progressBarSizeFromContents(const Style *style, const QStyleOption *opt,
                                                         const QSize &contentsSize, const QWidget *w,
                                                         StyleDetailFetcher *fetcher)
{
    // cast option
    const QStyleOptionProgressBar *progressBarOption(qstyleoption_cast<const QStyleOptionProgressBar *>(opt));
    if (!progressBarOption) return contentsSize;

    bool horizontal(progressBarOption->orientation == Qt::Horizontal);

    // make local copy
    QSize size(contentsSize);

    if (horizontal) {
        // check text visibility
        bool textVisible(progressBarOption->textVisible);

        size.setWidth(qMax(size.width(), int(Metrics::ProgressBar_Thickness)));
        size.setHeight(qMax(size.height(), int(Metrics::ProgressBar_Thickness)));
        if (textVisible) size.setHeight(qMax(size.height(), progressBarOption->fontMetrics.height()));
    } else {
        size.setHeight(qMax(size.height(), int(Metrics::ProgressBar_Thickness)));
        size.setWidth(qMax(size.width(), int(Metrics::ProgressBar_Thickness)));
    }

    return size;
}


QRect DrawProgressBarHelper::progressBarGrooveRect(const Style *style, const QStyleOption *option,
                                                   const QWidget *widget)
{
    auto progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar *>(option);
    // get flags and orientation
    bool textVisible(progressBarOption->textVisible);
    bool busy(progressBarOption->minimum == 0 && progressBarOption->maximum == 0);
    bool horizontal(progressBarOption->orientation == Qt::Horizontal);
    ProgressBarTextPosition textPosition = WidgetPropertyHelper::getProgressBarTextPosition(
            qobject_cast<const QProgressBar *>(widget));

    // copy rectangle and adjust
    QRect rect(option->rect);
    int frameWidth(style->pixelMetric(QStyle::PM_DefaultFrameWidth, option, widget));
    if (horizontal) rect = DrawCommonHelper::insideMargin(rect, frameWidth, 0);
    else rect = DrawCommonHelper::insideMargin(rect, 0, frameWidth);

    if (textVisible && !busy && horizontal) {
        QRect textRect(style->subElementRect(QStyle::SE_ProgressBarLabel, option, widget));
        textRect = style->visualRect(option->direction, option->rect, textRect);
        switch (textPosition) {
            case PROGRESS_TEXT_LEFT:
                rect.setLeft(textRect.right() + Metrics::ProgressBar_ItemSpacing + 1);
                break;
            case PROGRESS_TEXT_CENTER:
                break;
            case PROGRESS_TEXT_RIGHT:
                rect.setRight(textRect.left() - Metrics::ProgressBar_ItemSpacing - 1);
                break;
        }
        rect = QStyle::visualRect(option->direction, option->rect, rect);
        rect = DrawCommonHelper::centerRect(rect, rect.width(), Metrics::ProgressBar_Thickness);

    } else if (horizontal) {
        rect = DrawCommonHelper::centerRect(rect, rect.width(), Metrics::ProgressBar_Thickness);
    } else {
        rect = DrawCommonHelper::centerRect(rect, Metrics::ProgressBar_Thickness, rect.height());
    }

    return rect;
}

QRect DrawProgressBarHelper::progressBarContentsRect(const Style *style, const QStyleOption *option,
                                                     const QWidget *widget)
{
    const QStyleOptionProgressBar* progressBarOption( qstyleoption_cast<const QStyleOptionProgressBar*>( option ) );
    if( !progressBarOption ) return {};

    // get groove rect
    QRect rect( progressBarGrooveRect( style,option, widget ) );

    // in busy mode, grooveRect is used
    bool busy( progressBarOption->minimum == 0 && progressBarOption->maximum == 0 );
    if( busy ) return rect;

    // get orientation
    bool horizontal( progressBarOption->orientation == Qt::Horizontal );

    // check inverted appearance
    bool inverted( progressBarOption->invertedAppearance );

    // get progress and steps
    qreal progress( progressBarOption->progress - progressBarOption->minimum );
    int steps( qMax( progressBarOption->maximum  - progressBarOption->minimum, 1 ) );

    //Calculate width fraction
    qreal widthFrac = qMin( qreal(1), progress/steps );

    // convert the pixel width
    int indicatorSize( widthFrac*( horizontal ? rect.width():rect.height() ) );

    QRect indicatorRect;
    if( horizontal )
    {
        indicatorRect = QRect( inverted ? ( rect.right() - indicatorSize + 1):rect.left(), rect.y(), indicatorSize, rect.height() );
        indicatorRect = style->visualRect( option->direction, rect, indicatorRect );

    } else indicatorRect = QRect( rect.x(), inverted ? rect.top() : (rect.bottom() - indicatorSize + 1), rect.width(), indicatorSize );

    return indicatorRect;
}

QRect DrawProgressBarHelper::progressBarLabelRect(const Style *style, const QStyleOption *option,
                                                  const QWidget *widget)
{
    auto progressBarOption( qstyleoption_cast<const QStyleOptionProgressBar*>( option ) );
    if( !progressBarOption )
        return {};

    bool textVisible( progressBarOption->textVisible );
    bool busy( progressBarOption->minimum == 0 && progressBarOption->maximum == 0 );
    if( !textVisible || busy )
        return {};

    bool horizontal( progressBarOption->orientation == Qt::Horizontal );
    if( !horizontal )
        return {};

    int textWidth = qMax(
            option->fontMetrics.size( Qt::TextHideMnemonic, progressBarOption->text ).width(),
            option->fontMetrics.size( Qt::TextHideMnemonic, QString( "100%" ) ).width() );

    QRect rect( DrawCommonHelper::insideMargin( option->rect, Metrics::Frame_FrameWidth, 0 ) );
    rect.setWidth(textWidth);

    ProgressBarTextPosition textPosition = WidgetPropertyHelper::getProgressBarTextPosition(qobject_cast<const QProgressBar*>(widget));
    switch (textPosition) {
        case PROGRESS_TEXT_LEFT:
            rect.moveLeft(option->rect.left()+1);
            break;
        case PROGRESS_TEXT_CENTER:
            rect = DrawCommonHelper::centerRect(option->rect,rect.size());
            break;
        case PROGRESS_TEXT_RIGHT:
            rect.moveLeft( option->rect.right() - textWidth + 1 );
            break;
    }
    rect = QStyle::visualRect( option->direction,option->rect, rect );
    return rect;
}

bool DrawProgressBarHelper::drawProgressBarControl(const Style *style, const QStyleOption *opt, QPainter *p,
                                                   StyleDetailFetcher *fetcher, const QWidget *widget)
{
    const QStyleOptionProgressBar *progressBarOption(qstyleoption_cast<const QStyleOptionProgressBar *>(opt));
    if (!progressBarOption)
        return true;

    bool textVisible(progressBarOption->textVisible);
    bool busy(progressBarOption->minimum == 0 && progressBarOption->maximum == 0);

    // 凹槽
    QStyleOptionProgressBar tempOption = *progressBarOption;
    tempOption.rect = style->subElementRect(QStyle::SE_ProgressBarGroove, progressBarOption, widget);
    style->drawControl(QStyle::CE_ProgressBarGroove, &tempOption, p, widget);

    // 内容
    tempOption.rect = style->subElementRect(QStyle::SE_ProgressBarContents, progressBarOption, widget);
    style->drawControl(QStyle::CE_ProgressBarContents, &tempOption, p, widget);

    // 文本
    if (textVisible && !busy) {
        tempOption.rect = style->subElementRect(QStyle::SE_ProgressBarLabel, progressBarOption, widget);
        style->drawControl(QStyle::CE_ProgressBarLabel, &tempOption, p, widget);
    }
    return true;
}

bool DrawProgressBarHelper::drawProgressBarGrooveControl(const Style *style, const QStyleOption *opt,
                                                         QPainter *p, StyleDetailFetcher *fetcher,
                                                         const QWidget *widget)
{
    QColor grooveColor = fetcher->getColor(widget,opt,StyleDetailFetcher::ProgressBar_GrooveColor);
    DrawCommonHelper::renderProgressBarGroove(p,opt->rect,grooveColor,QColor());
    return true;
}

bool DrawProgressBarHelper::drawProgressBarContentsControl(const Style *style, const QStyleOption *option,
                                                           QPainter *p, StyleDetailFetcher *fetcher,
                                                           const QWidget *widget)
{

    auto progressBarOption( qstyleoption_cast<const QStyleOptionProgressBar*>( option ) );
    if( !progressBarOption ) return true;

    QRect rect( option->rect );
    const QPalette& palette( option->palette );

    bool horizontal = progressBarOption->orientation == Qt::Horizontal;
    bool inverted( progressBarOption->invertedAppearance  );
    bool reverse = horizontal && option->direction == Qt::RightToLeft;
    if( inverted ) reverse = !reverse;

    bool busy( ( progressBarOption->minimum == 0 && progressBarOption->maximum == 0 ) );

    QColor contentColor = fetcher->getColor(widget,option,StyleDetailFetcher::ProgressBar_ContentColor);

    //NOTE:为了适配5.9.7的QStyleAnimation为加入符号表的问题,暂时取消掉该部分功能
#if (QT_VERSION > QT_VERSION_CHECK(5,9,7))
    auto animation = qobject_cast<QProgressStyleAnimation*>(style->animation(option->styleObject));
    if( busy ) {
        if( !animation ){
            animation = new QProgressStyleAnimation(KIRAN_DEFAULT_ANIMATION_FPS,option->styleObject);
            style->startAnimation(animation);
        }
        int progressStep = animation->progressStep(100);
        DrawCommonHelper::renderProgressBarBusyContents( p, rect, contentColor,QColor(), horizontal, reverse, progressStep );
    }
    else
#endif
    {
#if (QT_VERSION > QT_VERSION_CHECK(5,9,7))
        if( animation ){
            animation->stop();
        }
#endif
        QRegion oldClipRegion( p->clipRegion() );
        if( horizontal ) {
            if( rect.width() < Metrics::ProgressBar_Thickness )
            {
                p->setClipRect( rect, Qt::IntersectClip );
                if( reverse ) rect.setLeft( rect.left() - Metrics::ProgressBar_Thickness + rect.width() );
                else rect.setWidth( Metrics::ProgressBar_Thickness );
            }
        } else {
            if( rect.height() < Metrics::ProgressBar_Thickness ) {
                p->setClipRect( rect, Qt::IntersectClip );
                if( reverse ) rect.setHeight( Metrics::ProgressBar_Thickness );
                else rect.setTop( rect.top() - Metrics::ProgressBar_Thickness + rect.height() );
            }
        }
        DrawCommonHelper::renderProgressBarGroove( p, rect, contentColor, QColor() );
        p->setClipRegion( oldClipRegion );
    }
    return true;
}

bool DrawProgressBarHelper::drawProgressBarLabelControl(const Style *style, const QStyleOption *option,
                                                        QPainter *p, StyleDetailFetcher *fetcher,
                                                        const QWidget *widget)
{
    auto progressBarOption( qstyleoption_cast<const QStyleOptionProgressBar*>( option ) );
    if( !progressBarOption )
        return true;

    bool horizontal = progressBarOption->orientation == Qt::Horizontal;
    if( !horizontal )
        return true;

    const QRect& rect( option->rect );
    const QPalette& palette( option->palette );

    const QStyle::State& state( option->state );
    bool enabled( state & QStyle::State_Enabled );

    Qt::Alignment hAlign( ( progressBarOption->textAlignment == Qt::AlignLeft ) ? Qt::AlignHCenter : progressBarOption->textAlignment );
    style->drawItemText( p, rect, Qt::AlignVCenter | hAlign, palette, enabled, progressBarOption->text, QPalette::WindowText );
    return true;
}