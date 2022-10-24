#pragma once

#include <QLabel>
#include <QObject>
#include "kiran-hover-tips.h"

class KiranHoverTipsPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranHoverTips)
public:
    KiranHoverTipsPrivate(KiranHoverTips *ptr);
    ~KiranHoverTipsPrivate();

    void init();
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    void updatePosition();
    void startHideTimer();
    void stopHideTimer();

private:
    KiranHoverTips *q_ptr;
    QMap<KiranHoverTips::HoverTipsTypeEnum, QString> m_tipsTypeIconMap = {
        {KiranHoverTips::HOVE_TIPS_SUC, ":/kiranwidgets-qt5/images/hover-tips/tips-suc.svg"},
        {KiranHoverTips::HOVE_TIPS_INFO, ":/kiranwidgets-qt5/images/hover-tips/tips-info.svg"},
        {KiranHoverTips::HOVE_TIPS_WARNING, ":/kiranwidgets-qt5/images/hover-tips/tips-warning.svg"},
        {KiranHoverTips::HOVE_TIPS_ERR, ":/kiranwidgets-qt5/images/hover-tips/tips-err.svg"}};
    QLabel *m_iconLabel;
    QLabel *m_textLabel;
    quint32 m_hideTimeout = 3000;
    int m_hideTimerID = -1;
};