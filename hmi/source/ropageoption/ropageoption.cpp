#include "header/ropageoption/ropageoption.h"
#include "ui_ropageoption.h"
#include <QDebug>

RoPageOption::RoPageOption(romenu *Menu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoPageOption)
{
    ui->setupUi(this);
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);
    ui->stackedWidget->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    this->Menu = Menu;

    Init();
}

RoPageOption::~RoPageOption()
{
    delete ui;
}

void RoPageOption::Init()
{
    ViewsInit();
    ConnectInit();
}

void RoPageOption::ViewsInit()
{
    home = new RoPageHome(this);
//    rProgram = new Program;
    Program = new RoProgram;
    CP = new ControlPanel;
    alarm = new RoPageAlarm(this);
    pos = new roposition(this);
    prodata = new ropageprogramdata;
    IOput = new InputOutput(this);
    BR = new BackupRecover;
    RManage = new ResourceManage;
    SysInfo = new SystemInfo;
    ParaSet = new HMI_ParaSet;
    manual = new RobManual(this);

    ui->stackedWidget->addWidget(home);
    ui->stackedWidget->addWidget(Program);
    ui->stackedWidget->addWidget(CP);
    ui->stackedWidget->addWidget(alarm);
    ui->stackedWidget->addWidget(pos);
    ui->stackedWidget->addWidget(prodata);
    ui->stackedWidget->addWidget(IOput);
    ui->stackedWidget->addWidget(BR);
    ui->stackedWidget->addWidget(RManage);
    ui->stackedWidget->addWidget(SysInfo);
    ui->stackedWidget->addWidget(ParaSet);
    ui->stackedWidget->addWidget(manual);

    stack = ui->stackedWidget;

    ui->stackedWidget->setCurrentIndex(0);
}

void RoPageOption::ConnectInit()
{
//    connect(stack,SIGNAL(currentChanged(int)),this,SLOT(changeview(int)));//底部托盘
    connect(this->Menu,SIGNAL(sendmenu(int)),this,SLOT(changeView(int)));
    connect(alarm,SIGNAL(isAlarm(int)),this,SLOT(changeView(int)));
}

void RoPageOption::changeView(int num)
{
    stack->setCurrentIndex(num);
}

