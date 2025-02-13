#ifndef KIRANICON_H
#define KIRANICON_H

#include <QFile>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

class KiranIconPrivate;

/**
 * @brief 该控件用于显示图标
 */

class KiranIcon : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranIcon)

public:
    explicit KiranIcon(QWidget *parent = nullptr);
    ~KiranIcon() override = default;

    /**
     * @brief 设置图标
     * @param icon 图标
     */
    void setIcon(const QIcon &icon);

    /**
     * @brief 获取设置的图标
     * @return 图标
     */
    QIcon icon();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QIcon m_icon;
    KiranIconPrivate *d_ptr;
};

#endif  // KIRANICON_H
