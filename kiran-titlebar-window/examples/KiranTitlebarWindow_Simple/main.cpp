#include <QApplication>
#include <QIcon>
#include <QLineEdit>
#include <QToolButton>
#include <QHBoxLayout>

#include <kiranwidgets-qt5/kiran-titlebar-window.h>
#include "titlebar-window-simple.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    KiranTitlebarWindow window;
    ///设置窗口标题栏
    window.setTitle("TitlebarWindowSimple");
    ///设置窗口图标
    window.setIcon(QIcon::fromTheme("window"));
    ///设置窗口按钮
    window.setButtonHints(KiranTitlebarWindow::TitlebarMinimizeButtonHint|KiranTitlebarWindow::TitlebarCloseButtonHint);
    ///设置是否允许窗口拖拽Resize
    window.setResizeable(false);
    ///标题栏添加自定义控件
    QLineEdit* edit = new QLineEdit;
    edit->setPlaceholderText("TitlebarWindowSimple");
    QToolButton* btn = new QToolButton;
    btn->setText("BUTTON");
    window.getTitlebarCustomLayout()->addWidget(edit);
    window.getTitlebarCustomLayout()->addWidget(btn);
    window.getTitlebarCustomLayout()->setSpacing(10);
    TitlebarWindowSimple simple;
    window.setWindowContentWidget(&simple);

    window.resize(640,480);
    window.show();
    return app.exec();
}
