#include "Diagnosis.h"
#include "ui_Diagnosis.h"

Diagnosis::Diagnosis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Diagnosis)
{
    ui->setupUi(this);
    Init();
}

Diagnosis::~Diagnosis()
{
    delete ui;
}

void Diagnosis::Init()
{
    BtnInit();
    ConnectInit();
}

void Diagnosis::BtnInit()
{

}

void Diagnosis::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}
