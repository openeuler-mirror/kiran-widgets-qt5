/*
 * @file   kiran-message-box.h
 * @brief  Kiran消息对话框
 * @author liuxinhao <liuxinhao@kylinos.com.cn>
 * @copyright (c) 2020 KylinSec. All rights reserved.
 */
 
#ifndef KIRANMESSAGEBOX_H
#define KIRANMESSAGEBOX_H

#include <QDialog>
#include <QDialogButtonBox>

class KiranMessageBoxPrivate;
class QAbstractButton;

/**
 * @brief Kiran封装消息对话框
 * @since kiranwidgets-qt5-2.0.0
 */
class Q_DECL_EXPORT KiranMessageBox : public QDialog {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranMessageBox)
    Q_DISABLE_COPY(KiranMessageBox)
    Q_PROPERTY(QSize buttonSize READ buttonSize WRITE setButtonSize)
public:
    ///定义了一些标准类型的按钮，提供给使用public static方法来快捷创建消息框
    ///没直接使用QDialogButtonBox中的StandarButton
    ///因为QDialogButtonBox中的Button翻译问题需要解决，也需要解决按钮不同样式
    enum KiranStandardButton {
        NoButton = 0x00000000,
        Ok = 0x00000400,
        Save = 0x00000800,
        SaveAll = 0x00001000,
        Open = 0x00002000,
        Yes = 0x00004000,
        YesToAll = 0x00008000,
        No = 0x00010000,
        NoToAll = 0x00020000,
        Abort = 0x00040000,
        Retry = 0x00080000,
        Ignore = 0x00100000,
        Close = 0x00200000,
        Cancel = 0x00400000,
        Discard = 0x00800000,
        Help = 0x01000000,
        Apply = 0x02000000,
        Reset = 0x04000000,
        RestoreDefaults = 0x08000000
    };
    Q_ENUM(KiranStandardButton)
    Q_DECLARE_FLAGS(KiranStandardButtons, KiranStandardButton)
    Q_FLAG(KiranStandardButtons)

public:
    explicit KiranMessageBox(QWidget *parent = nullptr);
    ~KiranMessageBox();

    /// 创建消息对话框
    /// \param parent   -   指定显示在哪个窗口中央，置null则为当前屏幕中央
    /// \param title    -   标题
    /// \param text     -   显示内容
    /// \param buttons  -   显示的按钮
    /// \return 用户点击的按钮
    static KiranStandardButton message(QWidget *parent,
                                       const QString &title,
                                       const QString &text,
                                       KiranStandardButtons buttons);

    /// 设置窗口标题
    /// \param title - 标题
    void setTitle(const QString &title);

    /// 设置窗口显示内容
    /// \param text - 内容
    void setText(const QString &text);

    /// 添加按钮
    /// \param button - 按钮
    /// \param role   - 按钮作用
    void addButton(QPushButton *button,QDialogButtonBox::ButtonRole role);

    /// 移除按钮
    /// \param button - 按钮
    void removeButton(QPushButton *button);

    /// 移除所有的按钮
    /// \param button - 按钮
    void cleanButton(QPushButton *button);

    /// 按钮的大小
    /// \return 按钮大小
    QSize buttonSize();

    /// 设置按钮大小
    /// \param size - 按钮大小
    void setButtonSize(const QSize &size);

    /// 获取用户点击的按钮
    /// \return 按钮
    QPushButton *clickedButton();

protected:
    bool event(QEvent *event) override;

private:
    KiranMessageBoxPrivate *d_ptr;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(KiranMessageBox::KiranStandardButtons)

#endif // KIRANMESSAGEBOX_H
