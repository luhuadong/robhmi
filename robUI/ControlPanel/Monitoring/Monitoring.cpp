#include "Monitoring.h"
#include "ui_Monitoring.h"

Monitoring::Monitoring(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitoring)
{
    ui->setupUi(this);
    Init();
}

Monitoring::~Monitoring()
{
    delete ui;
}

void Monitoring::Init()
{
    BtnInit();
    ConnectInit();
}

void Monitoring::BtnInit()
{

}

void Monitoring::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}
