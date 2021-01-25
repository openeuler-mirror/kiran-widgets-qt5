//
// Created by lxh on 2021/1/14.
//

#include "kiran-image-selector.h"
#include "kiran-image-list.h"
#include "kiran-image-button.h"
#include "kiran-image-selector-private.h"

#include "style.h"

#include <QBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QListWidget>
#include <QApplication>
#include <QScrollBar>
#include <QDateTime>
#include <QPainter>
#include <QStyleOption>

KiranImageSelector::KiranImageSelector(QWidget *parent)
    :QWidget(parent),
    d_ptr(new KiranImageSelectorPrivate(this)){
    d_ptr->init(this);
}

KiranImageSelector::~KiranImageSelector() {

}

void KiranImageSelector::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QStyleOption option;
    QWidget::paintEvent(event);
}
