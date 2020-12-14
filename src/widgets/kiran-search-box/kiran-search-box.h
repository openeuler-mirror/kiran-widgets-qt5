//
// Created by lxh on 2020/12/9.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
#define KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H

#include <QLineEdit>

class KiranSearchBoxPrivate;
class QLineEdit;
class QStyleOption;
class Q_DECL_EXPORT KiranSearchBox :public QLineEdit{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSearchBox)
public:
    explicit KiranSearchBox(QWidget *parent = nullptr);
    ~KiranSearchBox();

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranSearchBoxPrivate* d_ptr;
};


#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
