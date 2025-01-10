//
// Created by liuxinhao on 2022/5/19.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H
#define KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H

#include <QPushButton>

class KiranPushButtonPrivate;
class KiranPushButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranPushButton);

public:
    enum ButtonType
    {
        BUTTON_Normal,  /** < 普通按钮 */
        BUTTON_Default, /** < 默认按钮，突出显示 */
        BUTTON_Warning  /** < 警告按钮，突出警示显示 */
    };

public:
    explicit KiranPushButton(QWidget *parent = nullptr);
    explicit KiranPushButton(const QString &text, QWidget *parent = nullptr);
    ~KiranPushButton();

    /**
     * @brief 按钮内文字是否使用下划线
     * @return 是否使用下划线
     */
    bool fontUnderLine();
    /**
     * @brief 设置按钮内文字是否使用下划线
     * @param enable 是否使用下划线
     */
    void setFontUnderLine(bool enable);

    /**
     * @brief 获取按钮类型
     * @return 按钮类型
     */
    static KiranPushButton::ButtonType getButtonType(const QPushButton *btn);
    /**
     * @brief 设置按钮类型
     * @param btn 需要设置的按钮
     * @param type   按钮类型
     */
    static void setButtonType(QPushButton *btn, KiranPushButton::ButtonType type);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    KiranPushButtonPrivate *d_ptr;
};

#endif  // KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H
