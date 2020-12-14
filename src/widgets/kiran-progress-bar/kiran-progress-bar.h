//
// Created by lxh on 2020/12/12.
//

#ifndef KIRANWIDGETS_QT5_KIRAN_PROGRESS_BAR_H
#define KIRANWIDGETS_QT5_KIRAN_PROGRESS_BAR_H

#include <QProgressBar>
#include <kiran-public-define.h>

class KiranProgressBarPrivate;

class Q_DECL_EXPORT KiranProgressBar : public QProgressBar{
    Q_OBJECT
    Q_DECLARE_PRIVATE(KiranProgressBar)

public:
    explicit KiranProgressBar(QWidget *parent = nullptr);
    ~KiranProgressBar();

    /// NOTE: textPosition 只在KiranStyle下使用才生效
    /// 设置进度显示位置
    /// \param position 进度显示位置
    void setTextPosition(Kiran::ProgressBarTextPosition position);

    /// 获取进度显示位置
    /// \return 进度文本显示位置
    Kiran::ProgressBarTextPosition getTextPosition();

protected:
    bool event(QEvent *e) override;

private:
    KiranProgressBarPrivate* d_ptr;

};

#endif //KIRANWIDGETS_QT5_KIRAN_PROGRESS_BAR_H
