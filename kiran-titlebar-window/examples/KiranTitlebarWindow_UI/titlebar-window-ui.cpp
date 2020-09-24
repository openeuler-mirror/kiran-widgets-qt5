#include "titlebar-window-ui.h"
#include "ui_titlebar-window-ui.h"

TitlebarWindowUI::TitlebarWindowUI(QWidget *parent) :
    KiranTitlebarWindow(),
    ui(new Ui::TitlebarWindowUI)
{
    setWindowTitle("TitlebarWindowUI");
    ui->setupUi(getWindowContentWidget());
}

TitlebarWindowUI::~TitlebarWindowUI()
{
    delete ui;
}
