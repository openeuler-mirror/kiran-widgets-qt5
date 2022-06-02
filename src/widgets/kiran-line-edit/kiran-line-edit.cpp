#include "kiran-line-edit.h"
#include "kiran-line-edit-private.h"
#include <kiran-palette.h>

KiranLineEdit::KiranLineEdit(QWidget *parent)
    : QWidget(parent)
{
    d_ptr = new KiranLineEditPrivate();
    d_ptr->q_ptr = this;
    d_ptr->init();
}

KiranLineEdit::~KiranLineEdit()
{
    delete d_ptr;
}

QLineEdit* KiranLineEdit::lineEdit() const
{
    return d_func()->m_lineEdit;
}

void KiranLineEdit::setAlert(bool alert)
{
    Q_D(KiranLineEdit);
    if( alert == d->m_isAlert )
    {
        return;
    }

    d->m_isAlert = alert;
    update();
}

bool KiranLineEdit::getAlert() const
{
    return d_func()->m_isAlert;
}

void KiranLineEdit::setTipsPosition(TipsPosition position)
{
    Q_D(KiranLineEdit);

    if( position == d->m_tipsPosition )
    {
        return;
    }

    d->m_tipsPosition = position;
}

KiranLineEdit::TipsPosition KiranLineEdit::getTipsPosition() const
{
    return d_func()->m_tipsPosition;
}

void KiranLineEdit::paintEvent(QPaintEvent *event)
{
    KiranPalette::instance();
    QWidget::paintEvent(event);
}

QSize KiranLineEdit::sizeHint() const
{
    return QWidget::sizeHint();
}

QSize KiranLineEdit::minimumSizeHint() const
{
    return QWidget::minimumSizeHint();
}
