#include "kiran-color-block.h"
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include "kiran-color-block-private.h"
using namespace Kiran;

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

bool KiranColorBlock::getDrawBackground()
{
    return d_func()->m_drawBackground;
}

void KiranColorBlock::setDrawBackground(bool enable)
{
    Q_D(KiranColorBlock);
    if (d->m_drawBackground == enable)
        return;
    d->m_drawBackground = enable;
    update();
}

void KiranColorBlock::setFixedBackgroundState(Kiran::StylePalette::ColorState state)
{
    Q_D(KiranColorBlock);
    if (d->m_fixedBackground && d->m_fixedBackgroundState == state)
        return;
    d->m_fixedBackground = true;
    d->m_fixedBackgroundState = state;
    update();
}

void KiranColorBlock::unsetFixedBackgroundState()
{
    Q_D(KiranColorBlock);
    if (!d->m_fixedBackground)
        return;
    d->m_fixedBackground = false;
    update();
}

void KiranColorBlock::paintEvent(QPaintEvent *event)
{
    Q_D(KiranColorBlock);

    QStyleOption opt;
    QStyle::State state;

    opt.initFrom(this);
    state = opt.state;
    QRectF frect = opt.rect;

    QPainterPath painterPath;
    painterPath.addRoundedRect(frect, d->m_radius, d->m_radius);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto getStateFunc = [this](QStyle::State state) -> StylePalette::ColorState
    {
        if (!(state & QStyle::State_Enabled))
        {
            return StylePalette::Disabled;
        }
        else if (state & QStyle::State_Sunken)
        {
            return StylePalette::Active;
        }
        else if ((state & QStyle::State_MouseOver) && testAttribute(Qt::WA_Hover))
        {
            return StylePalette::Hover;
        }
        else
            return StylePalette::Normal;
    };

    auto kiranPalette = Kiran::StylePalette::instance();
    if (d->m_drawBackground)
    {
        QColor background;
        background = kiranPalette->color(d->m_fixedBackground ? d->m_fixedBackgroundState : getStateFunc(state),
                                         Kiran::StylePalette::Widget,
                                         Kiran::StylePalette::Background);
        painter.fillPath(painterPath, background);
    }

    QWidget::paintEvent(event);
}
