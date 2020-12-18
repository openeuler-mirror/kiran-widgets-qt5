/*
 * @file   kiran-switch-button.h
 * @brief  Kiran开关按钮
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANSTYLE_SWITCH_BUTTON_H
#define KIRANSTYLE_SWITCH_BUTTON_H

#include <QAbstractButton>

class KiranSwitchButtonPrivate;
class QStyleOptionButton;

/**
 * @brief SwitchButton，仅在KiranStyle下生效，其他Style中仅绘制成Button
 * @since 2.1.0
 * @see QAbstractButton
 */
class Q_DECL_EXPORT KiranSwitchButton : public QAbstractButton{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSwitchButton);
public:
    /**
     * @brief KiranSwitchButton构造方法
     * @param parent 父控件
     */
    explicit KiranSwitchButton(QWidget* parent = nullptr);
    /**
     * @brief KiranSwitchButton析构方法
     */
    ~KiranSwitchButton();

    /**
     * @see QWidget::sizeHint()
     */
    virtual QSize sizeHint() const override;

    /**
     * @see QWidget::minimumSizeHint()
     */
    virtual QSize minimumSizeHint() const override;
private:
    void initStyleOption(QStyleOptionButton* option) const;
    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    /* KiranSwitchButton私有类指针 */
    KiranSwitchButtonPrivate *d_ptr;
};


#endif //KIRANSTYLE_SWITCH_BUTTON_H
