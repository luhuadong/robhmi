#include "ResourceManage.h"
#include "ui_ResourceManage.h"

void ResourceManage::Init()
{
    TableWidgetInit();
    vkey = new vkeyworld;
    StackedWidgetAddWidget(vkey);
    BtnInit();
    ConnectInit();

    UDiskPath=NULL;
    copyFile=NULL;
    copyFlag=0;

    emit RMInit();
}

void ResourceManage::TableWidgetInit()
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

void ResourceManage::BtnInit()
{
    aCopy = new QAction(tr("复制"),this);
    aMove = new QAction(tr("移动"),this);
    aPase = new QAction(tr("粘帖"),this);
    aReNa = new QAction(tr("重命名"),this);
    aDele = new QAction(tr("删除"),this);
    aAttr = new QAction(tr("属性"),this);

    menu=new QMenu(this);

    menu->addAction(aCopy);
    menu->addAction(aMove);
    menu->addAction(aPase);
    menu->addAction(aReNa);
    menu->addAction(aDele);
    menu->addAction(aAttr);
}

void ResourceManage::ConnectInit()
{
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),
            this,SLOT(do_TableWidgetCellClicked(int,int)));
//    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),
//            this,SLOT(do_TableWidgetCellDoubleClicked(int,int)));
    connect(this,SIGNAL(TableWidgetNoChooseLine()),this,
            SLOT(do_TableWidgetNoChooseLine()));

    connect(ui->btn_menu,SIGNAL(clicked()),this,SLOT(do_btnMenuClicked()));
    connect(ui->btn_refresh,SIGNAL(clicked()),this,SLOT(do_btnRefreshClicked()));
    connect(ui->btn_new,SIGNAL(clicked()),this,SLOT(do_btnNewClicked()));
    connect(ui->btn_hideHeader,SIGNAL(clicked()),this,SLOT(do_btnHideHeaderClicked()));
    connect(ui->btn_showHeader,SIGNAL(clicked()),this,SLOT(do_btnShowHeaderClicked()));
    connect(ui->btn_showsize,SIGNAL(clicked()),this,SLOT(do_btnShowSize()));
    connect(ui->btn_close,SIGNAL(clicked()),this,SLOT(do_btnCloseClicked()));

    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(do_triggered(QAction*)));

    connect(vkey,SIGNAL(sig_ok(QString)),this,SLOT(do_keyOk(QString)));
    connect(vkey,SIGNAL(sig_cancel()),this,SLOT(do_keyCancle()));

    connect(this,SIGNAL(RMInit()),this,SLOT(Root()));
    connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(ItemDoubleClicked(QTableWidgetItem*)));
    connect(ui->btn_home,SIGNAL(clicked()),this,SLOT(Root()));
//    connect(ui->btn_UDisk,SIGNAL(clicked()),this,SLOT(UDisk()));
//    connect(ui->btn_Copy,SIGNAL(clicked()),this,SLOT(Copy()));
//    connect(ui->btn_Cut,SIGNAL(clicked()),this,SLOT(Cut()));
//    connect(ui->btn_Paste,SIGNAL(clicked()),this,SLOT(Paste()));
//    connect(ui->btn_Delete,SIGNAL(clicked()),this,SLOT(Delete()));
//    connect(ui->btn_Enter,SIGNAL(clicked()),this,SLOT(Enter()));
    connect(ui->btn_up,SIGNAL(clicked()),this,SLOT(Up()));
//    connect(ui->btn_Exit,SIGNAL(clicked()),this,SLOT(Exit()));
}
