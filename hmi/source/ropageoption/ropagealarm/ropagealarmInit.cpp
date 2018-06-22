#include "header/ropageoption/ropagealarm/ropagealarm.h"
#include "ui_ropagealarm.h"

void RoPageAlarm::Init()
{
    robRM = new robResouceManage;
    vkey = new vkeyworld;
    ui->stackedWidget->addWidget(robRM);
    ui->stackedWidget->addWidget(vkey);

    TableWidgetInit();
    BtnInit();
    ConnectInit();
}

void RoPageAlarm::TableWidgetInit()
{
    //ui->tableWidget
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,280);
    ui->tableWidget->setColumnWidth(2,180);

    /*去掉每行的行号*/
    QHeaderView *headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);

    //不要垂直滚动条
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置不显示格子线
    ui->tableWidget->setShowGrid(false);
    //单击选择一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置只能选择一行，不能多行选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置每行内容不可更改
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //不设置隔一行变一颜色，即：一灰一白
    ui->tableWidget->setAlternatingRowColors(false);
}

void RoPageAlarm::BtnInit()
{
    ui->btn_refresh->setEnabled(false);
    ui->btn_del->setEnabled(false);
}

void RoPageAlarm::ConnectInit()
{
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),
                this,SLOT(do_cellClicked(int ,int)));

//    connect(robAlarmThread,SIGNAL(sendAlarm()),this,SLOT(do_Alarm()));
    connect(this,SIGNAL(sendAlarm()),this,SLOT(do_Alarm()));

    connect(ui->btn_save,SIGNAL(clicked()),this,SLOT(do_btnSaveClicked()));
    connect(ui->btn_del,SIGNAL(clicked()),this,SLOT(do_btnDelClicked()));
    connect(ui->btn_refresh,SIGNAL(clicked()),this,SLOT(do_btnRefreshClicked()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(do_btnOkClicked()));
    connect(ui->btn_view,SIGNAL(clicked()),this,SLOT(do_btnViewClicked()));

    connect(robRM,SIGNAL(btnNewClicked_SIG()),this,SLOT(do_robRMbtnNewClicked()));
    connect(robRM,SIGNAL(btnOpenKeyClicked_SIG()),this,SLOT(do_robRMbtnOpenKeyClicked()));
    connect(robRM,SIGNAL(btnOkClicked_SIG()),this,SLOT(do_robRMbtnOkClicked()));
    connect(robRM,SIGNAL(btnCancelClicked_SIG()),this,SLOT(do_robRMbtnCancelClicked()));

    connect(vkey,SIGNAL(sig_ok(QString)),this,SLOT(do_keyOk(QString)));
    connect(vkey,SIGNAL(sig_cancel()),this,SLOT(do_keyCancel()));
}


