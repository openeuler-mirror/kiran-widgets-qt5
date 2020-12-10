//
// Created by lxh on 2020/12/9.
//

#include "kiran-search-box.h"
#include "kiran-search-box-private.h"
#include "style.h"

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QLineEdit>
#include <QEvent>
#include <QDebug>
#include <sqltypes.h>

/*FIXME:
 * 搜索框该部分为了偷懒使用了QLineEdit控件
 * 该情况需使用布局，设置左边距,在调用KiranStyle来绘制搜索框边框和搜索图标。
 * 这种方案不能在KiranStyle里修改图标和输入框的间隙和在KiranStyle里定制更多细节。
 * */

KiranSearchBox::KiranSearchBox(QWidget *parent)
        : QWidget(parent),
          d_ptr(new KiranSearchBoxPrivate(this))
{
    d_ptr->init(this);
    d_func()->m_edit->setVisible(true);
}

KiranSearchBox::~KiranSearchBox()
{

}

QLineEdit *KiranSearchBox::getLineEdit()
{
    return d_func()->m_edit;
}

bool KiranSearchBox::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::Resize:
            d_func()->adjustMargins();
            qInfo() << "ReSizeEvent:" << this->contentsMargins();
            break;
        case QEvent::Show:
            d_func()->adjustMargins();
            qInfo() << "ShowEvent:" << this->contentsMargins();
        default:
            break;
    }
    return QWidget::event(event);
}

void KiranSearchBox::initStyleOption(QStyleOption *option) const
{
    option->init(this);
    option->initFrom(this);
    if(d_func()->m_edit->hasFocus()){
        option->state |= QStyle::State_HasFocus;
        option->state &= ~QStyle::State_MouseOver;
    }
}

void KiranSearchBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QSize searchBoxSize = size();
    QStyleOption styleOption;
    initStyleOption(&styleOption);

    if (Kiran::Style::isKiranStyle()) {
        Kiran::Style *kiranStyle = Kiran::Style::castToKiranStyle();
        kiranStyle->drawPrimitive(Kiran::PE_SearchBoxFrame,
                                  &styleOption,
                                  &painter,
                                  this);

        styleOption.rect = QRect(0,0,searchBoxSize.height(),searchBoxSize.height());
        kiranStyle->drawPrimitive(Kiran::PE_SearchBoxIndicator,
                                  &styleOption,
                                  &painter,
                                  this);
    }
}

QSize KiranSearchBox::sizeHint() const
{
    return d_func()->m_hBoxLayout?d_func()->m_hBoxLayout->sizeHint():QSize();
}

bool KiranSearchBox::eventFilter(QObject *watched, QEvent *event)
{
    ///输入框聚焦改变情况下，更新SearchBox样式
    if( watched==d_func()->m_edit && (event->type()==QEvent::FocusIn || event->type()==QEvent::FocusOut)) {
        update();
    }
    return QObject::eventFilter(watched, event);
}
