 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
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