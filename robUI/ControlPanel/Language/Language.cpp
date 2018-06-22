#include "Language.h"
#include "ui_Language.h"

Language::Language(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Language)
{
    ui->setupUi(this);

    Init();

}

Language::~Language()
{
    delete ui;
}

void Language::Init()
{
    TableWidgetInit();
    BtnInit();
    ConnectInit();
}

void Language::TableWidgetInit()
{

}

void Language::BtnInit()
{

}

void Language::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SIGNAL(btn_OKClicked_SIG()));
}

