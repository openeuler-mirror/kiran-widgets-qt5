/*
 * @file   style.h
 * @brief  Style的相关实现
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */

#ifndef KIRANSTYLE_STYLE_H
#define KIRANSTYLE_STYLE_H

#include <QCommonStyle>
#include <QProxyStyle>
#include <QIcon>

#include "kiran-style-private-defines.h"
#include "kiran-style-public-define.h"
#include "style-detail-fetcher.h"

typedef QHash<QStyle::StandardPixmap, QIcon> IconCache;
class QStyleAnimation;

namespace Kiran {
    using ParentStyleClass = QProxyStyle;
    class Style : public ParentStyleClass {
        Q_OBJECT
    public:
        explicit Style(StyleEnum type);
        ~Style();

        /**
         * @brief  判断当前QApplication的Style是否是KiranStyle
         * @return 当前Style是否是KiranStyle
         */
        static bool isKiranStyle();

        /**
         * @brief  便利的将QApplication::style转换成KiranStyle的方法
         * @return KiranStyle指针，如果当前Style不是KiranStyle返回nullptr
         */
        static Style* castToKiranStyle();

        /**
         * @brief 使用给定的样式选项绘制Qt原始的控件元素
         * @param pe    原始控件类型
         * @param opt   样式选项
         * @param p     QPainter指针，使用该Painter进行绘制
         * @param w     相关控件指针
         */
        void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt,
                           QPainter *p,const QWidget *w = nullptr) const override;

        /**
         * @brief 使用给定的样式选项绘制Kiran自定义的控件元素
         * @param pe   原始控件类型
         * @param opt  样式选项
         * @param p    QPainter指针，使用该Painter进行绘制
         * @param w    相关控件指针
         */
        void drawPrimitive(KiranPrimitiveElement pe, const QStyleOption *opt,
                           QPainter *p,const QWidget *w = nullptr) const;

        /**
         * @brief 使用给定样式选项绘制Qt控件
         * @param element  绘制的控件类型
         * @param opt      样式选项
         * @param p        QPainter指针，使用该Painter进行绘制
         * @param w        相关控件指针
         */
        void drawControl(ControlElement element, const QStyleOption *opt,
                         QPainter *p,const QWidget *w = nullptr) const override;

        /**
         * @brief 使用给定样式选项绘制Kiran控件
         * @param ce    绘制的控件类型
         * @param opt   样式选项
         * @param p     QPainter指针，使用该Painter进行绘制
         * @param w     相关控件指针
         */
        void drawControl(KiranControlElement ce, const QStyleOption *opt,
                         QPainter *p, const QWidget *w = nullptr) const;

        /**
         * @brief 使用给定样式选项绘制复杂控件
         * @param cc   绘制的复杂控件类型
         * @param opt  样式选项
         * @param p    QPainter指针，使用该Painter进行绘制
         * @param w    相关控件指针
         */
        void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                QPainter *p,const QWidget *w = nullptr) const override;

        /**
         * @brief 返回给定子元素类型的绘制区域
         * @param se      子元素类型
         * @param opt     样式选项
         * @param widget  相关控件指针
         * @return 子元素应在的区域
         */
        QRect subElementRect(SubElement se, const QStyleOption *opt,
                             const QWidget *widget = nullptr) const override;

        /**
         * @brief 返回给定Kiran子元素类型的绘制区域
         * @param se      子元素类型
         * @param opt     样式选项
         * @param widget  相关控件指针
         * @return 子元素应在的区域
         */
        QRect subElementRect(KiranSubElement se,const QStyleOption *opt,
                             const QWidget *widget = nullptr) const;

        /**
         * @brief 返回给定复杂控件中给定位置的子控件（带有由option指定的样式选项）
         * @param cc     复杂控件
         * @param opt    样式选项
         * @param pt     指定的位置
         * @param w      相关控件指针
         * @return 指定位置的子控件
         */
        SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                         const QPoint &pt,const QWidget *w = nullptr) const override;

        /**
         * @brief 获取指定复杂控件中的指定子控件的位置
         * @param cc    复杂控件类型
         * @param opt   样式选项
         * @param sc    子控件类型
         * @param w     相关控件指针
         * @return 子控件在复杂控件中的区域
         */
        QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt,
                             SubControl sc,const QWidget *w = nullptr) const override;

        /**
         * @brief 通过内容大小和参数获取指定控件的大小,通常在控件的sizeHint方法中使用
         * @param ct            控件类型
         * @param opt           样式选项
         * @param contentsSize  内容大小
         * @param widget        相关控件指针
         * @return 控件应有的大小
         */
        QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                               const QSize &contentsSize,const QWidget *widget = nullptr) const override;

        /**
         * @brief 通过内容大小和参数获取指定Kiran控件的大小,通常在控件的sizeHint方法中使用
         * @param ct            Kiran控件类型
         * @param opt           样式选项
         * @param contentsSize  内容大小
         * @param widget 窗口
         * @return  控件应有的大小
         */
        QSize sizeFromContents(KiranContentsType ct,const QStyleOption *opt,
                               const QSize &contentsSize,const QWidget *widget = nullptr) const;

        /**
         * @brief 像素度量,返回给定像素指标的值,Style插件中用于获取类似边框宽度等细节值
         * @param metric     度量类型
         * @param opt        绘制选项
         * @param widget     相关控件指针
         * @return　该有的像素值
         */
        int pixelMetric(PixelMetric metric, const QStyleOption *opt = nullptr,
                        const QWidget *widget = nullptr) const override;

        int pixelMetric(KiranPixelMetric metric, const QStyleOption *opt = nullptr,
                        const QWidget *wodget = nullptr) const;

        /**
         * @brief 返回一个整数，该整数表示由提供的样式选项描述的给定窗口小部件的指定样式提示
         * @param sh      样式提示枚举
         * @param opt     样式选项
         * @param w       相关控件指针
         * @param shret   返回给调用者的样式提示
         * @return 需根据不同的类型进行判断，可能是整数值的样式提示，可能是Bool表示调用成功与否
         */
        int styleHint(StyleHint sh, const QStyleOption *opt = nullptr, const QWidget *w = nullptr,
                      QStyleHintReturn *shret = nullptr) const override;

        /**
         * @brief 获取给定的标准图标
         * @param standardIcon 标准图标类型枚举
         * @param opt          样式选项
         * @param widget       相关控件指针
         * @return 图标
         */
        QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = nullptr,
                           const QWidget *widget = nullptr) const override;

        /**
         * @brief 绘制生成用于TitleBar的图标
         * @param fetcher       绘制细节获取
         * @param standardIcon  标准图标类型
         * @param opt           样式选项
         * @param widget        相关控件指针
         * @return
         */
        QIcon titleBarButtonIcon(StyleDetailFetcher* fetcher,StandardPixmap standardIcon,
                                 const QStyleOption *opt = nullptr,const QWidget *widget = nullptr) const;

        /**
         * @brief 对调色板进行初始化
         * @param p
         */
        void polish(QPalette &p) override;

        /**
         * @brief 初始化整个应用程序的外观
         * @param app 待初始化的Application
         */
        void polish(QApplication *app) override;

        /**
         * @brief 初始化控件的外观,在其中设置控件属性或注册动画等
         * @param widget 相关控件指针
         */
        void polish(QWidget *widget) override;

        /**
         * @brief 取消控件的初始化,用于的Style::Polish(Qwidget*)所设置的属性或需要释放的空间等
         * @param widget 相关控件指针
         */
        void unpolish(QWidget *widget) override;

        /**
         * @brief 取消Application的初始化,用于的Style::Polish(QApplication*)所设置的属性或需要释放的空间等
         * @param application 相关Application的指针
         */
        void unpolish(QApplication *application) override;

    public:
        /**
         * @brief  获取动画的目标控件列表
         * @return 动画的目标控件列表
         */
        QList<const QObject*> animationTargets() const;

        /**
         * @brief 获取指定目标控件的动画
         * @param target 指定的目标控件
         * @return 动画指针
         */
        QStyleAnimation* animation(const QObject *target) const;

        /**
         * @brief 开始动画，加入到Style中的动画Hash表，连接信号槽，当被销毁移除出Hash表
         * @param animation 动画指针
         */
        void startAnimation(QStyleAnimation *animation) const;

        /**
         * @brief 停止目标控件动画,并从Hash表中移除该动画
         * @param target 目标控件
         */
        void stopAnimation(const QObject *target) const;

    public Q_SLOTS:
        /* 动画销毁的槽函数，删除该动画在Hash中的项 */
        void removeAnimation();

    protected:
        /* 判断控件类型是否属于KiranSidebarWidget */
        bool isKiranSidebarWidget(const QWidget* widget) const;

    private:
        StyleEnum m_styleType;
        StyleDetailFetcher *m_detailFetcher;
        IconCache m_iconCache;
        mutable QHash<const QObject*, QStyleAnimation*> animations;
    };
}

#endif //KIRANSTYLE_STYLE_H
