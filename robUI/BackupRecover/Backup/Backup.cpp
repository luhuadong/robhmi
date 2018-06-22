#include "Backup.h"
#include "ui_Backup.h"

Backup::Backup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Backup)
{
    ui->setupUi(this);
    Init();
}

Backup::~Backup()
{
    delete ui;
}

void Backup::Init()
{
    ConnectInit();
}

void Backup::ConnectInit()
{
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(BtnCancelClicked_SIG()));
    connect(ui->btn_backup,SIGNAL(clicked()),this,SIGNAL(BtnBackupClicked_SIG()));
}
