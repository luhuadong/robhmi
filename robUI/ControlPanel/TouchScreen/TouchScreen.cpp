#include "TouchScreen.h"
#include "ui_TouchScreen.h"

TouchScreen::TouchScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchScreen)
{
    ui->setupUi(this);
    Init();
}

TouchScreen::~TouchScreen()
{
    delete ui;
}

void TouchScreen::Init()
{
    BtnInit();
    ConnectInit();
}

void TouchScreen::BtnInit()
{
}


void TouchScreen::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btn_CancelClicked_SIG()));
    connect(ui->btn_correct,SIGNAL(clicked()),this,SIGNAL(btn_CorrectClicked_SIG()));
}
