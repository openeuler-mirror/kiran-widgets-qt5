#ifndef KIRANTITLEBARWINDOW_H
#define KIRANTITLEBARWINDOW_H

#include <QWidget>

class QHBoxLayout;
class KiranTitlebarWindowPrivate;

///FIXME: @bug 移动窗口过后，窗体收不到鼠标悬浮事件,考虑窗口管理器引起
class Q_DECL_EXPORT KiranTitlebarWindow : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranTitlebarWindow)
    Q_DISABLE_COPY(KiranTitlebarWindow)
public:
    //标题栏按钮枚举
    enum TitlebarButtonHint {
        TitlebarMinimizeButtonHint = 0x00000001,
        TitlebarMaximizeButtonHint = 0x00000002,
        TitlebarCloseButtonHint = 0x00000004,
        TitlebarMinMaxCloseHints = TitlebarMinimizeButtonHint | TitlebarMaximizeButtonHint | TitlebarCloseButtonHint
    };
    Q_ENUM(TitlebarButtonHint)
    Q_DECLARE_FLAGS(TitlebarButtonHintFlags, TitlebarButtonHint)
    Q_FLAG(TitlebarButtonHintFlags)

    //样式表中提供设置窗口内容Margin
    Q_PROPERTY(int contentWrapperMarginLeft READ contentWrapperMarginLeft WRITE setContentWrapperMarginLeft)
    Q_PROPERTY(int contentWrapperMarginRight READ contentWrapperMarginRight WRITE setContentWrapperMarginRight)
    Q_PROPERTY(int contentWrapperMarginBottom READ contentWrapperMarginBottom WRITE setContentWrapperMarginBottom)
    Q_PROPERTY(bool compositingRunning READ compositingRunning)
public:
    explicit KiranTitlebarWindow();
    ~KiranTitlebarWindow();

    /// 设置内容窗口
    /// \param widget - 内容窗口
    void setWindowContentWidget(QWidget *widget);

    /// 获取窗口内容部件
    /// \return 窗口内容部件
    QWidget *getWindowContentWidget();

    /// 获取标题栏部分自定义布局，可自行添加控件
    /// \return 窗口内容部件布局
    QHBoxLayout *getTitlebarCustomLayout();

    /// 设置窗口图标
    /// \param icon - 图标
    void setIcon(const QIcon &icon);

    /// 设置标题栏
    /// \param text - 标题栏文本
    void setTitle(const QString &text);

    /// 设置标题栏按钮
    /// \param hints - 标题栏按钮flag
    void setButtonHints(TitlebarButtonHintFlags hints);

    /// 设置窗口是否允许改变大小
    /// \param resizeable - 是否可改变大小
    void setResizeable(bool resizeable);

    /// ContentWidget距底部边距
    /// \return 边距
    int contentWrapperMarginBottom() const;

     /// contentWidget距右边边距
     /// \return 边距
    int contentWrapperMarginRight() const;

    /// contentWidget距左边边距
    /// \return 边距
    int contentWrapperMarginLeft() const;


    /// 提供给样式表一个属性值，方便设置混成开关两种样式
    /// \return 混成是否开启
    bool compositingRunning() const;

public slots:
    /// 设置ContentWidget距底部边距
    /// \param margin - 边距
    void setContentWrapperMarginBottom(int margin);

    /// 设置ContentWidget距右部边距
    /// \param margin - 边距
    void setContentWrapperMarginRight(int margin);

    /// 设置ContentWidget距左部边距
    /// \param margin - 边距
    void setContentWrapperMarginLeft(int margin);

protected:
    bool event(QEvent *event) override;

private:
    KiranTitlebarWindowPrivate *d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KiranTitlebarWindow::TitlebarButtonHintFlags)

#endif // KIRANTITLEBARWINDOW_H
