//
// Created by lxh on 2020/12/9.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_PRIVATE_H
#define KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_PRIVATE_H

#include "kiran-search-box.h"

#include <QObject>
#include <QBoxLayout>

class KiranSearchBoxPrivate : public QObject{
    Q_OBJECT
    Q_DECLARE_PUBLIC(KiranSearchBox)
public:
    KiranSearchBoxPrivate(QObject* parent = nullptr);
    ~KiranSearchBoxPrivate();

    void adjustMargins();

private:
    void init(KiranSearchBox* ptr);

private:
    KiranSearchBox* q_ptr = nullptr;
    QHBoxLayout* m_hBoxLayout = nullptr;
    QLineEdit* m_edit = nullptr;
};

#endif //KIRANWIDGETS_QT5_KIRAN_SEARCH_BOX_PRIVATE_H
