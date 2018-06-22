#include "Appearance.h"
#include "ui_Appearance.h"

Appearance::Appearance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Appearance)
{
    ui->setupUi(this);
    Init();
}

Appearance::~Appearance()
{
    delete ui;
}

void Appearance::Init()
{
    BtnInit();
    ConnectInit();
}

void Appearance::BtnInit()
{
}


void Appearance::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SIGNAL(btn_OKClicked_SIG()));
}
