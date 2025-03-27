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

#include <QFrame>

class FramelessBackgroundFrame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int radius READ getRadius WRITE setRadius)
public:
    explicit FramelessBackgroundFrame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~FramelessBackgroundFrame();

    int getRadius() const;
    void setRadius(int radius);

    bool getDrawBorder();
    void setDrawBorder(bool drawBorder);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

protected:
    void updateMask();

private:
    int m_radius;
    bool m_drawBorder = true;
};