#ifndef KIRANTITLEBARWINDOW_H
#define KIRANTITLEBARWINDOW_H

#include <QWidget>

class QHBoxLayout;
class KiranTitlebarWindowPrivate;
Q_DECLARE_METATYPE(QMargins)
class Q_DECL_EXPORT KiranTitlebarWindow : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranTitlebarWindow)
    Q_DISABLE_COPY(KiranTitlebarWindow)
public:
    ///@brief 标题栏按钮枚举
    enum TitlebarButtonHint{
        TitlebarMinimizeButtonHint = 0x00000001,
        TitlebarMaximizeButtonHint = 0x00000002,
        TitlebarCloseButtonHint = 0x00000004,
        TitlebarMinMaxCloseHints = TitlebarMinimizeButtonHint|TitlebarMaximizeButtonHint|TitlebarCloseButtonHint
    };
    Q_ENUM(TitlebarButtonHint)
    Q_DECLARE_FLAGS(TitlebarButtonHintFlags, TitlebarButtonHint)
    Q_FLAG(TitlebarButtonHintFlags)

    ///样式表中提供设置窗口内容Margin
    Q_PROPERTY(int contentWrapperMarginLeft READ contentWrapperMarginLeft WRITE setContentWrapperMarginLeft)
    Q_PROPERTY(int contentWrapperMarginRight READ contentWrapperMarginRight WRITE setContentWrapperMarginRight)
    Q_PROPERTY(int contentWrapperMarginBottom READ contentWrapperMarginBottom WRITE setContentWrapperMarginBottom)
    Q_PROPERTY(bool compositingRunning READ compositingRunning)
public:
    explicit KiranTitlebarWindow();
    ~KiranTitlebarWindow();

    /**
     * @brief 设置窗口内容部件，该操作会释放之前的内容窗口，会setParent当前窗口
     * @param 窗口内容部件
     */
    void setWindowContentWidget(QWidget* widget);

    /**
     * @brief  获取窗口内容部件
     * @return 窗口内容部件
     */
    QWidget* getWindowContentWidget();

    /**
     * @brief 获取标题栏自定义布局，可自行添加控件
     * @return 窗口内容部件布局
     */
    QHBoxLayout* getTitleBarCustomLayout();

    /**
     * @brief 设置窗口图标
     * @param 图标
     */
    void setIcon(const QIcon& icon);

    /**
     * @brief 设置标题栏
     * @param 标题
     */
    void setTitle(const QString& text);

    /**
     * @brief 设置标题栏按钮
     * @param 标题栏按钮flag
     */
    void setButtonsHint(TitlebarButtonHintFlags hints);

    /**
     * @brief 设置窗口是否允许改变大小
     * @param 是否允许改变大小
     */
    void setResizeable(bool resizeable);

    /**
     * @brief  窗口内容窗口距底部边距
     * @return 边距
     */
    int contentWrapperMarginBottom() const;

    /**
     * @brief  窗口内容窗口距右边边距
     * @return 边距
     */
    int contentWrapperMarginRight() const;

    /**
     * @brief  窗口内容窗口距左边边距
     * @return 边距
     */
    int contentWrapperMarginLeft() const;

    /**
     * @brief  提供给样式表一个属性值，混成开关两种样式
     * @return 混成是否开启
     */
    bool compositingRunning() const;

public slots:
    void setContentWrapperMarginBottom(int contentWrapperMarginBottom);
    void setContentWrapperMarginRight(int contentWrapperMarginRight);
    void setContentWrapperMarginLeft(int contentWrapperMarginLeft);

private:
    /**
     * @brief 初始化连接关键信号槽
     */
    void initConnect();

protected:
    /**
     * @brief 窗口事件获取，交由私有类处理
     */
    bool event(QEvent *event) override;

private:
    KiranTitlebarWindowPrivate* d_ptr;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(KiranTitlebarWindow::TitlebarButtonHintFlags)
#endif // KIRANTITLEBARWINDOW_H
