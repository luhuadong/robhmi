#include "ProgramData_Alter.h"
#include "ui_ProgramData_Alter.h"
#include <QDebug>
ProgramData_Alter::ProgramData_Alter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramData_Alter)
{
    ui->setupUi(this);
    Init();
}

ProgramData_Alter::~ProgramData_Alter()
{
    delete ui;
}

void ProgramData_Alter::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    tableWidgetInit();
    buttonWidgetInit();

    ConnectInit();
}

void ProgramData_Alter::tableWidgetInit()
{    //单击选择一行
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
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置点击更改
    ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);

    TableWidgetRowCount = ui->tableWidget->rowCount();


    while(TableWidgetRowCount!=0)
        TableWidgetRemoveRow(0);
    ui->tableWidget->setColumnCount(3);
    QStringList header;

    header<<tr("名称")<<tr("值")<<tr("数据类型");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->horizontalHeader()->show();
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->tableWidget->size().width()/ui->tableWidget->columnCount());
}

void ProgramData_Alter::buttonWidgetInit()
{
    setFALSEBtnHide(true);
    setTRUEBtnHide(true);
}

void ProgramData_Alter::ConnectInit()
{
    connect(ui->btn_true,SIGNAL(clicked()),this,SIGNAL(TRUEBtnClicked_SIG()));
    connect(ui->btn_false,SIGNAL(clicked()),this,SIGNAL(FALSEBtnClicked_SIG()));
    connect(ui->btn_undo,SIGNAL(clicked()),this,SIGNAL(UndoBtnClicked_SIG()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SIGNAL(OkBtnClicked_SIG()));
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SIGNAL(CancelBtnClicked_SIG()));
    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,
            SLOT(TableWidgetCellPressed(int,int)));
    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,
            SIGNAL(TableWidgetItemClicked_SIG(QTableWidgetItem*)));
//    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,
//            SLOT(TableWidgetCellDoubleClicked(int,int)));
}

void ProgramData_Alter::setFALSEBtnHide(bool Hideen)
{
    if(Hideen)
        ui->btn_false->hide();
    else
        ui->btn_false->show();
}

void ProgramData_Alter::setUndoBtnHide(bool Hideen)
{
    if(Hideen)
        ui->btn_undo->hide();
    else
        ui->btn_undo->show();
}

void ProgramData_Alter::setTRUEBtnHide(bool Hideen)
{
    if(Hideen)
        ui->btn_true->hide();
    else
        ui->btn_true->show();
}

void ProgramData_Alter::setCancelBtnEnabled(bool checkable)
{
    ui->btn_cancel->setEnabled(checkable);
}

void ProgramData_Alter::setUndoBtnEnabled(bool checkable)
{
    ui->btn_undo->setEnabled(checkable);
}

void ProgramData_Alter::setOKBtnEnabled(bool checkable)
{
    ui->btn_ok->setEnabled(checkable);
}

void ProgramData_Alter::TableWidgetClear()
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_Alter::TableWidgetSetItem(int row, int column, QTableWidgetItem *item)
{    
    ui->tableWidget->setItem(row,column,item);

    if(column==ui->tableWidget->columnCount()-1){
        QTableWidgetItem *item_1 = ui->tableWidget->item(row, 1);

        if(item_1->text()=="TRUE"||item_1->text()=="FALSE"){
            for(int i = 0;i<ui->tableWidget->columnCount();i++){//变成不可编辑
                QTableWidgetItem *item_t = ui->tableWidget->item(row, i);
                item_t->setFlags(item_t->flags() & (~Qt::ItemIsEditable));
            }
        }else if(item_1->text().at(0)=='['&&//变成不可用
                item_1->text().at(item_1->text().count()-1)==']'){
            for(int i = 0;i<ui->tableWidget->columnCount();i++){
                QTableWidgetItem *item_t = ui->tableWidget->item(row, i);
                item_t->setFlags(item_t->flags() & (~Qt::ItemIsEnabled));
            }
        }

        for(int i = 0;i<ui->tableWidget->columnCount();i++){//变成不可编辑
            QTableWidgetItem *item_t = ui->tableWidget->item(row, i);
            if(i!=1)
                item_t->setFlags(item_t->flags() & (~Qt::ItemIsEditable));
        }
    }
}

void ProgramData_Alter::TableWidgetSetRowCount(int RowCount)//设置行数
{
    ui->tableWidget->setRowCount(RowCount);
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_Alter::TableWidgetInsertRow(int Row)
{
    ui->tableWidget->insertRow(Row);//插入一行
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

void ProgramData_Alter::TableWidgetRemoveRow(int Row)
{
    ui->tableWidget->removeRow(Row);//删除一行
    TableWidgetRowCount = ui->tableWidget->rowCount();
}

//void ProgramData_Alter::TableWidgetCellDoubleClicked(int row,int column)
//{
//    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);
//    if(itemData == NULL)
//        return ;
//    TableWidgetCurrentRow = row;
//    TableWidgetCurrentColumn = column;
//    emit TableWidgetCellDoubleClicked_SIG(row,column,itemData->text());
//}

void ProgramData_Alter::TableWidgetCellPressed(int row,int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);
    if(itemData == NULL)
        return ;
    TableWidgetCurrentRow = row;
    TableWidgetCurrentColumn = column;
    emit TableWidgetCellPressed_SIG(row,column,itemData->text());
}

void ProgramData_Alter::TableWidgetAlterCurrentItem(QString str)
{
    QTableWidgetItem *item = ui->tableWidget->
            item(ui->tableWidget->currentRow(),ui->tableWidget->currentColumn());

    item->setText(str);
}

void ProgramData_Alter::TableWidgetSelectRow(int row)
{
    ui->tableWidget->selectRow(row);
}

QString ProgramData_Alter::TableWidgetItemQString(int row,int column)//指定某行某列的内容
{
    return ui->tableWidget->item(row,column)->text();
}
