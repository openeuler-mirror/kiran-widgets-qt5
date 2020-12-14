//
// Created by lxh on 2020/12/9.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
#define KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H

#include <QLineEdit>

class KiranSearchBoxPrivate;
class QLineEdit;
class QStyleOption;

/// NOTE:搜索框，只有才KiranStyle下才支持绘制搜索图标，其他Style下绘制出来只是个普通输入框
class Q_DECL_EXPORT KiranSearchBox :public QLineEdit{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranSearchBox)
public:
    explicit KiranSearchBox(QWidget *parent = nullptr);
    ~KiranSearchBox();

protected:
    ///NOTE:预留
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    KiranSearchBoxPrivate* d_ptr;
};


#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_H
