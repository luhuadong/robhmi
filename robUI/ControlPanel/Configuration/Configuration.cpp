#include "Configuration.h"
#include "ui_Configuration.h"

Configuration::Configuration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);

    Init();
}

Configuration::~Configuration()
{
    delete ui;
}

void Configuration::Init()
{
    TableWidgetInit();
    BtnInit();
    ConnectInit();
}

void Configuration::TableWidgetInit()
{

}

void Configuration::BtnInit()
{

}

void Configuration::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}
