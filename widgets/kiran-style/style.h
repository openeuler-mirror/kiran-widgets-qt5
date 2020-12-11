//
// Created by lxh on 2020/11/16.
//

#ifndef KIRANSTYLE_STYLE_H
#define KIRANSTYLE_STYLE_H

#include <QCommonStyle>
#include <QProxyStyle>
#include <QIcon>

#include "kiran-global-defines.h"
#include "style-data/style-detail-fetcher.h"

///TODO: 暂时不加入动画
///NOTE: 暂时不考虑支持QML
///NOTE: 不考虑高度是否能容下字体和和上下FrameOutline高度，只考虑样式统一!

typedef QHash<QStyle::StandardPixmap, QIcon> IconCache;

class QStyleAnimation;

namespace Kiran {
    using ParentStyleClass = QProxyStyle;

    class Style : public ParentStyleClass {
        Q_OBJECT
    public:
        explicit Style(StyleEnum type);
        ~Style();

        static bool isKiranStyle();
        static Style* castToKiranStyle();

        /// 使用给定的选项，使用提供的Painter绘制指定的原始元素
        void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt,
                           QPainter *p,const QWidget *w = nullptr) const override;

        void drawPrimitive(KiranPrimitiveElement pe, const QStyleOption *opt,
                           QPainter *p,const QWidget *w = nullptr) const;

        /// 通过使用给定的参数和Painter绘制元素
        void drawControl(ControlElement element, const QStyleOption *opt,
                         QPainter *p,const QWidget *w = nullptr) const override;

        void drawControl(KiranControlElement ce, const QStyleOption *opt,
                         QPainter *p, const QWidget *w = nullptr) const;

        /// 通过给定的类型和参数绘制复杂控件
        void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                QPainter *p,const QWidget *w = nullptr) const override;

        /// 返回给定子元素枚举的区域
        QRect subElementRect(SubElement se, const QStyleOption *opt,
                             const QWidget *widget = nullptr) const override;

        QRect subElementRect(KiranSubElement se,const QStyleOption *opt,
                             const QWidget *widget = nullptr) const;

        /// 返回给定复杂控件中给定位置的子控件（带有由option指定的样式选项）。
        SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                         const QPoint &pt,const QWidget *w = nullptr) const override;

        /// 获取指定复杂控件中的指定子控件的位置
        QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt,
                             SubControl sc,const QWidget *w = nullptr) const override;

        /// 通过内容大小和参数获取指定控件的大小
        QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                               const QSize &contentsSize,const QWidget *widget = nullptr) const override;

        QSize sizeFromContents(KiranContentsType ct,const QStyleOption *opt,
                               const QSize &contentsSize,const QWidget *widget = nullptr) const;

        /// 像素度量,返回给定像素指标的值
        int pixelMetric(PixelMetric metric, const QStyleOption *opt = nullptr,
                        const QWidget *widget = nullptr) const override;

        /// 返回一个整数，该整数表示由提供的样式选项描述的给定窗口小部件的指定样式提示。
        int styleHint(StyleHint sh, const QStyleOption *opt = nullptr, const QWidget *w = nullptr,
                      QStyleHintReturn *shret = nullptr) const override;

        /// 获取给定的标准图标
        QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = nullptr,
                           const QWidget *widget = nullptr) const override;
        QIcon titleBarButtonIcon(StyleDetailFetcher* fetcher,StandardPixmap standardIcon,
                                 const QStyleOption *opt = nullptr,const QWidget *widget = nullptr) const;
        QIcon toolBarExtensionIcon(StandardPixmap standardIcon, const QStyleOption *opt = nullptr,
                                 const QWidget *widget = nullptr) const;

        /// 根据调色板的样式特定要求更改调色板
        void polish(QPalette &p) override;

        /// 初始化整个应用程序的外观
        void polish(QApplication *app) override;

        /// 初始化窗口小部件的外观
        void polish(QWidget *widget) override;

        /// 取消初始化窗口小控件的外观
        void unpolish(QWidget *widget) override;

        /// 取消初始化整个程序
        void unpolish(QApplication *application) override;

    public:
        QList<const QObject*> animationTargets() const;
        QStyleAnimation* animation(const QObject *target) const;
        void startAnimation(QStyleAnimation *animation) const;
        void stopAnimation(const QObject *target) const;

    public Q_SLOTS:
        void removeAnimation();

    private:
        StyleEnum m_styleType;
        StyleDetailFetcher *m_detailFetcher;
        IconCache m_iconCache;
        mutable QHash<const QObject*, QStyleAnimation*> animations;
    };
}

#endif //KIRANSTYLE_STYLE_H
