#include "ProgramData_ChooseDataType.h"
#include "ui_ProgramData_ChooseDataType.h"

ProgramData_ChooseDataType::ProgramData_ChooseDataType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramData_ChooseDataType)
{
    ui->setupUi(this);

    Init();
}

ProgramData_ChooseDataType::~ProgramData_ChooseDataType()
{
    delete ui;
}

void ProgramData_ChooseDataType::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    tableWidgetInit();
    ConnectInit();
}

void ProgramData_ChooseDataType::tableWidgetInit()
{
    ui->tableWidget->setColumnCount(3);

    //设置只能选择一个，不能多行选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //单击选择一个单元格
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
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
    //表头不可见
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->tableWidget->size().width()/ui->tableWidget->columnCount());

    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseDataType::ConnectInit()
{
    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,SLOT(TableWidgetCellPressed(int ,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(TableWidgetCellDoubleClicked(int ,int)));

    connect(ui->btn_ShowData,SIGNAL(clicked()),this,SIGNAL(btnShowDataClicked_SIG()));
    connect(ui->btn_View,SIGNAL(clicked()),this,SIGNAL(btnViewClicked_SIG()));
}

void ProgramData_ChooseDataType::setExplainLabelText(QString String)
{
    ui->ExplainLabel->setText(String);
}

void ProgramData_ChooseDataType::setScopeLabelText(QString String)
{
    ui->ScopeLabel->setText(String);
}

void ProgramData_ChooseDataType::setAlterScopeText(QString String)
{
    ui->AlterScope->setText(String);
}

void ProgramData_ChooseDataType::TableWidgetInsertRow(int Row)
{
    ui->tableWidget->insertRow(Row);//插入一行
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseDataType::TableWidgetRemoveRow(int Row)
{
    ui->tableWidget->removeRow(Row);//删除一行
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_ChooseDataType::TableWidgetSetItem(int row, int column, QTableWidgetItem *item)
{
    ui->tableWidget->setItem(row,column,item);
}

void ProgramData_ChooseDataType::TableWidgetCellPressed(int row, int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);
    if(itemData == NULL)
        return ;

    TableWidgetCurrentRow = row;
    TableWidgetCurrentColumn = column;

    emit TableWidgetCellPressed_SIG(row,column,itemData->text());
}

void ProgramData_ChooseDataType::TableWidgetCellDoubleClicked(int row, int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);

    if(itemData == NULL)
        return ;

    TableWidgetCurrentRow = row;
    TableWidgetCurrentColumn = column;

    emit TableWidgetCellDoubleClicked_SIG(row,column,itemData->text());
}

void ProgramData_ChooseDataType::TableWidgetClear()
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);
    TableWidgetRowCount = ui->tableWidget->rowCount();
}
