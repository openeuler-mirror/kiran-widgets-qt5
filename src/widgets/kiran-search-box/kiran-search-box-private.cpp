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

#include "kiran-search-box-private.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>

#include <palette.h>
#include <style-helper.h>

using namespace Kiran::Theme;

KiranSearchBoxPrivate::KiranSearchBoxPrivate(QObject* parent)
    : QObject(parent)
{
    connect(DEFAULT_PALETTE(), &Palette::baseColorsChanged, this, &KiranSearchBoxPrivate::updateSearchPixmap);
}

KiranSearchBoxPrivate::~KiranSearchBoxPrivate()
{
}

void KiranSearchBoxPrivate::init(KiranSearchBox* ptr)
{
    q_ptr = ptr;

    auto layout = new QHBoxLayout(q_ptr);
    m_searchLabel = new QLabel(q_ptr);
    layout->addWidget(m_searchLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);

    q_ptr->setTextMargins(24, 0, 0, 0);
    updateSearchPixmap();
}

void KiranSearchBoxPrivate::updateSearchPixmap()
{
    QIcon icon(":/kiranwidgets-qt5/images/search-box/search.svg");
    QPixmap pixmap = icon.pixmap(16, 16);
    if (DEFAULT_STYLE_HELPER()->paletteType() != PaletteType::PALETTE_DARK)
    {
        QImage image = pixmap.toImage();
        image.invertPixels(QImage::InvertRgb);
        pixmap = QPixmap::fromImage(image);
    }
    m_searchLabel->setPixmap(pixmap);
}
