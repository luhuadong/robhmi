#include "IO.h"
#include "ui_IO.h"

IO::IO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IO)
{
    ui->setupUi(this);
    Init();
}

IO::~IO()
{
    delete ui;
}

void IO::Init()
{
    TableWidgetInit();
    BtnInit();
    ConnectInit();
}

void IO::TableWidgetInit()
{

}

void IO::BtnInit()
{

}

void IO::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}
