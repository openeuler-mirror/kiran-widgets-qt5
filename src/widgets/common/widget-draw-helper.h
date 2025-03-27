/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */

#pragma once

#include <QPainterPath>
#include <QRect>

namespace WidgetDrawHelper
{
/* 通过指定宽高获取矩形中的居中区域 */
QRect centerRect(const QRect &rect, int width, int height);
/* 通过指定大小获取矩形中的居中区域 */
QRect centerRect(const QRect &rect, const QSize &size);

/* 使用给定的边距调整矩形 */
QRect insideMargin(const QRect &r, int margin);
/* 使用给定的边距调整矩形 */
QRect insideMargin(const QRect &r, int marginWidth, int marginHeight);

/* 使用给定的边距调整大小 */
QSize expandSize(const QSize &size, int margin);
/* 使用给定的边距调整大小 */
QSize expandSize(const QSize &size, int marginWidth, int marginHeight);

/* 获取绘制圆角矩形路径 */
QPainterPath getRoundedRectanglePath(const QRectF &rect, int tlRadius, int trRadius, int blRadius, int brRadius);
};  // namespace WidgetDrawHelper
