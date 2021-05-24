#include "widget.h"
#include "ui_widget.h"

#include "kiran-application.h"
#include "kiran-switch-button.h"
#include "kiran-search-box.h"
#include "widget-property-helper.h"

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QTabBar>
#include <QCheckBox>
#include <QDebug>
#include <kiran-message-box.h>
#include <kiran-image-selector.h>
#include <QCompleter>

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

    WidgetPropertyHelper::setSpinboxButtonPosition(ui->timeEdit, Kiran::ARROW_TWO_SIDERS);


    initTabBar();
    initPushButtonTab();
    initSwitchButtonTab();
    initComboBoxTab();
    initSearchBox();
    initProgressBar();
    initIconLineEdit();
    initKiranImageSelector();
}

Widget::~Widget()
{
    delete ui;
}

#include <child-window.h>
void Widget::initPushButtonTab()
{
    WidgetPropertyHelper::setButtonType(ui->btn_default, BUTTON_Default);
    WidgetPropertyHelper::setButtonType(ui->btn_normal, BUTTON_Normal);
    WidgetPropertyHelper::setButtonType(ui->btn_warning, BUTTON_Warning);
    connect(ui->btn_normal,&QPushButton::clicked,this,[this](){
        KiranMessageBox::message(this,"标题","文本",KiranMessageBox::Yes|KiranMessageBox::No);
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
    ui->comboBox->setStyleSheet("QComboBox{combobox-popup:0;}");
    for(int i=0;i<50;i++){
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
    QCompleter* completer = new QCompleter(QStringList() << "test" << "test001" << "test002",searchBox);
    completer->setFilterMode(Qt::MatchContains);
    completer->setCaseSensitivity(Qt::CaseSensitive);
    searchBox->setCompleter(completer);
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
    WidgetPropertyHelper::setProgressBarTextProsition(ui->progressBar, Kiran::PROGRESS_TEXT_RIGHT);
}

void Widget::initIconLineEdit()
{
    ui->iconLineEdit->setIcon(QIcon::fromTheme("window"));
    ui->iconLineEdit->setIconPosition(Kiran::ICON_POSITION_LEFT);
    ui->iconLineEdit->setIconSize(QSize(16,16));
}

void Widget::initKiranImageSelector()
{
    KiranImageSelector* imageSelector = new KiranImageSelector();
    imageSelector->setFixedHeight(148);
    ui->tab_imageSelector->layout()->addWidget(imageSelector);

    QLineEdit* edit_addImage = new QLineEdit;
    ui->tab_imageSelector->layout()->addWidget(edit_addImage);

    QPushButton* btn_addImage = new QPushButton("添加图片");
    btn_addImage->setFixedSize(120,40);
    connect(btn_addImage,&QPushButton::clicked,[&](){
        QString imagePath = edit_addImage->text();
        if( imagePath.isEmpty() ){
            return ;
        }
        imageSelector->addImage(imagePath);
    });

    ui->tab_imageSelector->layout()->addWidget(btn_addImage);

    QLineEdit* edit_removeImage = new QLineEdit;
    ui->tab_imageSelector->layout()->addWidget(edit_removeImage);

    QPushButton* btn_removeImage = new QPushButton("删除图片");
    btn_removeImage->setFixedSize(120,40);
    ui->tab_imageSelector->layout()->addWidget(btn_removeImage);
    connect(btn_removeImage,&QPushButton::clicked,[&](){
        QString imagePath = edit_removeImage->text();
        if( imagePath.isEmpty() ){
            return ;
        }
        imageSelector->removeImage(imagePath);
    });


    auto spacerItem = new QSpacerItem(20,20,QSizePolicy::Preferred,QSizePolicy::Expanding);
    ui->tab_imageSelector->layout()->addItem(spacerItem);
}
