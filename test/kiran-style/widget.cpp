#include "widget.h"
#include "ui_widget.h"

#include "kiran-application.h"
#include "kiran-switch-button.h"
#include "kiran-search-box.h"
#include "style-property-helper.h"

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QTabBar>
#include <QCheckBox>
#include <QDebug>

using namespace Kiran;

Widget::Widget(QWidget *parent)
    : KiranTitlebarWindow()
    , ui(new Ui::Widget)
{
    ui->setupUi(getWindowContentWidget());
    ui->checkBox_2->setCheckState(Qt::Checked);
    connect(ui->checkBox_2,&QCheckBox::stateChanged,[this](int state){
        auto setAllWidgetEnable = [this](bool enable){
            ui->tabWidget->setEnabled(enable);
        };
        if( state == Qt::Unchecked ){
            setAllWidgetEnable(false);
        }else{
            setAllWidgetEnable(true);
        }
    });

    PropertyHelper::setSpinboxButtonPosition(ui->timeEdit,Kiran::ARROW_TWO_SIDERS);

    initTabBar();
    initPushButtonTab();
    initSwitchButtonTab();
    initComboBoxTab();
    initSearchBox();
    initProgressBar();

//    ui->listWidget->item(0)->setCheckState(Qt::Checked);
    ui->listWidget->item(0)->setIcon(QIcon::fromTheme("system-file-manager"));
    ui->listWidget->item(0)->setData(Kiran::ItemStatus_Role,"禁用");
    ui->listWidget->item(0)->setData(Kiran::ItemStatusColor_Role,QColor("red"));
    ui->listWidget->setIconSize(QSize(40,40));
}

Widget::~Widget()
{
    delete ui;
}

#include <child-window.h>
void Widget::initPushButtonTab()
{
    PropertyHelper::setButtonType(ui->btn_default,BUTTON_Default);
    PropertyHelper::setButtonType(ui->btn_normal,BUTTON_Normal);
    PropertyHelper::setButtonType(ui->btn_warning,BUTTON_Warning);
    connect(ui->btn_normal,&QPushButton::clicked,this,[this](){
        ChildWindow *cw = new ChildWindow(this);
        cw->show();
    });
}

void Widget::initSwitchButtonTab()
{
    QWidget* switchWidget = ui->tabWidget->widget(1);

    KiranSwitchButton* switchCheckedButton = new KiranSwitchButton();
        switchCheckedButton->setText("checked");
        switchCheckedButton->setChecked(true);
    switchWidget->layout()->addWidget(switchCheckedButton);

    KiranSwitchButton* switchUncheckedButton = new KiranSwitchButton();
    switchUncheckedButton->setText("unchecked");
    switchUncheckedButton->setChecked(true);
    switchWidget->layout()->addWidget(switchUncheckedButton);

    KiranSwitchButton* switchdisableButton = new KiranSwitchButton();
    switchdisableButton->setText("disabled");
    switchdisableButton->setChecked(true);
    switchdisableButton->setEnabled(false);
    switchWidget->layout()->addWidget(switchdisableButton);
}

void Widget::initComboBoxTab()
{
    ui->comboBox->setEditable(false);
    ui->comboBox->addItem(QIcon::fromTheme("system-file-manager"),"system-file-manager");

    for(int i=0;i<5;i++){
        ui->comboBox->addItem(QString("%1").arg(i));
    }

    QActionGroup* actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);

    QMenu *egMenu = new QMenu(ui->bth_hasMenu);
    egMenu->setObjectName("menu");

    auto action1 = egMenu->addAction("111111111111");
    action1->setCheckable(true);
    action1->setChecked(true);
    actionGroup->addAction(action1);

    auto action2 = egMenu->addAction("2222");
    action2->setCheckable(true);
    actionGroup->addAction(action2);

    auto action3 = egMenu->addAction("33");
    action3->setCheckable(true);
    actionGroup->addAction(action3);

    auto action4 = egMenu->addAction("44");
    action4->setCheckable(true);
    actionGroup->addAction(action4);

    ui->bth_hasMenu->setMenu(egMenu);
}

void Widget::initTabBar()
{
    ui->tabWidget->tabBar()->setTabIcon(0,QIcon::fromTheme("system-file-manager"));
}

void Widget::initSearchBox()
{
    KiranSearchBox* searchBox = new KiranSearchBox(this);
    searchBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QBoxLayout* layout = qobject_cast<QBoxLayout*>(ui->tabWidget->widget(5)->layout());
    layout->addWidget(searchBox,0,Qt::AlignVCenter);
}

void Widget::initProgressBar()
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(60);
    ui->progressBar->setValue(50);
    ui->progressBar->setOrientation(Qt::Horizontal);
    PropertyHelper::setProgressBarTextProsition(ui->progressBar,Kiran::PROGRESS_TEXT_RIGHT);
}