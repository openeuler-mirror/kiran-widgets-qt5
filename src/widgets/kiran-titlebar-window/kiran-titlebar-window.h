/**
 * Copyright (c) 2020 ~ 2021 KylinSec Co., Ltd. 
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
#ifndef KIRANTITLEBARWINDOW_H
#define KIRANTITLEBARWINDOW_H

#include <QWidget>

class QHBoxLayout;
class KiranTitlebarWindowPrivate;

/**
 * @brief 自定义标题栏窗口
 * <img src="../snapshot/kiran-switch-button.png" alt="kiran-switch-button" style="zoom:90%;" />
 * @bug 移动窗口过后，窗体收不到鼠标悬浮事件,考虑窗口管理器引起
 * @since 2.0.0
 */

class Q_DECL_EXPORT KiranTitlebarWindow : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranTitlebarWindow)
    Q_DISABLE_COPY(KiranTitlebarWindow)
public:
    /**
     * @brief 标题栏按钮选项
     */
    enum TitlebarButtonHint {
        TitlebarMinimizeButtonHint = 0x00000001,/** < 最小化 */
        TitlebarMaximizeButtonHint = 0x00000002,/** < 最大化 */
        TitlebarCloseButtonHint = 0x00000004,   /** < 关闭 */
        TitlebarMinMaxCloseHints = TitlebarMinimizeButtonHint | TitlebarMaximizeButtonHint | TitlebarCloseButtonHint /** < 最小化,最大化,关闭 */
    };
    Q_ENUM(TitlebarButtonHint)
    Q_DECLARE_FLAGS(TitlebarButtonHintFlags, TitlebarButtonHint)
    Q_FLAG(TitlebarButtonHintFlags)

    /* 样式表中提供设置窗口内容Margin */
    Q_PROPERTY(int contentWrapperMarginLeft READ contentWrapperMarginLeft WRITE setContentWrapperMarginLeft)
    Q_PROPERTY(int contentWrapperMarginRight READ contentWrapperMarginRight WRITE setContentWrapperMarginRight)
    Q_PROPERTY(int contentWrapperMarginBottom READ contentWrapperMarginBottom WRITE setContentWrapperMarginBottom)
    Q_PROPERTY(bool compositingRunning READ compositingRunning)

public:
    /**
     * @brief KiranTitlebarWindow构造方法
     * @deprecated 3.0.0之后该接口将被废弃
     */
    Q_DECL_DEPRECATED explicit KiranTitlebarWindow();

    /**
     * @brief KiranTitlebarWindow构造方法
     * 考虑之前版本的兼容问题，暂时父控件不为默认构造
     * @param parent      父控件
     * @param windowFlags window标志
     * @since 2.1.0
     * @see QWidget::QWidget(QWidget*, Qt::WindowFlags)
     */
    explicit KiranTitlebarWindow(QWidget *parent, Qt::WindowFlags windowFlags=Qt::Window);

    /**
     * @brief KiranTitlebarWindow析构方法
     */
    ~KiranTitlebarWindow();

    /**
     * @brief 设置自定义标题栏的内容窗口
     * @param widget 需要设置的内容窗口
     */
    void setWindowContentWidget(QWidget *widget);

    /**
     * @brief  获取窗口内容部件
     * @return 窗口内容部件
     */
    QWidget *getWindowContentWidget();

    /**
     * @brief  获取标题栏部分自定义布局，可自行添加控件至标题栏
     * @return 窗口内容部件布局
     */
    QHBoxLayout *getTitlebarCustomLayout();

    /**
     * @brief 获取标题栏部分自定义控件区域是否居中
     * @return 标题栏自定义控件区域是否居中
     */
    bool titlebarCustomLayoutAlignHCenter();

    /**
     * @brief 设置标题栏自定义控件区域是否居中
     * @param center 自定义控件区域是否居中
     */
    void setTitlebarCustomLayoutAlignHCenter(bool center);

    /**
     * @brief 设置窗口图标
     * @param icon 窗口图标
     */
    void setIcon(const QIcon &icon);

    /**
     * @brief 设置标题栏
     * @param text 标题栏文本
     */
    void setTitle(const QString &text);

    /**
     * @brief 设置标题栏按钮
     * @param hints 标题栏按钮flag
     */
    void setButtonHints(TitlebarButtonHintFlags hints);

    /**
     * @brief 设置窗口是否允许改变大小
     * @param resizeable 是否可改变大小
     */
    void setResizeable(bool resizeable);

    /**
     * @brief 内容窗口距底部边距
     * @return 边距
     */
    int contentWrapperMarginBottom() const;

     /**
      * @brief 内容窗口距右边边距
      * @return 边距
      */
    int contentWrapperMarginRight() const;

    /**
     * @brief 内容窗口距左边边距
     * @return 边距
     */
    int contentWrapperMarginLeft() const;

    /**
      * 初始化时缓存QX11Info::isCompositingManagerRunning的值
      * 提供给样式表一个属性值，方便设置混成开关两种样式
      */
    Q_DECL_DEPRECATED bool compositingRunning() const;

    QSize sizeHint() const override;

    void setTitleBarHeight(int height);

    int  titleBarHeight();

    /**
     * 获取窗口透明边框的宽度
     */
    int transparentWidth();

    void setTitlebarColorBlockEnable(bool enable);
    bool getTitlebarColorBlockEnable();
public slots:
    /**
     * @brief 设置内容窗口距底部边距
     * @param margin 边距
     */
    void setContentWrapperMarginBottom(int margin);

    /**
     * @brief 设置内容窗口距右边边距
     * @param margin 边距
     */
    void setContentWrapperMarginRight(int margin);

    /**
     * @brief 设置内容窗口距左边距
     * @param margin 边距
     */
    void setContentWrapperMarginLeft(int margin);

protected:
    /* 事件处理 */
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    /* KiranTitlebarWindow私有类指针 */
    KiranTitlebarWindowPrivate *d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KiranTitlebarWindow::TitlebarButtonHintFlags)

#endif // KIRANTITLEBARWINDOW_H
