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

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

protected:
    void updateMask();

private:
    int m_radius;
};