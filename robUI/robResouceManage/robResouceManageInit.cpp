#include "robResouceManage.h"
#include "ui_robResouceManage.h"

void robResouceManage::Init()
{
    TableWidgetInit();
//    StackedWidgetAddWidget(vkey);
//    BtnInit();
    ConnectInit();

    UDiskPath=NULL;
    copyFile=NULL;
    copyFlag=0;

    emit robRMInit();
}

void robResouceManage::TableWidgetInit()
{
    //只能选择一行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //选择一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不要垂直滚动条
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //不要水平滚动条
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置不显示格子线
    ui->tableWidget->setShowGrid(false);
    /*去掉每行的行号*/
    ui->tableWidget->verticalHeader()->hide();
    //设置每行内容不可更改
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //表头显示
    ui->tableWidget->horizontalHeader()->show();
    //设置表头不可点击（默认点击后进行排序）
    ui->tableWidget->horizontalHeader()->setDisabled(true);
    //列宽
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0,560);
    ui->tableWidget->setColumnWidth(1,240);
}

void robResouceManage::ConnectInit()
{
    connect(ui->btn_OpenKey,SIGNAL(clicked()),this,SIGNAL(btnOpenKeyClicked_SIG()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SIGNAL(btnOkClicked_SIG()));
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(btnCancelClicked_SIG()));
    connect(ui->btn_new,SIGNAL(clicked()),this,SIGNAL(btnNewClicked_SIG()));

    connect(ui->btn_hideHeader,SIGNAL(clicked()),this,SLOT(do_btnHideHeaderClicked()));
    connect(ui->btn_showHeader,SIGNAL(clicked()),this,SLOT(do_btnShowHeaderClicked()));
    connect(ui->btn_up,SIGNAL(clicked()),this,SLOT(do_btnUpClicked()));
    connect(ui->btn_home,SIGNAL(clicked()),this,SLOT(do_btnHomeClicked()));

    connect(this,SIGNAL(robRMInit()),this,SLOT(do_Init()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(do_cellClicked(int,int)));
}
