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
 * @since kiranwidgets-qt5-2.1.0
 */
class Q_DECL_EXPORT KiranSwitchButton : public QAbstractButton{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSwitchButton);
public:
    explicit KiranSwitchButton(QWidget* parent = nullptr);
    ~KiranSwitchButton();

    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
signals:
    void checkedChanged(bool checked);

private:
    void initStyleOption(QStyleOptionButton* option) const;
    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    KiranSwitchButtonPrivate *d_ptr;
};


#endif //KIRANSTYLE_SWITCH_BUTTON_H
