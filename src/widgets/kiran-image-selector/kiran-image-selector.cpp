/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2. 
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2 
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, 
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v2 for more details.  
 * 
 * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
 */
 
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
    connect(d_ptr->m_selectorList,&KiranImageList::selectedImageChanged,[this](QString imagePath){
        emit selectedImageChanged(imagePath);
    });
}

KiranImageSelector::~KiranImageSelector() {

}

QStringList KiranImageSelector::imageList() {
    return d_func()->m_selectorList->imageList();
}

bool KiranImageSelector::addImage(const QString &image) {
    auto item = d_func()->m_selectorList->addImageItem(image);
    return item!=nullptr;
}

void KiranImageSelector::addImages(const QStringList &imageList) {
    for( QString image:imageList ){
        addImage(image);
    }
}

void KiranImageSelector::removeImage(const QString &image) {
    d_func()->m_selectorList->removeImageItem(image);
}

void KiranImageSelector::removeImages(const QStringList &imageList) {
    for(QString image:imageList){
        removeImage(image);
    }
}

QString KiranImageSelector::selectedImage() {
    return d_func()->m_selectorList->selectedImage();
}

bool KiranImageSelector::setSelectedImage(const QString &imagePath) {
    return d_func()->m_selectorList->setSelectedImage(imagePath);
}

void KiranImageSelector::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QStyleOption option;

    option.initFrom(this);

    if( Kiran::Style::isKiranStyle() ){
        auto style = Kiran::Style::castToKiranStyle();
        style->drawPrimitive(Kiran::PE_KiranImageSelector,&option,&painter,this);
    }
}

bool KiranImageSelector::event(QEvent *event) {
    return QWidget::event(event);
}

quint64 KiranImageSelector::itemSpacing() {
    return d_func()->m_selectorList->itemSpacing();
}

void KiranImageSelector::setItemSpacing(quint64 spacing){
    d_func()->m_selectorList->setItemSpacing(spacing);
}

quint64 KiranImageSelector::itemUpAndDownSidesMargin() {
    return d_func()->m_selectorList->itemUpAndDownSidesMargin();
}

void KiranImageSelector::setItemUpAndDownSidesMargin(quint64 margin) {
    d_func()->m_selectorList->setItemUpAndDownSidesMargin(margin);
}