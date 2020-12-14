//
// Created by lxh on 2020/11/27.
//

#include "draw-common-helper.h"
#include "draw-spinbox-helper.h"
#include "style.h"
#include "style-property-helper.h"

#include <QStyleOption>
#include <QPainter>
#include <QWidget>

using namespace Kiran;

void drawSpinboxArrow(const Style* style,QStyle::SubControl subControl,
                      const QStyleOptionSpinBox *option,StyleDetailFetcher* fetcher, QPainter *painter,
                      const QWidget *widget, const QRect &spinboxRect)
{
    painter->setRenderHint(QPainter::Antialiasing);
    bool hasFocus = (option->state & QStyle::State_HasFocus);
    bool enabled = (option->state & QStyle::State_Enabled);
    bool mouseHover = (option->state & QStyle::State_Active) && enabled && (option->state & QStyle::State_MouseOver);

    bool subControlHover = (mouseHover && (option->activeSubControls & subControl));
    bool subControlSunken = (option->state & QStyle::State_Sunken) && enabled && (option->activeSubControls & subControl);

    QRect arrowRect = style->subControlRect(QStyle::CC_SpinBox, option, subControl, widget);

    quint64 pseudoStatus = 0;
    if (!enabled) {
        pseudoStatus = QCss::PseudoClass_Disabled;
    } else {
        pseudoStatus |= QCss::PseudoClass_Unspecified;
        if (subControlSunken) {
            pseudoStatus |= QCss::PseudoClass_Pressed;
        } else if (subControlHover) {
            pseudoStatus |= QCss::PseudoClass_Hover;
        }
    }

    QColor signColor, bgColor;
    signColor = fetcher->getColor(StyleDetailFetcher::Spinbox_ArrowSignColor, pseudoStatus);
    bgColor = fetcher->getColor(StyleDetailFetcher::Spinbox_ArrowBackground, pseudoStatus);
    int radius = fetcher->getInt(StyleDetailFetcher::Frame_Radius, pseudoStatus);

    DrawCommonHelper::drawSpinboxArrow(painter, arrowRect, spinboxRect, radius,
                                       bgColor, signColor, subControl == QStyle::SC_SpinBoxUp);
}

bool DrawSpinboxHelper::drawSpinBoxCompleControl(const Style *style,
                                                        const QStyleOptionComplex *opt,
                                                        StyleDetailFetcher *fetcher,
                                                        QPainter *painter, const QWidget *widget)
{
    const auto spinBoxOption = qstyleoption_cast<const QStyleOptionSpinBox *>(opt);
    if (!spinBoxOption) {
        return true;
    }
    painter->setRenderHint(QPainter::Antialiasing);

    const QRect rect = spinBoxOption->rect;
    const QPalette &palette(opt->palette);

    /// frame
    if (opt->subControls & QStyle::SC_SpinBoxFrame) {
        bool flat = !spinBoxOption->frame;
        if (flat) {
            QColor background(palette.color(QPalette::Base));
            painter->setBrush(background);
            painter->setPen(Qt::NoPen);
            painter->drawRect(rect);
        } else {
            style->drawPrimitive(QStyle::PE_FrameLineEdit, opt, painter, widget);
        }
    }


    /// plus、minus
    if ((opt->subControls & QStyle::SC_SpinBoxUp)) {
        drawSpinboxArrow(style,QStyle::SC_SpinBoxUp, spinBoxOption,fetcher, painter, widget, rect);
    }

    if (opt->subControls & QStyle::SC_SpinBoxDown) {
        drawSpinboxArrow(style,QStyle::SC_SpinBoxDown, spinBoxOption,fetcher, painter, widget, rect);
    }

    return true;
}

QRect
DrawSpinboxHelper::spinBoxSubControlRect(const Style *style,const QStyleOptionComplex *opt, QStyle::SubControl subControl,
                                         const QWidget *w)
{
    const QStyleOptionSpinBox *spinBoxOption = nullptr;
    spinBoxOption = qstyleoption_cast<const QStyleOptionSpinBox *>(opt);
    if (spinBoxOption == nullptr) {
        return QRect();
    }

    bool hasFrame = spinBoxOption->frame;
    QRect rect(spinBoxOption->rect);

    SpinboxArrowPosition position = PropertyHelper::getSpinboxButtonPosition(w);

    if ( position == ARROW_POSITION_AUTOMATIC ){
        if (rect.width() < (rect.height() * 2 + 24)) {///左右堆叠两个正方形按钮,留空不够
            position = ARROW_VERTICAL_STACK;
        } else if ((rect.width() >= (rect.height() * 2 + 24)) &&
                   (rect.width() < (rect.height() * 2 + 24 + 180))) {///左右堆叠两个正方形按钮，留空正常，按钮放两侧
            position = ARROW_TWO_SIDERS;
        } else {
            position = ARROW_HORIZONTAL_STACK;
        }
    }

    switch (subControl) {
        case QStyle::SC_SpinBoxFrame:
            return hasFrame ? rect : QRect();
        case QStyle::SC_SpinBoxEditField: {
            int frameWidth = style->pixelMetric(QStyle::PM_SpinBoxFrameWidth, opt, w);
            if (position == ARROW_TWO_SIDERS) {
                return QRect(rect.left() + rect.height() + frameWidth, rect.top(),
                             rect.width() - 2 * rect.height() - 2*frameWidth, rect.height());
            } else if (position == ARROW_HORIZONTAL_STACK) {
                return QRect(rect.left()+frameWidth, rect.top(),
                             rect.width()-frameWidth-2*rect.height(),
                             rect.height());
            } else {
                return QRect(rect.left()+frameWidth, rect.top(),
                             rect.width()-2*frameWidth-0.6*rect.height(),
                             rect.height());
            }
        }
        case QStyle::SC_SpinBoxUp:
        case QStyle::SC_SpinBoxDown: {
            if (position == ARROW_TWO_SIDERS) {
                QSize buttonSize(rect.height(),
                                 rect.height());
                int leftTopX = subControl == QStyle::SC_SpinBoxUp ? rect.right() - buttonSize.width() : rect.left();
                QPoint point = QPoint(leftTopX, rect.top());
                return QRect(point, buttonSize);
            } else if (position == ARROW_HORIZONTAL_STACK) {
                QSize buttonSize(rect.height(),
                                 rect.height());
                int leftTopX = subControl == QStyle::SC_SpinBoxUp ? rect.right() - buttonSize.width() : rect.right() -
                                                                                                2 * buttonSize.width();
                QPoint point = QPoint(leftTopX, rect.top());
                return QRect(point, buttonSize);
            } else {
                QSize buttonSize(rect.height() * 0.5,
                                 rect.height() * 0.5);
                if (subControl == QStyle::SC_SpinBoxUp) {
                    return QRect(rect.right() - buttonSize.width(),
                                 rect.top() + 1,
                                 buttonSize.width(),
                                 buttonSize.height() - 1);
                } else {
                    return QRect(rect.right() - buttonSize.width(),
                                 rect.top() + buttonSize.height(),
                                 buttonSize.width(),
                                 buttonSize.height());
                }
            }
            break;
        }
        default:
            break;
    }

    return QRect();
}
