#include "kiran-icon.h"
#include "kiran-icon-private.h"

#include <QPainter>
KiranIcon::KiranIcon(QWidget *parent)
    : QWidget(parent),
      d_ptr(new KiranIconPrivate(this))
{
}

void KiranIcon::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

QIcon KiranIcon::icon()
{
    return m_icon;
}

void KiranIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    if (!m_icon.isNull())
    {
        m_icon.paint(&painter, rect());
    }
}
