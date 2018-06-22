#include "ProgKeys.h"
#include "ui_ProgKeys.h"

ProgKeys::ProgKeys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgKeys)
{
    ui->setupUi(this);

    Init();
}

ProgKeys::~ProgKeys()
{
    delete ui;
}

void ProgKeys::Init()
{
    BtnInit();
    TabWidgetInit();
    ConnectInit();
}

void ProgKeys::BtnInit()
{

}

void ProgKeys::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
}

void ProgKeys::TabWidgetInit()
{   //设置宽度
    ui->tabWidget->setStyleSheet("QTabBar::tab{width:200}");
}
