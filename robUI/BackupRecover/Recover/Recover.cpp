#include "Recover.h"
#include "ui_Recover.h"

Recover::Recover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recover)
{
    ui->setupUi(this);
    Init();
}

Recover::~Recover()
{
    delete ui;
}

void Recover::Init()
{
    ConnectInit();
}

void Recover::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(BtnCancelClicked_SIG()));
    connect(ui->btn_recover,SIGNAL(clicked()),this,SIGNAL(BtnRecoverClicked_SIG()));
}
