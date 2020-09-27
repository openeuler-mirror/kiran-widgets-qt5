#include "titlebar-window-ui.h"
#include "ui_titlebar-window-ui.h"

#include <QIcon>
#include <QLineEdit>
#include <QToolButton>
TitlebarWindowUI::TitlebarWindowUI(QWidget *parent) :
    KiranTitlebarWindow(),
    ui(new Ui::TitlebarWindowUI)
{
    ///设置窗口标题栏
    setTitle("TitlebarWindowUI");
    ///设置窗口图标
    setIcon(QIcon::fromTheme("window"));
    ///设置窗口按钮
    setButtonHints(KiranTitlebarWindow::TitlebarMinimizeButtonHint|KiranTitlebarWindow::TitlebarCloseButtonHint);
    ///设置是否允许窗口拖拽Resize
    setResizeable(false);
    ///标题栏添加自定义控件
    QLineEdit* edit = new QLineEdit;
    edit->setPlaceholderText("KiranTitlebarWindowUI");
    QToolButton* btn = new QToolButton;
    btn->setText("BUTTON");
    getTitlebarCustomLayout()->addWidget(edit);
    getTitlebarCustomLayout()->addWidget(btn);
    getTitlebarCustomLayout()->setSpacing(10);
    ///NOTE:通过UI文件初始化自定义标题栏的内容窗口
    ui->setupUi(getWindowContentWidget());
}

TitlebarWindowUI::~TitlebarWindowUI()
{
    delete ui;
}
