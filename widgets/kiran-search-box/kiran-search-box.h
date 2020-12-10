//
// Created by lxh on 2020/12/9.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
#define KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H

#include <QWidget>

class KiranSearchBoxPrivate;
class QLineEdit;
class QStyleOption;
class KiranSearchBox :public QWidget{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSearchBox)
public:
    explicit KiranSearchBox(QWidget *parent = nullptr);
    ~KiranSearchBox();

    QLineEdit* getLineEdit();
    virtual QSize sizeHint() const override;

protected:
    void initStyleOption(QStyleOption* option) const;
    bool event(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranSearchBoxPrivate* d_ptr;
};


#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
