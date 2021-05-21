/**
 *@file  title-bar-layout.h
 *@brief  自定义标题栏窗口标题栏布局
 *@auth  liuxinhao <liuxinhao@kylinos.com.cn>
 *@copyright (c) 2021 KylinSec. All rights reserved.
 */
#ifndef KIRANWIDGETS_QT5_TITLE_BAR_LAYOUT_H
#define KIRANWIDGETS_QT5_TITLE_BAR_LAYOUT_H

#include <QLayout>
#include <QLabel>
#include <QMargins>

class TitlebarLayout : public QLayout
{
    Q_OBJECT
public:
    TitlebarLayout(QWidget *parent = nullptr);
    ~TitlebarLayout();

    QLayoutItem* titleBarIcon();
    void setTitleBarIconLabel(QLabel* icon);
    //NOTE:上下边距不会生效,生效的只有左右边距
    QMargins titleBarIconMargin();
    void setTitleBarIconMargin(QMargins margins);

    QLayoutItem* titleBarTitle();
    void setTitleBarTitleLabel(QLabel* title);
    void setTitleBarCompleteTitle(const QString& title);
    QMargins titleBarLabelMargin();
    void setTitleBarTLabelMargin(QMargins margins);

    QLayoutItem* titleBarCustomWidget();
    void setTitleBarCustomWidget(QWidget* customWidget);
    QMargins titleBarCustomMargin();
    void setTitleBarCustomMargin(QMargins margins);

    QLayoutItem* titleBarRightWidget();
    void setTitleBarRightWidget(QWidget* rightWidget);
    QMargins titleBarRightMargin();
    void setTitleBarRightWidgetMargin(QMargins margins);

    void setCustomWidgetCenter(bool center);
    bool customWidgetCenter();

protected:
    /**
     * @brief 将布局项添加到布局中
     * @param item
     */
    virtual void addItem(QLayoutItem *item) override;
    /**
     * @brief  控件的建议大小
     * @return 控件大小
     */
    virtual QSize sizeHint() const override;
    /**
     * @brief 获取索引处的布局项，如没有这样的项返回null
     * @param index
     * @return
     */
    virtual QLayoutItem *itemAt(int index) const override;
    /**
     * @brief 计算各个item的位置大小
     * @param rect
     */
    virtual void setGeometry(const QRect &rect) override;
    virtual QSize minimumSize() const override;
    virtual QLayoutItem *takeAt(int index) override;
    virtual int count() const override;

private:
    QMargins m_iconMargins;
    QLayoutItem* m_iconLabelItem = nullptr;

    QMargins m_titleMargins;
    QString m_completeTitle;
    QLayoutItem* m_titleLabelItem = nullptr;

    QMargins m_customWidgetMargins;
    bool m_customWidgetCenter = true;
    QLayoutItem* m_customWidgetItem = nullptr;

    QMargins m_rightWidgetMargins;
    QLayoutItem* m_rightWidgetItem = nullptr;
};
#endif //KIRANWIDGETS_QT5_TITLE_BAR_LAYOUT_H
