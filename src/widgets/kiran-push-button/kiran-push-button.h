//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H
#define KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H

#include <QPushButton>
#include <style-property-helper.h>

class KiranPushButtonPrivate;
class Q_DECL_EXPORT KiranPushButton : public QPushButton{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranPushButton);
public:
    explicit KiranPushButton(QWidget *parent = nullptr);
    explicit KiranPushButton(const QString &text, QWidget *parent = nullptr);
    KiranPushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
    ~KiranPushButton();

    /// NOTE:只在KiranStyle下才能生效
    /// 设置按钮类型(KiranStyle提供了三种内置按钮样式)
    /// \param buttonType   按钮类型
    void setButtonType(Kiran::ButtonType buttonType);

    /// 获取按钮类型
    /// \return 按钮类型
    Kiran::ButtonType getButtonType();

protected:
    bool event(QEvent *e) override;

private:
    KiranPushButtonPrivate* d_ptr;
};


#endif //KIRANWIDGETS_QT5_KIRAN_PUSH_BUTTON_H
