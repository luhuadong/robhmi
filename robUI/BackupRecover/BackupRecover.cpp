#include "BackupRecover.h"
#include "ui_BackupRecover.h"

BackupRecover::BackupRecover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackupRecover)
{
    ui->setupUi(this);

    Init();
}

BackupRecover::~BackupRecover()
{
    delete ui;
}

void BackupRecover::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    ViewInit();
    ConnectInit();
    ViewInit();
}

void BackupRecover::ViewInit()
{
    rBackup = new Backup;
    rRecover = new Recover;

    StackedWidgetAddWidget(rBackup);
    StackedWidgetAddWidget(rRecover);
}

void BackupRecover::ConnectInit()
{
    connect(ui->btn_Backup,SIGNAL(clicked()),this,SLOT(do_BtnBackupClicked()));
    connect(ui->btn_Recover,SIGNAL(clicked()),this,SLOT(do_BtnRecoverClicked()));
    connect(rRecover,SIGNAL(BtnCancelClicked_SIG()),this,SLOT(do_BtnCancelClicked()));
    connect(rBackup,SIGNAL(BtnCancelClicked_SIG()),this,SLOT(do_BtnCancelClicked()));
}

void BackupRecover::do_BtnBackupClicked()
{
    StackedWidgetSetCurrentIndex(vBackup);
}

void BackupRecover::do_BtnRecoverClicked()
{
    StackedWidgetSetCurrentIndex(vRecover);
}

void BackupRecover::do_BtnCancelClicked()
{
    StackedWidgetSetCurrentIndex(vBackupRecover);
}

void BackupRecover::StackedWidgetAddWidget(QWidget * widget)
{
    ui->stackedWidget->addWidget(widget);
}

void BackupRecover::StackedWidgetSetCurrentIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
