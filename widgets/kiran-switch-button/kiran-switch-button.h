//
// Created by lxh on 2020/11/28.
//

#ifndef KIRANSTYLE_SWITCH_BUTTON_H
#define KIRANSTYLE_SWITCH_BUTTON_H

#include <QAbstractButton>

class KiranSwitchButtonPrivate;
class QStyleOptionButton;

class KiranSwitchButton : public QAbstractButton{
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
