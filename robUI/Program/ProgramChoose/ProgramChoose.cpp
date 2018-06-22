#include "ProgramChoose.h"
#include "ui_ProgramChoose.h"

ProgramChoose::ProgramChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramChoose)
{
    ui->setupUi(this);

    Init();
}

ProgramChoose::~ProgramChoose()
{
    delete ui;
}

void ProgramChoose::Init()
{
    BtnInit();
    TableWidgetInit();
    ConnectInit();

    setChoosePro();//默认处于这个界面
}

void ProgramChoose::BtnInit()
{
    ui->Btn_File->setFocusPolicy(Qt::NoFocus);
    ui->Btn_Open->setFocusPolicy(Qt::NoFocus);
    ui->Btn_ShowModule->setFocusPolicy(Qt::NoFocus);

    QAction *newPro = new QAction(tr("新建程序..."),this);
    QAction *loadPro = new QAction(tr("加载程序..."),this);
    QAction *savePro = new QAction(tr("另存程序为..."),this);
    QAction *renamePro = new QAction(tr("重命名程序..."),this);
    QAction *deletePro = new QAction(tr("删除程序..."),this);

    menu=new QMenu(this);

    menu->addAction(newPro);
    menu->addAction(loadPro);
    menu->addAction(savePro);
    menu->addAction(renamePro);
    menu->addAction(deletePro);
}

void ProgramChoose::TableWidgetInit()
{
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
    //单击选择一行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //总是聚焦
    ui->tableWidget->setFocusPolicy(Qt::WheelFocus);
}

void ProgramChoose::ConnectInit()
{
    connect(ui->Btn_File,SIGNAL(clicked()),this,SLOT(do_BtnFileClicked()));
    connect(ui->Btn_ShowModule,SIGNAL(clicked()),this,SIGNAL(BtnShowModuleClicked_SIG()));
    connect(ui->Btn_Open,SIGNAL(clicked()),this,SLOT(do_BtnOpenClicked()));

    connect(menu,SIGNAL(triggered(QAction*)),this,SIGNAL(MenuActionTriggered(QAction *)));
}

void ProgramChoose::setMissionAndPro()
{
    ui->label_Exp->setText(tr("任务与程序"));
    ui->Btn_File->setHidden(false);
    ui->Btn_Open->setHidden(false);
    ui->Btn_ShowModule->setHidden(false);
    disconnect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,
            SLOT(do_TableWidgetCellClicked(int ,int)));
}

void ProgramChoose::setChoosePro()
{
    ui->label_Exp->setText(tr("从列表中选择一个任务以打开程序。"));
    ui->Btn_File->setHidden(true);
    ui->Btn_Open->setHidden(true);
    ui->Btn_ShowModule->setHidden(true);
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,
            SLOT(do_TableWidgetCellClicked(int ,int)));
}

void ProgramChoose::do_TableWidgetCellClicked(int row,int column)
{
    QTableWidgetItem *itemData = ui->tableWidget->item(row,column);
    if(itemData == NULL)
        return ;

    column = 0;
    QTableWidgetItem *itemMisson = ui->tableWidget->item(row,column);

    column = 1;
    QTableWidgetItem *itemProgram = ui->tableWidget->item(row,column);

    emit TableWidgetCellClicked_SIG(row,column,itemMisson->text(),
                                    itemProgram->text());    
}

void ProgramChoose::do_BtnOpenClicked()
{
    QTableWidgetItem *itemMisson = ui->tableWidget->item(ui->tableWidget->currentRow(),0);

    QTableWidgetItem *itemProgram = ui->tableWidget->item(ui->tableWidget->currentRow(),1);
    if(itemMisson==NULL||itemProgram==NULL)
        return;

    emit BtnOpenClicked_SIG(ui->tableWidget->currentRow(),ui->tableWidget->currentColumn(),
                            itemMisson->text(),itemProgram->text());
}

void ProgramChoose::do_BtnFileClicked()
{
    menu->setFixedWidth(ui->Btn_File->size().width());

    QPoint pos;
    pos.setX(0);
    pos.setY(-menu->sizeHint().height());

    menu->exec(ui->Btn_File->mapToGlobal(pos));
}

/*显示文件名的步骤
1、清除表格
2、设置行数
3、设置表格内容
4、高亮第一行
*/
void ProgramChoose::TableWidgetSelectRow(int Row)
{
    ui->tableWidget->selectRow(Row);
}

void ProgramChoose::TableWidgetSetRowCount(int Row)
{
    ui->tableWidget->setRowCount(Row);
}

void ProgramChoose::TableWidgetClear()
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);
}

void ProgramChoose::TableWidgetSetItem(int row, int column, QTableWidgetItem *item)
{
    ui->tableWidget->setItem(row,column,item);
}

void ProgramChoose::setItemText(int row, int column, QString str)
{
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    if(item==NULL)
        return;

    item->setText(str);
}
