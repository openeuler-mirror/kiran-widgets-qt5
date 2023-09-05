/**
 * Copyright (c) 2020 ~ 2022 KylinSec Co., Ltd.
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

#include "kiran-label.h"
#include "kiran-label-private.h"

#include <private/qlabel_p.h>
#include <private/qstylesheetstyle_p.h>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>

KiranLabelPrivate::KiranLabelPrivate(KiranLabel *ptr, QObject *parent)
    : QObject(parent),
      q_ptr(ptr)
{
}

KiranLabelPrivate::~KiranLabelPrivate()
{
}

void KiranLabelPrivate::init()
{
}

Qt::LayoutDirection KiranLabelPrivate::textDirection(QLabelPrivate *ld)
{
    if (ld->control)
    {
        QTextOption opt = ld->control->document()->defaultTextOption();
        return opt.textDirection();
    }

    return ld->text.isRightToLeft() ? Qt::RightToLeft : Qt::LeftToRight;
}

QRectF KiranLabelPrivate::layoutRect(QLabelPrivate *ld)
{
    QRectF cr = documentRect(ld);
    if (!ld->control)
        return cr;
    ensureTextLayouted(ld);
    // Caculate y position manually
    qreal rh = ld->control->document()->documentLayout()->documentSize().height();
    qreal yo = 0;
    if (ld->align & Qt::AlignVCenter)
        yo = qMax((cr.height() - rh) / 2, qreal(0));
    else if (ld->align & Qt::AlignBottom)
        yo = qMax(cr.height() - rh, qreal(0));
    return QRectF(cr.x(), yo + cr.y(), cr.width(), cr.height());
}

QRectF KiranLabelPrivate::documentRect(QLabelPrivate *ld)
{
    QLabel *q = qobject_cast<QLabel *>(ld->q_ptr);
    Q_ASSERT_X(ld->isTextLabel, "documentRect", "document rect called for label that is not a text label!");
    QRect cr = q->contentsRect();
    cr.adjust(ld->margin, ld->margin, -ld->margin, -ld->margin);
    const int align = QStyle::visualAlignment(ld->isTextLabel ? textDirection(ld)
                                                              : q->layoutDirection(),
                                              QFlag(ld->align));
    int m = ld->indent;
    if (m < 0 && q->frameWidth())  // no indent, but we do have a frame
#if (QT_VERSION >= QT_VERSION_CHECK(5, 11, 0))
        m = q->fontMetrics().horizontalAdvance(QLatin1Char('x')) / 2 - ld->margin;
#else
         m = q->fontMetrics().width(QLatin1Char('x')) / 2 - ld->margin;
#endif
    if (m > 0)
    {
        if (align & Qt::AlignLeft)
            cr.setLeft(cr.left() + m);
        if (align & Qt::AlignRight)
            cr.setRight(cr.right() - m);
        if (align & Qt::AlignTop)
            cr.setTop(cr.top() + m);
        if (align & Qt::AlignBottom)
            cr.setBottom(cr.bottom() - m);
    }
    return cr;
}

void KiranLabelPrivate::ensureTextLayouted(QLabelPrivate *ld)
{
    if (ld->textLayoutDirty)
    {
        if (ld->textDirty)
        {
            if (ld->control)
            {
                QTextDocument *doc = ld->control->document();
                if (ld->textDirty)
                {
#ifndef QT_NO_TEXTHTMLPARSER
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
                    if (ld->textformat == Qt::TextFormat::RichText)
#else
                    if (ld->isRichText)
#endif
                        doc->setHtml(ld->text);
                    else
                        doc->setPlainText(ld->text);
#else
                    doc->setPlainText(ld->text);
#endif
                    doc->setUndoRedoEnabled(false);

#ifndef QT_NO_SHORTCUT
                    if (ld->hasShortcut)
                    {
                        // Underline the first character that follows an ampersand (and remove the others ampersands)
                        int from = 0;
                        bool found = false;
                        QTextCursor cursor;
                        while (!(cursor = ld->control->document()->find((QLatin1String("&")), from)).isNull())
                        {
                            cursor.deleteChar();  // remove the ampersand
                            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                            from = cursor.position();
                            if (!found && cursor.selectedText() != QLatin1String("&"))
                            {  // not a second &
                                found = true;
                                ld->shortcutCursor = cursor;
                            }
                        }
                    }
#endif
                }
            }
            ld->textDirty = false;
        }

        if (ld->control)
        {
            QTextDocument *doc = ld->control->document();
            QTextOption opt = doc->defaultTextOption();

            opt.setAlignment(QFlag(ld->align));

            if (ld->align & Qt::TextWordWrap)
                opt.setWrapMode(QTextOption::WordWrap);
            else
                opt.setWrapMode(QTextOption::ManualWrap);

            doc->setDefaultTextOption(opt);

            QTextFrameFormat fmt = doc->rootFrame()->frameFormat();
            fmt.setMargin(0);
            doc->rootFrame()->setFrameFormat(fmt);
            doc->setTextWidth(documentRect(ld).width());
        }
        ld->textLayoutDirty = false;
    }
}

KiranLabel::KiranLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f),
      kiran_d_ptr(new KiranLabelPrivate(this))
{
    kiran_d_ptr->init();
}

KiranLabel::KiranLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text,parent, f),
      kiran_d_ptr(new KiranLabelPrivate(this))
{
    kiran_d_ptr->init();
}

KiranLabel::~KiranLabel()
{
    delete kiran_d_ptr;
}

void KiranLabel::setElideMode(Qt::TextElideMode elideMode)
{
    if (KiranLabel::elideMode() == elideMode)
    {
        return;
    }

    kiran_d_ptr->elideMode = elideMode;
    update();
}

Qt::TextElideMode KiranLabel::elideMode() const
{
    return kiran_d_ptr->elideMode;
}

/// @brief 从QLabel::paintEvent修改而来,将QLabelPrivate相关方法(由于未暴露符号)移动至KiranLabelPrivate之中
void KiranLabel::paintEvent(QPaintEvent *event)
{
    QLabelPrivate *d = static_cast<QLabelPrivate *>(d_ptr.data());
    QStyle *style = QWidget::style();

    QPainter p(this);

    drawFrame(&p);

    QRect cr = contentsRect();
    cr.adjust(d->margin, d->margin, d->margin, d->margin);
    int align = QStyle::visualAlignment(d->isTextLabel ? KiranLabelPrivate::textDirection(d) : layoutDirection(), QFlag(d->align));

#if QT_CONFIG(movie)
    if (d->movie && !d->movie->currentPixmap().isNull())
    {
        if (d->scaledcontents)
            style->drawItemPixmap(&p, cr, align, d->movie->currentPixmap().scaled(cr.size()));
        else
            style->drawItemPixmap(&p, cr, align, d->movie->currentPixmap());
    }
    else
#endif
        if (d->isTextLabel)
    {
        QRectF lr = KiranLabelPrivate::layoutRect(d).toAlignedRect();
        QStyleOption opt;
        opt.initFrom(this);

        if (d->control)
        {
#ifndef QT_NO_SHORTCUT
            const bool underline = static_cast<bool>(style->styleHint(QStyle::SH_UnderlineShortcut,
                                                                      nullptr, this, nullptr));
            if (d->shortcutId != 0 && underline != d->shortcutCursor.charFormat().fontUnderline())
            {
                QTextCharFormat fmt;
                fmt.setFontUnderline(underline);
                d->shortcutCursor.mergeCharFormat(fmt);
            }
#endif
            KiranLabelPrivate::ensureTextLayouted(d);

            QAbstractTextDocumentLayout::PaintContext context;
            // Adjust the palette
            context.palette = opt.palette;

            if (foregroundRole() != QPalette::Text && isEnabled())
                context.palette.setColor(QPalette::Text, context.palette.color(foregroundRole()));

            p.save();
            p.translate(lr.topLeft());
            p.setClipRect(lr.translated(-lr.x(), -lr.y()));
            d->control->setPalette(context.palette);
            d->control->drawContents(&p, QRectF(), this);
            p.restore();
        }
        else
        {
            int flags = align | (KiranLabelPrivate::textDirection(d) == Qt::LeftToRight ? Qt::TextForceLeftToRight
                                                                                        : Qt::TextForceRightToLeft);
            if (d->hasShortcut)
            {
                flags |= Qt::TextShowMnemonic;
                if (!style->styleHint(QStyle::SH_UnderlineShortcut, &opt, this))
                    flags |= Qt::TextHideMnemonic;
            }

            QString elideText = d->text;
            if (kiran_d_ptr->elideMode != Qt::ElideNone)
            {
                const QFontMetrics fm(fontMetrics());
                elideText = fm.elidedText(elideText, elideMode(), width(), Qt::TextShowMnemonic);
            }

            style->drawItemText(&p, lr.toRect(), flags, opt.palette, isEnabled(), elideText, foregroundRole());
        }
    }
    else
#ifndef QT_NO_PICTURE
        if (d->picture)
    {
        QRect br = d->picture->boundingRect();
        int rw = br.width();
        int rh = br.height();
        if (d->scaledcontents)
        {
            p.save();
            p.translate(cr.x(), cr.y());
            p.scale((double)cr.width() / rw, (double)cr.height() / rh);
            p.drawPicture(-br.x(), -br.y(), *d->picture);
            p.restore();
        }
        else
        {
            int xo = 0;
            int yo = 0;
            if (align & Qt::AlignVCenter)
                yo = (cr.height() - rh) / 2;
            else if (align & Qt::AlignBottom)
                yo = cr.height() - rh;
            if (align & Qt::AlignRight)
                xo = cr.width() - rw;
            else if (align & Qt::AlignHCenter)
                xo = (cr.width() - rw) / 2;
            p.drawPicture(cr.x() + xo - br.x(), cr.y() + yo - br.y(), *d->picture);
        }
    }
    else
#endif
        if (d->pixmap && !d->pixmap->isNull())
    {
        QPixmap pix;
        if (d->scaledcontents)
        {
            QSize scaledSize = cr.size() * devicePixelRatioF();
            if (!d->scaledpixmap || d->scaledpixmap->size() != scaledSize)
            {
                if (!d->cachedimage)
                    d->cachedimage = new QImage(d->pixmap->toImage());
                delete d->scaledpixmap;
                QImage scaledImage =
                    d->cachedimage->scaled(scaledSize,
                                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                d->scaledpixmap = new QPixmap(QPixmap::fromImage(std::move(scaledImage)));
                d->scaledpixmap->setDevicePixelRatio(devicePixelRatioF());
            }
            pix = *d->scaledpixmap;
        }
        else
            pix = *d->pixmap;
        QStyleOption opt;
        opt.initFrom(this);
        if (!isEnabled())
            pix = style->generatedIconPixmap(QIcon::Disabled, pix, &opt);
        style->drawItemPixmap(&p, cr, align, pix);
    }
}