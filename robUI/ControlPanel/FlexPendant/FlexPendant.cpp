#include "FlexPendant.h"
#include "ui_FlexPendant.h"

FlexPendant::FlexPendant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlexPendant)
{
    ui->setupUi(this);
    Init();
}

FlexPendant::~FlexPendant()
{
    delete ui;
}

void FlexPendant::Init()
{
    TableWidgetInit();
    BtnInit();
    ConnectInit();
}

void FlexPendant::TableWidgetInit()
{

}

void FlexPendant::BtnInit()
{

}

void FlexPendant::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}
