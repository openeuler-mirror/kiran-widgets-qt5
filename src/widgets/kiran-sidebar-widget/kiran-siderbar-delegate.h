#pragma once

#include <QItemDelegate>

class KiranSiderbarDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit KiranSiderbarDelegate(QObject *parent = nullptr);
    ~KiranSiderbarDelegate();

    void setInvertIconPixelsEnable(bool enable);

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize sizeFromContents(const QStyleOptionViewItem &opt, const QModelIndex &idx,
                          QSize &pixmapSize, QSize &textSize,
                          QSize &statusDescSize, QSize &indicatorSize) const;

    QPixmap getDecorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index, QSize &pixmapSize) const;
    inline QIcon::State iconState(QStyle::State styleState) const
    {
        return (styleState & QStyle::State_On) ? QIcon::On : QIcon::Off;
    }

    inline QIcon::Mode iconMode(QStyle::State styleState) const
    {
        if (!(styleState & QStyle::State_Enabled))
            return QIcon::Disabled;
        else if (styleState & QStyle::State_Selected)
            return QIcon::Selected;
        else
            return QIcon::Normal;
    }

private:
    QString textForRole(Qt::ItemDataRole role, const QVariant &value, const QLocale &locale) const;
    QRect textLayoutBounds(const QStyleOptionViewItem &option) const;
    QSize doLayout(const QStyleOptionViewItem &option, const QModelIndex &index,
                   QRect &pixmapRect, QRect &textRect,
                   QRect &statusDescRect, QRect &indicatorRect) const;

private:
    bool m_invertIconPixelsEnable = false;
};