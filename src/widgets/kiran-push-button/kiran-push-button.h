//
// Created by liuxinhao on 2022/5/19.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H
#define KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H

#include <QPushButton>

//TODO:private class
class KiranPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KiranPushButton(QWidget* parent = nullptr);
    explicit KiranPushButton(const QString &text, QWidget *parent = nullptr);
    ~KiranPushButton();

    bool fontUnderLine();
    void setFontUnderLine(bool enable);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_fontUnderLineEnable = false;
};

#endif  // KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H
