//
// Created by lxh on 2022/4/11.
//

#include "kiran-siderbar-delegate.h"
#include "kiran-sidebar-define.h"
#include "widget-draw-helper.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QJsonValue>
#include <QPainter>
#include <QSet>
#include <QStyle>

#include <style-palette.h>

using namespace Kiran;

KiranSiderbarDelegate::KiranSiderbarDelegate(QObject *parent) : QItemDelegate(parent)
{
}

KiranSiderbarDelegate::~KiranSiderbarDelegate()
{
}

QSize KiranSiderbarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant value = index.data(Qt::SizeHintRole);
    if (value.isValid())
        return qvariant_cast<QSize>(value);

    QSize pixmapSize, textSize, statusDescSize, indicatorSize;
    QSize totalSize = sizeFromContents(option, index, pixmapSize, textSize, statusDescSize, indicatorSize);
    totalSize.setHeight(50);
    return totalSize;
}

void KiranSiderbarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = setOptions(index, option);
    const QWidget *widget = opt.widget;
    const QStyle *style = widget ? widget->style() : QApplication::style();

    painter->save();
    painter->setClipRect(opt.rect);
    painter->setRenderHint(QPainter::Antialiasing);

    QRect pixmapRect, textRect, statusDescRect, indicatorRect;
    doLayout(opt, index, pixmapRect, textRect, statusDescRect, indicatorRect);

    const auto kiranPalette = StylePalette::instance();

    //background
    QColor bgColor = kiranPalette->color(widget, &opt, StylePalette::Widget, StylePalette::Background);
    QPainterPath fillBackgroundPath;
    fillBackgroundPath.addRoundedRect(opt.rect, 6, 6);
    fillBackgroundPath = WidgetDrawHelper::getRoundedRectanglePath(opt.rect, 5, 5, 5, 5);
    painter->fillPath(fillBackgroundPath, QBrush(bgColor));

    //pixmap
    QPixmap pixmap;
    QSize pixmapSize;
    pixmap = getDecorationPixmap(option, index, pixmapSize);
    if (!pixmap.isNull())
    {
        //默认侧边栏为白色图标，但是深浅色主题需要切换颜色，若为浅色主题，则反转颜色
        //浅色主题，选中状态不反转，仍为白色
        auto kiranPalette = StylePalette::instance();
        if(  m_invertIconPixelsEnable && kiranPalette->paletteType() == PALETTE_LIGHT && !(opt.state & QStyle::State_Selected)  )
        {
            auto image = pixmap.toImage();
            image.invertPixels(QImage::InvertRgb);
            pixmap = QPixmap::fromImage(image);
        }
        painter->drawPixmap(pixmapRect.topLeft(), pixmap);
    }

    //text
    QVariant displayVar = index.data(Qt::DisplayRole);
    if (displayVar.isValid() && !displayVar.isNull())
    {
        //将存储的数据根据locale转换
        QString text = textForRole(Qt::DisplayRole, displayVar, option.locale);
        drawDisplay(painter, opt, textRect, text);
    }

    //status desc
    QVariant statusDescVar = index.data(ItemStatus_Role);
    if (statusDescVar.isValid() && !statusDescVar.isNull())
    {
        QString statusDesc = statusDescVar.toString();
        QVariant statusColorVar = index.data(ItemStatusColor_Role);
        QColor statusColor = statusColorVar.value<QColor>();
        painter->save();
        if (!(option.state & QStyle::State_Selected) && statusColor.isValid())
        {
            painter->setPen(statusColor);
        }
        else
        {
            painter->setPen(option.palette.color(QPalette::WindowText));
        }
        painter->drawText(statusDescRect, Qt::AlignCenter, statusDesc);
        painter->restore();
    }

    //indicator
    if (option.state & QStyle::State_Selected)
    {
        QPixmap indicatorPixmap = style->standardPixmap(QStyle::SP_ArrowRight, &opt, widget);
        painter->drawPixmap(indicatorRect, indicatorPixmap);
    }

    painter->restore();
}

QPixmap KiranSiderbarDelegate::getDecorationPixmap(const QStyleOptionViewItem &option, const QModelIndex &index, QSize &pixmapSize) const
{
    QVariant decorationVar = index.data(Qt::DecorationRole);
    QPixmap pixmap;
    QStyle::State styleState = option.state;

    static const QSet<QVariant::Type> pixmapSet = {QVariant::Pixmap, QVariant::Image, QVariant::Icon};
    if (decorationVar.isValid() && !decorationVar.isNull() && pixmapSet.contains(decorationVar.type()))
    {
        switch (decorationVar.type())
        {
        case QVariant::Pixmap:
        {
            pixmap = qvariant_cast<QPixmap>(decorationVar);
            pixmapSize = pixmap.size() / pixmap.devicePixelRatio();
            break;
        }
        case QVariant::Image:
        {
            const QImage &image = qvariant_cast<QImage>(decorationVar);
            pixmap = QPixmap::fromImage(image);
            pixmapSize = image.size() / image.devicePixelRatio();
            break;
        }
        case QVariant::Icon:
        {
            QIcon::Mode mode = iconMode(styleState);
            QIcon::State state = iconState(styleState);
            QIcon icon = qvariant_cast<QIcon>(decorationVar);
            pixmapSize = icon.actualSize(option.decorationSize, mode, state);
            pixmap = icon.pixmap(pixmapSize, mode, state);
            break;
        }
        default:
            break;
        }
    }

    return pixmap;
}

//提取存储于model之中的数据进行本地转换
QString KiranSiderbarDelegate::textForRole(Qt::ItemDataRole role, const QVariant &value, const QLocale &locale) const
{
    static const int precision = 10;

    const QLocale::FormatType formatType = (role == Qt::DisplayRole) ? QLocale::ShortFormat : QLocale::LongFormat;
    QString text;
    switch (value.userType())
    {
    case QMetaType::Float:
        text = locale.toString(value.toFloat());
        break;
    case QVariant::Double:
        text = locale.toString(value.toDouble(), 'g', precision);
        break;
    case QVariant::Int:
    case QVariant::LongLong:
        text = locale.toString(value.toLongLong());
        break;
    case QVariant::UInt:
    case QVariant::ULongLong:
        text = locale.toString(value.toULongLong());
        break;
    case QVariant::Date:
        text = locale.toString(value.toDate(), formatType);
        break;
    case QVariant::Time:
        text = locale.toString(value.toTime(), formatType);
        break;
    case QVariant::DateTime:
        text = locale.toString(value.toDateTime(), formatType);
        break;
    default:
    {
        if (value.canConvert<QJsonValue>())
        {
            const QJsonValue val = value.toJsonValue();
            if (val.isBool())
                text = QVariant(val.toBool()).toString();
            else if (val.isDouble())
                text = locale.toString(val.toDouble(), 'g', precision);
            else if (val.isString())
                text = val.toString();
        }
        else
        {
            text = value.toString();
        }
        if (role == Qt::DisplayRole)
            text.replace(QLatin1Char('\n'), QChar::LineSeparator);
        break;
    }
    }
    return text;
}

QRect KiranSiderbarDelegate::textLayoutBounds(const QStyleOptionViewItem &option) const
{
    QRect rect = option.rect;
    const bool wrapText = option.features & QStyleOptionViewItem::WrapText;
    switch (option.decorationPosition)
    {
    case QStyleOptionViewItem::Left:
    case QStyleOptionViewItem::Right:
        rect.setWidth(wrapText && rect.isValid() ? rect.width() : (INT_MAX / 256));
        break;
    case QStyleOptionViewItem::Top:
    case QStyleOptionViewItem::Bottom:
        rect.setWidth(wrapText ? option.decorationSize.width() : (INT_MAX / 256));
        break;
    }
    return rect;
}

// NOTE:不考虑option之中decorationPosition、decorationAlignment、direction,以及不考虑不绘制勾选框
void KiranSiderbarDelegate::doLayout(const QStyleOptionViewItem &option, const QModelIndex &index,
                                      QRect &pixmapRect, QRect &textRect,
                                      QRect &statusDescRect, QRect &indicatorRect) const
{
    const QStyle::State &styleState = option.state;
    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();

    QSize pixmapSize, textSize, statusDescSize, indicatorSize;
    sizeFromContents(option, index, pixmapSize, textSize, statusDescSize, indicatorSize);

    QRect rect = option.rect.adjusted(10, 0, -10, 0);

    //最左
    QRect pixmapRectTemp = QRect(rect.x(), rect.y(), pixmapSize.width(), rect.height());
    pixmapRect.setSize(pixmapSize);
    pixmapRect.moveCenter(pixmapRectTemp.center());

    //最右
    QRect indicatorRectTemp = QRect(rect.right() - indicatorSize.width(), rect.y(), indicatorSize.width(), rect.height());
    indicatorRect.setSize(indicatorSize);
    indicatorRect.moveCenter(indicatorRectTemp.center());

    //状态描述文本靠右布局
    QRect statusDescRectTemp = QRect(indicatorRectTemp.left() - statusDescSize.width() - 10, rect.y(), statusDescSize.width(), rect.height());
    statusDescRect.setSize(statusDescSize);
    statusDescRect.moveCenter(statusDescRectTemp.center());

    //文本扩张
    int textSpaceX = pixmapSize.isEmpty() ? pixmapRectTemp.right() : pixmapRectTemp.right() + 10;
    int textSpaceWidth = statusDescRectTemp.left() - (statusDescSize.isEmpty() ? 0 : 10) - textSpaceX;
    QRect textRectTemp = QRect(textSpaceX, rect.y(), textSpaceWidth, rect.height());
    textRect.setSize(textSize);
    if (option.displayAlignment & Qt::AlignLeft)
    {
        textRect.moveCenter(textRectTemp.center());
        textRect.moveLeft(textRectTemp.left());
    }
    else
    {
        textRect.moveCenter(textRectTemp.center());
    }
}

QSize KiranSiderbarDelegate::sizeFromContents(const QStyleOptionViewItem &opt, const QModelIndex &idx,
                                              QSize &pixmapSize, QSize &textSize,
                                              QSize &statusDescSize, QSize &indicatorSize) const
{
    QVariant decorationVar = idx.data(Qt::DecorationRole);
    QVariant displayVar = idx.data(Qt::DisplayRole);
    QVariant statusDescVar = idx.data(ItemStatus_Role);

    pixmapSize = QSize(0, 0);
    getDecorationPixmap(opt, idx, pixmapSize);

    textSize = QSize(0, 0);
    if (displayVar.isValid() && !displayVar.isNull())
    {
        const QString text = textForRole(Qt::DisplayRole, displayVar, opt.locale);
        QVariant fontVar = idx.data(Qt::FontRole);
        QFont font = qvariant_cast<QFont>(fontVar).resolve(opt.font);
        QRect tempRect = textRectangle(0, textLayoutBounds(opt), font, text);
        textSize = tempRect.size();
    }

    statusDescSize = QSize(0, 0);
    if (statusDescVar.isValid() && !statusDescVar.isNull())
    {
        const QString text = statusDescVar.toString();
        QVariant fontVar = idx.data(Qt::FontRole);
        QFont font = qvariant_cast<QFont>(fontVar).resolve(opt.font);
        QRect tempRect = textRectangle(0, textLayoutBounds(opt), font, text);
        statusDescSize = tempRect.size();
    }

    indicatorSize = QSize(16, 16);

    QSize totalSize(20, 0);
    QList<QSize> itemsSize{pixmapSize, textSize, statusDescSize, indicatorSize};
    int itemCount = 0;
    for (QSize size : itemsSize)
    {
        if (size.isEmpty())
        {
            continue;
        }

        if (size.height() > totalSize.height())
            totalSize.rheight() = size.height();

        totalSize.rwidth() += size.width();
        itemCount++;
    }
    totalSize.rwidth() += (itemCount - 1) * 10;
    return totalSize;
}

void KiranSiderbarDelegate::setInvertIconPixelsEnable(bool enable)
{
    if( enable != m_invertIconPixelsEnable )
        m_invertIconPixelsEnable = enable;
}
