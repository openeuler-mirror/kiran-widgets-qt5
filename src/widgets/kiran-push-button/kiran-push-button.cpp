//
// Created by liuxinhao on 2022/5/19.
//

#include "kiran-push-button.h"
#include <QPushButton>
#include <QStylePainter>
#include <QStyleOptionButton>

KiranPushButton::KiranPushButton(QWidget *parent)
    : QPushButton(parent)
{

}

KiranPushButton::KiranPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
}

KiranPushButton::~KiranPushButton()
{
}

bool KiranPushButton::fontUnderLine()
{
    return m_fontUnderLineEnable;
}

void KiranPushButton::setFontUnderLine(bool enable)
{
    if( enable == m_fontUnderLineEnable )
        return;
    m_fontUnderLineEnable = enable;
    update();
}

void KiranPushButton::paintEvent(QPaintEvent *event)
{
    QStylePainter p(this);
    QStyleOptionButton option;

    //不设置font进入QWidget之中，避免影响后续字体变更的功能
    auto tempfont = p.font();
    tempfont.setUnderline(m_fontUnderLineEnable);
    p.setFont(tempfont);

    initStyleOption(&option);
    p.drawControl(QStyle::CE_PushButton, option);
}
