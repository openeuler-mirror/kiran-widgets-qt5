//
// Created by lxh on 2020/11/19.
//

#include "draw-common-helper.h"

#include <QtMath>
#include <QDebug>
#include <QApplication>
#include <QX11Info>

using namespace Kiran;

QRect DrawCommonHelper::centerRect(const QRect &rect, int width, int height)
{
    return QRect(rect.left() + (rect.width() - width) / 2, rect.top() + (rect.height() - height) / 2, width, height);
}

QRect DrawCommonHelper::centerRect(const QRect &rect, const QSize &size)
{
    return centerRect(rect, size.width(), size.height());
}

//* adjust rect based on provided margins
QRect DrawCommonHelper::insideMargin(const QRect &r, int margin)
{
    return insideMargin(r, margin, margin);
}

//* adjust rect based on provided margins
QRect DrawCommonHelper::insideMargin(const QRect &r, int marginWidth, int marginHeight)
{
    return r.adjusted(marginWidth, marginHeight, -marginWidth, -marginHeight);
}

//* expand size based on margins
QSize DrawCommonHelper::expandSize(const QSize &size, int margin)
{
    return expandSize(size, margin, margin);
}

//* expand size based on margins
QSize DrawCommonHelper::expandSize(const QSize &size, int marginWidth, int marginHeight)
{
    return size + 2 * QSize(marginWidth, marginHeight);
}

void DrawCommonHelper::drawFrame(QPainter *painter, const QRect &rect,
                                 int radius, int outlineWidth,
                                 const QColor &color, const QColor &outline)
{

    painter->setRenderHint(QPainter::Antialiasing);

    double dwidthHalf = outlineWidth / 2.0;
    int widthHalf = qCeil(dwidthHalf);

    QRectF frameRect = rect.adjusted(widthHalf, widthHalf, -widthHalf, -widthHalf);

    // set pen
    if (outline.isValid() && outlineWidth > 0) {
        painter->setPen(QPen(outline, outlineWidth));

        radius = qMax(radius - 1.0, qreal(0.0));
    } else {
        painter->setPen(Qt::NoPen);
    }

    frameRect.adjust(dwidthHalf, dwidthHalf, -dwidthHalf, -dwidthHalf);

    // set brush
    if (color.isValid()) painter->setBrush(color);
    else painter->setBrush(Qt::NoBrush);

    // render
    painter->drawRoundedRect(frameRect, radius, radius);
}

void
DrawCommonHelper::drawSpinboxArrow(QPainter *painter, const QRect &rect, const QRect &spinboxRect, int spinboxRadius,
                                   QColor bgColor,
                                   QColor signColor, bool isUp)
{
    painter->setRenderHint(QPainter::Antialiasing);

    ///以SpinboxFrame作为裁切路径
    QPainterPath backgroundPath;
    spinboxRect.adjusted(1, 1, -1, -1);
    backgroundPath = getRoundedRectanglePath(spinboxRect, spinboxRadius, spinboxRadius, spinboxRadius, spinboxRadius);

    painter->setClipPath(backgroundPath, Qt::ReplaceClip);
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawRect(rect);

    QPen pen(signColor, 2);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawLine(rect.center() - QPointF(4, 0), rect.center() + QPointF(4, 0));

    if (isUp) {
        painter->drawLine(rect.center() - QPointF(0, 4), rect.center() + QPointF(0, 4));
    }
}

QPainterPath DrawCommonHelper::getRoundedRectanglePath(const QRect &rect,
                                                       int tlRadius, int trRadius,
                                                       int blRadius, int brRadius)
{
    QPainterPath painterPath;

    /// 判断圆角半径是否合法,不合法调整参数
    if (tlRadius + trRadius > rect.width()) {
        tlRadius = trRadius = 0;
    }
    if (tlRadius + blRadius > rect.height()) {
        tlRadius = blRadius = 0;
    }
    if (blRadius + brRadius > rect.width()) {
        blRadius = brRadius = 0;
    }
    if (trRadius + brRadius > rect.height()) {
        trRadius = brRadius = 0;
    }

    /// 计算圆角矩形
    QSize tlSize(tlRadius, tlRadius);
    QSize trSize(trRadius, trRadius);
    QSize brSize(brRadius, brRadius);
    QSize blSize(blRadius, blRadius);

    // top left corner
    if (!tlSize.isEmpty()) {
        QRectF tlArcRect(rect.left(), rect.top(), tlRadius * 2, tlRadius * 2);
        painterPath.moveTo(rect.left(), rect.top() + tlRadius);
        painterPath.arcTo(tlArcRect, -180, -90);
    }

    // top
    painterPath.lineTo(rect.right() - trSize.width(), rect.top());

    // top right corner
    if (!trSize.isEmpty()) {
        QRectF trArcRect(rect.right() - 2 * trRadius, rect.top(), trRadius * 2, trRadius * 2);
        painterPath.arcTo(trArcRect, 90, -90);
    }

    // right
    painterPath.lineTo(rect.right(), rect.bottom() - brSize.height());

    // bottom right
    if (!brSize.isEmpty()) {
        QRectF brArcRect(rect.right() - 2 * brRadius, rect.bottom() - 2 * brRadius, brRadius * 2, brRadius * 2);
        painterPath.arcTo(brArcRect, 0, -90);
    }

    // bottom
    painterPath.lineTo(rect.left() + blSize.width(), rect.bottom());

    // bottom left
    if (!blSize.isEmpty()) {
        QRectF blArcRect(rect.left(), rect.bottom() - 2 * blRadius, blRadius * 2, blRadius * 2);
        painterPath.arcTo(blArcRect, -90, -90);
    }

    // left
    painterPath.lineTo(rect.left(), rect.top() + tlSize.height());
    return painterPath;
}

void DrawCommonHelper::drawRadioButtonIndicator(QPainter *painter, const QRect &rect,
                                                const QColor &IndicatorColor, bool isOn)
{
    QRect frameRect(rect);
    frameRect.adjust(2, 2, -2, -2);

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen(IndicatorColor);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    QRectF contentRect(frameRect.adjusted(0.5, 0.5, -0.5, -0.5));
    painter->drawEllipse(contentRect);

    if (isOn) {
        painter->setBrush(IndicatorColor);
        painter->setPen(Qt::NoPen);
        QRectF markerRect(frameRect.adjusted(3, 3, -3, -3));
        painter->drawEllipse(markerRect);
    }
}

void DrawCommonHelper::drawCheckBoxIndicator(QPainter *painter, const QRect &rect, const QColor &border,
                                             const QColor &bgColor,
                                             const QColor &indicatorColor, CheckBoxIndicatorState indicatorState)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    QRect frameRect(rect);
    frameRect.adjust(2, 2, -2, -2);

    painter->save();
    drawFrame(painter, frameRect, 2, 1, bgColor, border);
    painter->restore();

    if (indicatorState == CheckOn) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(Qt::NoBrush);
        QPen pen(indicatorColor, 1.4);
        pen.setJoinStyle(Qt::MiterJoin);
        painter->setPen(pen);

        QRectF markerRect(frameRect);

        QPainterPath path;
        path.moveTo(markerRect.right() - markerRect.width() / 3.2, markerRect.top() + markerRect.height() / 3);
        path.lineTo(markerRect.center().x(), markerRect.bottom() - markerRect.height() / 3.0);
        path.lineTo(markerRect.left() + markerRect.width() / 3.2, markerRect.center().y());

        painter->setClipRect(markerRect);
        painter->drawPath(path);
        painter->restore();
    } else if (indicatorState == CheckPartial) {
        QPen pen(indicatorColor, 2);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);

        QRectF markerRect(frameRect.adjusted(4, 4, -4, -4));
        painter->drawLine(markerRect.center() - QPoint(3, 0), markerRect.center() + QPoint(3, 0));
    }
}

bool DrawCommonHelper::isCompositingManagerRuning()
{
    return QX11Info::isCompositingManagerRunning();
}

void DrawCommonHelper::drawSeparator(QPainter *painter, const QRect &rect, QColor color, bool vertical)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(color);

    if (vertical) {
        painter->translate(rect.width() / 2, 0);
        painter->drawLine(rect.topLeft(), rect.bottomLeft());
    } else {
        painter->translate(0, rect.height() / 2);
        painter->drawLine(rect.topLeft(), rect.topRight());
    }

    painter->restore();
}

void DrawCommonHelper::drawMenuCheckedIndicator(QPainter *painter, const QRect &rect,
                                                QColor bgColor, QColor signColor)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    if (bgColor.isValid()) {
        QPainterPath bgPath;
        bgPath.addEllipse(rect);
        painter->fillPath(bgPath, bgColor);
    }

    QRectF markerRect(rect);
    QPainterPath path;
    path.moveTo(markerRect.right() - markerRect.width() / 4.2, markerRect.top() + markerRect.height() / 3.8);
    path.lineTo(markerRect.center().x(), markerRect.bottom() - markerRect.height() / 3.0);
    path.lineTo(markerRect.left() + markerRect.width() / 4.2, markerRect.center().y());

    QPen pen(signColor, 2);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);

    painter->setClipRect(markerRect);
    painter->drawPath(path);

    painter->restore();
}

void DrawCommonHelper::drawArrow(QPainter *painter, const QRect &rect,
                                 const QColor &color, ArrowOrientation orientation)
{
#if 0
    // define polygon
    QPolygonF arrow;
    switch (orientation) {
        case ArrowUp:
            arrow << QPointF(-4, 2) << QPointF(0, -2) << QPointF(4, 2);
            break;
        case ArrowDown:
            arrow << QPointF(-4, -2) << QPointF(0, 2) << QPointF(4, -2);
            break;
        case ArrowLeft:
            arrow << QPointF(2, -4) << QPointF(-2, 0) << QPointF(2, 4);
            break;
        case ArrowRight:
            arrow << QPointF(-2, -4) << QPointF(2, 0) << QPointF(-2, 4);
            break;
        default:
            break;
    }

    QPen pen(color, 1.2);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    painter->translate(QRectF(rect).center());
    painter->setBrush(color);
    painter->setPen(pen);
    painter->drawPolygon(arrow);

    painter->restore();

    return;
#else
    QRect markRect(rect.adjusted(1, 1, -1, -1));
    QPen pen(color, 1.5);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter->save();

    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter->setPen(pen);

    QPainterPath path;
    path.moveTo(markRect.left() + markRect.width() / 3, markRect.top() + markRect.height() / 2.4);
    path.lineTo(markRect.center().x(), markRect.bottom() - markRect.height() / 2.5);
    path.lineTo(markRect.right() - markRect.width() / 3, markRect.top() + markRect.height() / 2.4);
    painter->drawPath(path);

    painter->restore();
#endif
}

void
DrawCommonHelper::drawDecorationButton(QPainter *painter,
                                       const QRect &rect,
                                       const QColor &color,
                                       TitleBarButtonType buttonType)
{
    painter->save();
    painter->setViewport(rect);
    painter->setWindow(0, 0, 18, 18);
    painter->setRenderHints(QPainter::Antialiasing, false);

    // initialize pen
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::MiterJoin);

    painter->setBrush(Qt::NoBrush);

    pen.setColor(color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(2.0 * qMax(1.0, 18.0 / rect.width()));
    painter->setPen(pen);

    switch (buttonType) {
        case ButtonClose: {
            painter->setRenderHints(QPainter::Antialiasing, true);
            painter->drawLine(QPointF(5, 5), QPointF(13, 13));
            painter->drawLine(13, 5, 5, 13);
            break;
        }

        case ButtonMaximize: {
            painter->drawPolyline(QPolygonF()
                                          << QPointF(4, 4)
                                          << QPointF(4, 14)
                                          << QPointF(14, 14)
                                          << QPointF(14, 4));
            break;
        }

        case ButtonMinimize: {

            painter->drawPolyline(QPolygonF()
                                          << QPointF(4, 14)
                                          << QPointF(14, 14));
            break;
        }

        case ButtonRestore: {
            painter->setPen(pen);
            QPolygonF rect = QPolygonF() << QPointF(0, 0)
                                         << QPointF(8, 0)
                                         << QPointF(8, 8)
                                         << QPointF(0, 8);
            painter->drawPolygon(rect.translated(7, 3));
            painter->drawPolygon(rect.translated(3, 7));
            break;
        }

        default:
            break;
    }

    painter->restore();
    return;
}
