#ifndef KIRAN_BACKGROUND_WIDGET_PRIVATE_H
#define KIRAN_BACKGROUND_WIDGET_PRIVATE_H

#include "kiran-color-block.h"

class KiranColorBlockPrivate
{
public:
    KiranColorBlockPrivate(KiranColorBlock* ptr) : q_ptr(ptr) {}

private:
    KiranColorBlock* q_ptr;
    Q_DECLARE_PUBLIC(KiranColorBlock)

    int m_radius = 6;
    bool m_drawBackground = true;
    bool m_fixedBackground = false;

    Kiran::StylePalette::ColorState m_fixedBackgroundState = Kiran::StylePalette::Normal;
    Kiran::StylePalette::ColorState m_fixedBorderState = Kiran::StylePalette::Normal;
};

#endif  // KIRAN_BACKGROUND_WIDGET_PRIVATE_H
