#include "ProgramRoutinePro.h"
#include "ui_ProgramRoutinePro.h"

ProgramRoutinePro::ProgramRoutinePro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramRoutinePro)
{
    ui->setupUi(this);
    Init();
}

ProgramRoutinePro::~ProgramRoutinePro()
{
    delete ui;
}

void ProgramRoutinePro::Init()
{
    TableWidgetInit();
    BtnInit();
    ConnectInit();
}

void ProgramRoutinePro::TableWidgetInit()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置只能选择一个，不能多行选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //不要垂直滚动条
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //不要水平滚动条
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置不显示格子线
    ui->tableWidget->setShowGrid(false);
    /*去掉每行的行号*/
    QHeaderView *headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
    //设置表头不可点击（默认点击后进行排序）
    ui->tableWidget->horizontalHeader()->setDisabled(true);
    //设置每行内容不可更改
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);

    ui->tableWidget->setColumnCount(3);
    QStringList header;

    header<<tr("名称")<<tr("模块")<<tr("类型");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->horizontalHeader()->show();
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->tableWidget->size().width()/ui->tableWidget->columnCount());
}

void ProgramRoutinePro::ConnectInit()
{
    connect(ui->btn_file,SIGNAL(clicked()),this,SLOT(do_btnFileClicked()));
    connect(ui->btn_back,SIGNAL(clicked()),this,SIGNAL(BtnBackClicked_SIG()));
    connect(ui->btn_showRoutinePro,SIGNAL(clicked()),this,SIGNAL(BtnShowRoutineProClicked_SIG()));
    connect(ui->btn_filter,SIGNAL(clicked()),this,SIGNAL(BtnFilterClicked()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,
            SLOT(do_TableWidgetCellClicked(int ,int)));
    connect(menu,SIGNAL(triggered(QAction*)),this,SIGNAL(MenuActionTriggered(QAction*)));
}

void ProgramRoutinePro::BtnInit()
{
    QAction *newModule = new QAction(tr("新建例行程序..."),this);
    QAction *loadModule = new QAction(tr("加载例行程序..."),this);
    QAction *saveModule = new QAction(tr("另存例行程序为..."),this);
    QAction *alterModule = new QAction(tr("更改声明..."),this);
    QAction *renameModule = new QAction(tr("重命名..."),this);
    QAction *deleteModule = new QAction(tr("删除例行程序..."),this);

    menu=new QMenu(this);

    menu->addAction(newModule);
    menu->addAction(loadModule);
    menu->addAction(saveModule);
    menu->addAction(alterModule);
    menu->addAction(renameModule);
    menu->addAction(deleteModule);
}

void ProgramRoutinePro::TableWidgetSelectRow(int Row)
{
    ui->tableWidget->selectRow(Row);
}

void ProgramRoutinePro::TableWidgetSetRowCount(int Row)
{
    ui->tableWidget->setRowCount(Row);
}

void ProgramRoutinePro::TableWidgetClear()
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);
}

void ProgramRoutinePro::TableWidgetSetItem(int row, int column, QTableWidgetItem *item)
{
    ui->tableWidget->setItem(row,column,item);
}

void ProgramRoutinePro::do_TableWidgetCellClicked(int row,int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);
    if(itemData == NULL)
        return ;

    column = 0;
    QTableWidgetItem *Name = ui->tableWidget->item(row,column);

    column = 1;
    QTableWidgetItem *Module = ui->tableWidget->item(row,column);

    column = 2;
    QTableWidgetItem *Type = ui->tableWidget->item(row,column);

    emit TableWidgetCellClicked_SIG(row,column,Name->text(),
                                    Module->text(),Type->text());
}

void ProgramRoutinePro::do_btnFileClicked()
{
    menu->setFixedWidth(ui->btn_file->size().width());

    QPoint pos;
    pos.setX(0);
    pos.setY(-menu->sizeHint().height());

    menu->exec(ui->btn_file->mapToGlobal(pos));
}
