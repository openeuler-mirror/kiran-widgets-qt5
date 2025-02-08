#ifndef KIRAN_COLOR_BLOCK_H
#define KIRAN_COLOR_BLOCK_H

#include <QWidget>

class KiranColorBlockPrivate;
class KiranColorBlock : public QWidget
{
    Q_OBJECT
public:
    enum Corner
    {
        CornerTopLeft = 0x1,
        CornerTopRight = 0x2,
        CornerBottomLeft = 0x4,
        CornerBottomRight = 0x8,
        CornersTop = CornerTopLeft | CornerTopRight,
        CornersBottom = CornerBottomLeft | CornerBottomRight,
        CornersLeft = CornerTopLeft | CornerBottomLeft,
        CornersRight = CornerTopRight | CornerBottomRight,
        AllCorners = CornerTopLeft | CornerTopRight | CornerBottomLeft | CornerBottomRight,
    };
    Q_DECLARE_FLAGS(Corners, Corner)

    explicit KiranColorBlock(QWidget *parent = nullptr);
    ~KiranColorBlock();

    /**
     * @brief 设置圆角
     * @param radius 圆角大小
     */
    void setRadius(int radius);
    /**
     * @brief 获取圆角值
     * @return 圆角值
     */
    int getRadius();

    void setRoundedCorner(Corner corder);
    Corner getRoundedCorner();

    bool getDrawBackground();
    void setDrawBackground(bool enable);

    void specifyColor(const QColor &normal,const QColor &hover);
    void unsetSpecifiedColor();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    KiranColorBlockPrivate *d_ptr;
    Q_DECLARE_PRIVATE(KiranColorBlock)
};

#endif  // KIRAN_COLOR_BLOCK_H
