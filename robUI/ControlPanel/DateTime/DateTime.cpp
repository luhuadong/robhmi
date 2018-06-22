#include "DateTime.h"
#include "ui_DateTime.h"

DateTime::DateTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTime)
{
    ui->setupUi(this);
    Init();
}

DateTime::~DateTime()
{
    delete ui;
}

void DateTime::Init()
{
    BtnInit();
    ConnectInit();
}

void DateTime::BtnInit()
{

}

void DateTime::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}
