#include "titlebar-window-cpp.h"

#include <QIcon>
#include <QLineEdit>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
TitlebarWindowCPP::TitlebarWindowCPP(QWidget *parent) :
    KiranTitlebarWindow()
{
    ///设置窗口标题栏
    setTitle("KiranTitlebarWindowCPP");
    ///设置窗口图标
    setIcon(QIcon::fromTheme("window"));
    ///设置窗口按钮
    setButtonsHint(KiranTitlebarWindow::TitlebarMinimizeButtonHint|KiranTitlebarWindow::TitlebarCloseButtonHint);
    ///设置是否允许窗口拖拽Resize
    setResizeable(false);
    ///标题栏添加自定义控件
    QLineEdit* edit = new QLineEdit;
    edit->setPlaceholderText("KiranTitlebarWindowCPP");
    QToolButton* btn = new QToolButton;
    btn->setText("BUTTON");
    getTitleBarCustomLayout()->addWidget(edit);
    getTitleBarCustomLayout()->addWidget(btn);
    getTitleBarCustomLayout()->setSpacing(10);

    ///初始化自定义标题栏窗口内容
    initUI();
}

TitlebarWindowCPP::~TitlebarWindowCPP()
{

}

void TitlebarWindowCPP::initUI()
{
    QWidget* windowContentWidget = getWindowContentWidget();
    QVBoxLayout* vLayout = new QVBoxLayout(windowContentWidget);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    QLabel* label = new QLabel(windowContentWidget);
    label->setAlignment(Qt::AlignCenter);
    label->setText("KiranTitlebarWindowCPP");
    label->setStyleSheet("QLabel{color:pink;font:40px;}");
    vLayout->addWidget(label);


}
