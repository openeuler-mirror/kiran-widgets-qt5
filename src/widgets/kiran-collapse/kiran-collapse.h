/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiran-widgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     youzhengcai <youzhengcai@kylinsec.com.cn>
 */
#pragma once
#include <QWidget>

class QEvent;

namespace Ui
{
class KiranCollapse;
}

class KiranCollapse : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 默认构造函数
     * @param parent 父控件
     */
    explicit KiranCollapse(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~KiranCollapse() override;

    /**
     * @brief 通过有参构造实例化 KiranCollapse
     * @param defaultIsExpand 默认是否展开
     * @param title 文本标题
     * @param expandSpaceWidget 扩展区控件
     * @param parent 父控件
     */
    KiranCollapse(bool defaultIsExpand, const QString& title, QWidget* expandSpaceWidget, QWidget* parent = nullptr);

    /**
     * @brief 设置 kiran-collapse 的标题
     * @param title 标题文本
     */
    void setTitle(const QString& title);

    /**
     * @brief 添加一个控件到顶栏
     * @param widget QWidget控件，加入方式为：每次加入的控件会放在最右边图标的左侧
     */
    void addTopBarWidget(QWidget* widget);

    /**
     * @brief 设置顶栏的固定高度
     * @param height 高度（默认为45）
     */
    void setTopBarFixedHeight(int height);

    /**
     * @brief 设置扩展区内部间距
     * @param left 左边距
     * @param top 上边距
     * @param right 右边距
     * @param bottom 下边距
     */
    void setExpansionMargin(int left, int top, int right, int bottom);

    /**
     * @brief 获取扩展区内部间距
     * @return 边距对象
     */
    QMargins expansionMargin();

    /**
     * @brief 设置顶栏内部间距
     * @param left 左边距
     * @param top 上边距
     * @param right 右边距
     * @param bottom 下边距
     */
    void setTopBarMargin(int left, int top, int right, int bottom);

    /**
     * @brief 设置顶栏控件间距
     * @param spacing 间距值
     */
    void setTopBarSpacing(int spacing);

    /**
     * @brief 获取 kiran-collapse 是否展开
     * @return 是否展开的状态
     */
    bool getIsExpand() const;

    /**
     * @brief 设置 kiran-collapse 默认状态是否展开，初始化时使用
     * @param isExpanded 是否展开
     */
    void setIsExpand(bool isExpanded);

    /**
     * @brief 设置扩展区固定最大展开高度
     * @param maxExpandHeight 最大展开高度
     */
    void setFixMaxExpansionHeight(int maxExpandHeight);

    /**
     * @brief 添加控件到扩展区
     * @param widget 要加入到扩展区的控件
     */
    void addExpansionSpaceWidget(QWidget* widget);

    /**
     * @brief 根据索引删除扩展区的控件
     * @param index 扩展区内控件从上到下的索引
     */
    void delExpansionSpaceWidget(int index);

    /**
     * @brief 根据控件对象名称删除控件
     * @param widgetName 控件名称
     */
    void delExpansionSpaceWidget(const QString& widgetName);

    /**
     * @brief 清除扩展区所有控件
     */
    void delAllExpansionSpaceWidget();

    /**
     * @brief 将扩展区展开
     */
    void setExpand();

    /**
     * @brief 将扩展区折叠
     */
    void setCollapse();

signals:
    /**
     * @brief 扩展区被展开时发出的信号
     */
    void expandSpaceExpanded();
    
    /**
     * @brief 扩展区被折叠时发出的信号
     */
    void expandSpaceCollapsed();

protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    // 使用PIMPL模式隐藏实现细节
    Q_DISABLE_COPY(KiranCollapse);
    class KiranCollapsePrivate;
    KiranCollapsePrivate* d;
    ::Ui::KiranCollapse* ui;
};
