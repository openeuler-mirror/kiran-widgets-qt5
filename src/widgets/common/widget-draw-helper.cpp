#include "widget-draw-helper.h"

QRect WidgetDrawHelper::centerRect(const QRect& rect, int width, int height)
{
    return QRect(rect.left() + (rect.width() - width) / 2, rect.top() + (rect.height() - height) / 2, width, height);
}

QRect WidgetDrawHelper::centerRect(const QRect& rect, const QSize& size)
{
    return centerRect(rect, size.width(), size.height());
}

QRect WidgetDrawHelper::insideMargin(const QRect& r, int margin)
{
    return insideMargin(r, margin, margin);
}

QRect WidgetDrawHelper::insideMargin(const QRect& r, int marginWidth, int marginHeight)
{
    return r.adjusted(marginWidth, marginHeight, -marginWidth, -marginHeight);
}

QSize WidgetDrawHelper::expandSize(const QSize& size, int margin)
{
    return expandSize(size, margin, margin);
}

QSize WidgetDrawHelper::expandSize(const QSize& size, int marginWidth, int marginHeight)
{
    return size + 2 * QSize(marginWidth, marginHeight);
}

QPainterPath WidgetDrawHelper::getRoundedRectanglePath(const QRectF& rect, int tlRadius, int trRadius, int blRadius, int brRadius)
{
    QPainterPath painterPath;

    /// 判断圆角半径是否合法,不合法调整参数
    if (tlRadius + trRadius > rect.width())
    {
        tlRadius = trRadius = 0;
    }
    if (tlRadius + blRadius > rect.height())
    {
        tlRadius = blRadius = 0;
    }
    if (blRadius + brRadius > rect.width())
    {
        blRadius = brRadius = 0;
    }
    if (trRadius + brRadius > rect.height())
    {
        trRadius = brRadius = 0;
    }

    /// 计算圆角矩形
    QSize tlSize(tlRadius, tlRadius);
    QSize trSize(trRadius, trRadius);
    QSize brSize(brRadius, brRadius);
    QSize blSize(blRadius, blRadius);

    // top left corner
    if (!tlSize.isEmpty())
    {
        QRectF tlArcRect(rect.left(), rect.top(), tlRadius * 2, tlRadius * 2);
        painterPath.moveTo(rect.left(), rect.top() + tlRadius);
        painterPath.arcTo(tlArcRect, -180, -90);
    }

    // top
    painterPath.lineTo(rect.right() - trSize.width(), rect.top());

    // top right corner
    if (!trSize.isEmpty())
    {
        QRectF trArcRect(rect.right() - 2 * trRadius, rect.top(), trRadius * 2, trRadius * 2);
        painterPath.arcTo(trArcRect, 90, -90);
    }

    // right
    painterPath.lineTo(rect.right(), rect.bottom() - brSize.height());

    // bottom right
    if (!brSize.isEmpty())
    {
        QRectF brArcRect(rect.right() - 2 * brRadius, rect.bottom() - 2 * brRadius, brRadius * 2, brRadius * 2);
        painterPath.arcTo(brArcRect, 0, -90);
    }

    // bottom
    painterPath.lineTo(rect.left() + blSize.width(), rect.bottom());

    // bottom left
    if (!blSize.isEmpty())
    {
        QRectF blArcRect(rect.left(), rect.bottom() - 2 * blRadius, blRadius * 2, blRadius * 2);
        painterPath.arcTo(blArcRect, -90, -90);
    }

    // left
    painterPath.lineTo(rect.left(), rect.top() + tlSize.height());
    return painterPath;
}
