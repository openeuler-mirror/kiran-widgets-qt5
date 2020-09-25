#include "titlebar-window-simple.h"
#include "ui_titlebar-window-simple.h"

TitlebarWindowSimple::TitlebarWindowSimple(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitlebarWindowSimple)
{
    ui->setupUi(this);
}

TitlebarWindowSimple::~TitlebarWindowSimple()
{
    delete ui;
}
