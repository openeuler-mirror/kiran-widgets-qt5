#include "kiran-color-block.h"
#include <palette.h>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include "kiran-color-block-private.h"

using namespace Kiran::Theme;

QPainterPath roundedPath(const QRectF &rect, KiranColorBlock::Corners corners, int radius)
{
    QPainterPath path;

    if (corners == 0)
    {
        path.addRect(rect);
        return path;
    }

    if (corners == KiranColorBlock::AllCorners)
    {
        path.addRoundedRect(rect, radius, radius);
        return path;
    }

    const QSizeF cornerSize(2 * radius, 2 * radius);

    // rotate counterclockwise
    // top left corner
    if (corners & KiranColorBlock::CornerTopLeft)
    {
        path.moveTo(rect.topLeft() + QPointF(radius, 0));
        path.arcTo(QRectF(rect.topLeft(), cornerSize), 90, 90);
    }
    else
        path.moveTo(rect.topLeft());

    // bottom left corner
    if (corners & KiranColorBlock::CornerBottomLeft)
    {
        path.lineTo(rect.bottomLeft() - QPointF(0, radius));
        path.arcTo(QRectF(rect.bottomLeft() - QPointF(0, 2 * radius), cornerSize), 180, 90);
    }
    else
        path.lineTo(rect.bottomLeft());

    // bottom right corner
    if (corners & KiranColorBlock::CornerBottomRight)
    {
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.arcTo(QRectF(rect.bottomRight() - QPointF(2 * radius, 2 * radius), cornerSize), 270, 90);
    }
    else
        path.lineTo(rect.bottomRight());

    // top right corner
    if (corners & KiranColorBlock::CornerTopRight)
    {
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.arcTo(QRectF(rect.topRight() - QPointF(2 * radius, 0), cornerSize), 0, 90);
    }
    else
        path.lineTo(rect.topRight());

    path.closeSubpath();
    return path;
}

KiranColorBlock::KiranColorBlock(QWidget *parent)
    : QWidget{parent},
      d_ptr(new KiranColorBlockPrivate(this))
{
}

KiranColorBlock::~KiranColorBlock()
{
    delete d_ptr;
}

void KiranColorBlock::setRadius(int radius)
{
    Q_D(KiranColorBlock);
    if (radius < 0 || radius == d->m_radius)
    {
        return;
    }
    d->m_radius = radius;
    update();
}

int KiranColorBlock::getRadius()
{
    return d_func()->m_radius;
}

void KiranColorBlock::setRoundedCorner(Corner corner)
{
    if (d_ptr->m_radiusCorner != corner)
    {
        d_ptr->m_radiusCorner = corner;
        update();
    }
}

KiranColorBlock::Corner KiranColorBlock::getRoundedCorner()
{
    return d_ptr->m_radiusCorner;
}

void KiranColorBlock::paintEvent(QPaintEvent *event)
{
    Q_D(KiranColorBlock);

    if (!d_func()->m_drawBackground)
    {
        return QWidget::paintEvent(event);
    }

    QStyleOption opt;
    QStyle::State state;

    opt.initFrom(this);
    state = opt.state;
    QRectF frect = opt.rect;

    QPainterPath painterPath;
    painterPath = roundedPath(frect, d_ptr->m_radiusCorner, d_ptr->m_radius);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor background;
    // background = kiranPalette->getBulkColor();
    // FIXME:暂时通过获取激活状态下的控件颜色代替
    background = DEFAULT_PALETTE()->getColor(Palette::ColorGroup::ACTIVE, Palette::ColorRole::WIDGET);
    painter.fillPath(painterPath, background);

    QWidget::paintEvent(event);
}

bool KiranColorBlock::getDrawBackground()
{
    return d_func()->m_drawBackground;
}

void KiranColorBlock::setDrawBackground(bool enable)
{
    if (d_func()->m_drawBackground != enable)
    {
        d_func()->m_drawBackground = enable;
        update();
    }
}