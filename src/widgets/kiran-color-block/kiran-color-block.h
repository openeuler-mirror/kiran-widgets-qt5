#ifndef KIRAN_COLOR_BLOCK_H
#define KIRAN_COLOR_BLOCK_H

#include <style-palette.h>
#include <QWidget>

class KiranColorBlockPrivate;
class KiranColorBlock : public QWidget
{
    Q_OBJECT

public:
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

    /**
     * @brief 获取是否绘制背景
     * @return 是否绘制背景
     */
    bool getDrawBackground();
    /**
     * @brief 设置是否绘制背景
     * @param 是否绘制背景
     */
    void setDrawBackground(bool enable);
    /**
     * @brief 设置绘制背景固定的状态，不根据实际状态从KiranPalette之中取出颜色(除了disable状态，disable将还是从KiranPalette之中取出禁用色)
     * @param state 希望固定的颜色状态
     */
    void setFixedBackgroundState(Kiran::StylePalette::ColorState state);
    /**
     * @brief 取消掉固定背景状态，背景色根据实际状态取出
     */
    void unsetFixedBackgroundState();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    KiranColorBlockPrivate *d_ptr;
    Q_DECLARE_PRIVATE(KiranColorBlock)
};

#endif  // KIRAN_COLOR_BLOCK_H
