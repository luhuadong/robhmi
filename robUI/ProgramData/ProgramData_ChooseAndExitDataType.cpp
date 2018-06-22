#include "ProgramData_ChooseAndExitDataType.h"
#include "ui_ProgramData_ChooseAndExitDataType.h"

ProgramData_ChooseAndExitDataType::ProgramData_ChooseAndExitDataType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramData_ChooseAndExitDataType)
{
    ui->setupUi(this);

    Init();
}

ProgramData_ChooseAndExitDataType::~ProgramData_ChooseAndExitDataType()
{
    delete ui;
}

void ProgramData_ChooseAndExitDataType::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    tableWidgetInit();
    ConnectInit();
}

void ProgramData_ChooseAndExitDataType::tableWidgetInit()
{
    ui->tableWidget->setColumnCount(4);

    //设置只能选择一个，不能多行选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //单击选择一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
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
    //表头可见
    ui->tableWidget->horizontalHeader()->show();
    //行宽
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->tableWidget->size().width()/ui->tableWidget->columnCount());

    QStringList header;

    header<<tr("名称")<<tr("值")<<tr("模块")<<tr("");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseAndExitDataType::ConnectInit()
{
    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,SLOT(TableWidgetCellPressed(int ,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(TableWidgetCellDoubleClicked(int ,int)));

    connect(ui->btn_ShowDataType,SIGNAL(clicked()),this,SIGNAL(btnShowDataTypeClicked_SIG()));
    connect(ui->btn_Refresh,SIGNAL(clicked()),this,SIGNAL(btnRefreshClicked_SIG()));
    connect(ui->btn_ExitData,SIGNAL(clicked()),this,SIGNAL(btnExitDataClicked_SIG()));
    connect(ui->btn_Filter,SIGNAL(clicked()),this,SIGNAL(btnFilterClicked_SIG()));
    connect(ui->btn_NewData,SIGNAL(clicked()),this,SIGNAL(btnNewDataClicked_SIG()));
}

void ProgramData_ChooseAndExitDataType::setExplainLabelText(QString String)
{
    ui->ExplainLabel->setText(String);
}

void ProgramData_ChooseAndExitDataType::setScopeLabelText(QString String)
{
    ui->ScopeLabel->setText(String);
}

void ProgramData_ChooseAndExitDataType::setAlterScopeText(QString String)
{
    ui->AlterScope->setText(String);
}

void ProgramData_ChooseAndExitDataType::TableWidgetInsertRow(int Row)
{
    ui->tableWidget->insertRow(Row);//插入一行
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseAndExitDataType::TableWidgetRemoveRow(int Row)
{
    ui->tableWidget->removeRow(Row);//删除一行
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseAndExitDataType::TableWidgetSetItem(int row, int column, QTableWidgetItem *item)
{
    ui->tableWidget->setItem(row,column,item);
}

void ProgramData_ChooseAndExitDataType::TableWidgetCellPressed(int row, int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);
    if(itemData == NULL)
        return ;

    TableWidgetCurrentRow = row;
    TableWidgetCurrentColumn = column;

    emit TableWidgetCellPressed_SIG(row,column,itemData->text());
}

void ProgramData_ChooseAndExitDataType::TableWidgetCellDoubleClicked(int row, int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);

    if(itemData == NULL)
        return ;

    QString String = itemData->text();

    TableWidgetCurrentRow = row;
    TableWidgetCurrentColumn = column;

    itemData = ui->tableWidget->item(row,0);
    if(itemData == NULL)
        return ;
    QString FirstStr = itemData->text();

    emit TableWidgetCellDoubleClicked_SIG(row,column,String,FirstStr);
}

void ProgramData_ChooseAndExitDataType::TableWidgetClear()
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseAndExitDataType::TableWidgetAlterItem(int row,int column,QString str)//更改某行某列表格数据
{
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    item->setText(str);
}
