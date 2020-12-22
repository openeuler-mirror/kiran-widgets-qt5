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
 * @brief 基于QDialog封装的消息对话框
 * <img src="../snapshot/kiran-message-box.png" alt="kiran-message-box.png" style="zoom:90%;" />
 * @since 2.0.0
 */
class Q_DECL_EXPORT KiranMessageBox : public QDialog {
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranMessageBox)
    Q_DISABLE_COPY(KiranMessageBox)
    Q_PROPERTY(QSize buttonSize READ buttonSize WRITE setButtonSize)

public:
     /**
      * @brief 标准类型的按钮枚举
      * @see 　QDialogButtonBox::StandardButton
      * @note 定义了一些按钮类型枚举,提供给使用静态方法来快捷创建消息框
      *       没直接使用QDialogButtonBox中的StandarButton是因为QDialogButtonBox中的Button翻译问题需要解决
      *       也需要使用Q_ENUM将枚举信息加入元对象，通过枚举转字符串生成按钮ObjectName，来匹配样式表，以解决按钮不同样式的问题
      */
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
    /**
     * @brief KiranMessageBox构造方法
     * @param parent parent为nullptr现在当前屏幕中央,如果存在parent，会显示在parent窗口中央
     */
    explicit KiranMessageBox(QWidget *parent = nullptr);

    /**
     * @brief KiranMessageBox析构方法
     */
    ~KiranMessageBox();

    /**
     * @brief 创建消息对话框
     * @param parent    指定显示在哪个窗口中央，置null则为当前屏幕中央
     * @param title     窗口标题
     * @param text      显示内容
     * @param buttons   显示内容
     * @return 用户点击的按钮
     */
    static KiranStandardButton message(QWidget *parent,
                                       const QString &title,
                                       const QString &text,
                                       KiranStandardButtons buttons);

    /**
     * @brief 设置窗口标题
     * @param title 标题
     */
    void setTitle(const QString &title);

    /**
     * @brief 设置显示内容
     * @param text 内容
     */
    void setText(const QString &text);

    /**
     * @brief 添加按钮到消息对话框中
     * @param button 按钮
     * @param role   按钮作用
     * @see QDialogButtonBox::addButton(QAbstractButton*, ButtonRole)
     */
    void addButton(QPushButton *button,QDialogButtonBox::ButtonRole role);

    /**
     * @brief 使用添加按钮的指针来移除消息对话框中的按钮
     * @param button 按钮
     * @see QDialogButtonBox::removeButton(QAbstractButton *)
     */
    void removeButton(QPushButton *button);

    /**
     * @brief 移除消息对话框中的所有按钮
     */
    void cleanButton();

    /**
     * @brief 返回设置的按钮大小
     * @return 按钮大小
     */
    QSize buttonSize();

    /**
     * @brief 设置按钮的大小
     * @param size 按钮尺寸
     */
    void setButtonSize(const QSize &size);

    /**
     * @brief 获取消息对话框中点击的按钮
     * @return 消息对话框点击的按钮，若没点击按钮则为NULL
     */
    QPushButton *clickedButton();

protected:
    bool event(QEvent *event) override;

private:
    KiranMessageBoxPrivate *d_ptr;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(KiranMessageBox::KiranStandardButtons)

#endif // KIRANMESSAGEBOX_H
