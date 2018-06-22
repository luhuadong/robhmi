#include "header/ropageoption/HMI_ParaSet/HMI_ParaSet.h"
#include "ui_HMI_ParaSet.h"

HMI_ParaSet::HMI_ParaSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HMI_ParaSet)
{
    ui->setupUi(this);

    Init();
}

HMI_ParaSet::~HMI_ParaSet()
{
    delete ui;
}

void HMI_ParaSet::Init()
{
    TableWidgetInit();
    ConnectInit();    

//    HMI_ParaReadFile();

    do_comboBoxIndexChanged(2);
}

void HMI_ParaSet::TableWidgetInit()
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

    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);

    ui->tableWidget->setColumnCount(3);
    QStringList header;

    header<<tr("名称")<<tr("值")<<tr("数据类型");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->horizontalHeader()->show();
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(ui->tableWidget->size().width()/ui->tableWidget->columnCount());
}

void HMI_ParaSet::ConnectInit()
{
    connect(ui->btn_acq,SIGNAL(clicked()),this,SLOT(do_btnAcqClicked()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(do_btnOkClicked()));

    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,
            SLOT(TableWidgetCellPressed(int,int)));
    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,
            SLOT(TableWidgetItemClicked(QTableWidgetItem*)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(do_comboBoxIndexChanged(int)));
}

void HMI_ParaSet::do_btnAcqClicked()
{

}

void HMI_ParaSet::do_btnOkClicked()
{

}

void HMI_ParaSet::TableWidgetCellPressed(int row,int column)
{
    QTableWidgetItem* item = ui->tableWidget->item(row,column);
    if(item==NULL)
        return;
}

void HMI_ParaSet::TableWidgetItemClicked(QTableWidgetItem* item)
{
    if(item==NULL)
        return;
}

void HMI_ParaSet::do_comboBoxIndexChanged(int index)
{
    SetLabelPosText(ui->comboBox->currentText());
    switch(index){
        case 0:ShowAcc();break;
        case 1:ShowWorldAcc();break;
        case 2:ShowSing();break;
        case 3:ShowCornerJointSpeedChange();break;
        case 4:ShowAccWay();break;
        case 5:ShowProgDisp();break;
    default:break;
    }

    QTableWidgetItem *item;
    for(int row = 0;row<ui->tableWidget->rowCount();row++){
        for(int column = 0;column<ui->tableWidget->columnCount();column++){//变成不可编辑
            item = ui->tableWidget->item(row, column);
            if(item==NULL)
                continue;
            if(column!=1)
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
        }
    }
}

void HMI_ParaSet::ShowAcc()//关节加速度
{
    clearTableWidget();
    ui->tableWidget->setRowCount(6);

    QString str[]={
        tr("加速度"),tr("减加速度"),tr("加加速度"),
        tr("到fine点的加加速度"),tr("最大加速度"),tr("最大减速度")
    };

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str[i]));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(QString::number(*MotSetData[i])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem("12"));
    }
}

void HMI_ParaSet::ShowWorldAcc()//笛卡尔加速度
{
    clearTableWidget();
    ui->tableWidget->setRowCount(6);

    QString str[]={
        tr("加速度"),tr("减加速度"),tr("加加速度"),
        tr("到fine点的加加速度"),tr("最大世界坐标系加速度"),tr("最大笛卡尔坐标系减速度")
    };

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str[i]));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(QString::number(*MotSetData[i+6])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem("12"));
    }
}

void HMI_ParaSet::ShowSing()//奇异点
{
    QString str[]={
        tr("工具方向发生偏移以避开奇异点"),
        tr("当5轴接近0度时，将4轴锁定在0或+-180。"),
        tr("不处理")
    };

    clearTableWidget();
    ui->tableWidget->setRowCount(3);


    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str[i]));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(QString::number(*MotSetData[i+6])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem("12"));
    }
}

void HMI_ParaSet::ShowCornerJointSpeedChange()//允许的拐角关节速度变化
{
    QList<QString> str;
    str.append(tr("允许的拐角关节速度变化"));
    clearTableWidget();
    ui->tableWidget->setRowCount(1);

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str.at(i)));
        ui->tableWidget->setItem(i,1,
                                 new QTableWidgetItem(QString::number(*MotSetData[i+6])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem("12"));
    }
}

void HMI_ParaSet::ShowAccWay()//机器人配置
{
    clearTableWidget();
}

void HMI_ParaSet::ShowProgDisp()//偏移参数
{
    clearTableWidget();
}

void HMI_ParaSet::clearTableWidget()
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);
}

//void HMI_ParaSet::TableWidgetSetItem(int row, int column, QTableWidgetItem *item)
//{
//    ui->tableWidget->setItem(row,column,item);

//    if(column==ui->tableWidget->columnCount()-1){
//        QTableWidgetItem *item_1 = ui->tableWidget->item(row, 1);

//        if(item_1->text()=="TRUE"||item_1->text()=="FALSE"){
//            for(int i = 0;i<ui->tableWidget->columnCount();i++){//变成不可编辑
//                QTableWidgetItem *item_t = ui->tableWidget->item(row, i);
//                item_t->setFlags(item_t->flags() & (~Qt::ItemIsEditable));
//            }
//        }else if(item_1->text().at(0)=='['&&//变成不可用
//                item_1->text().at(item_1->text().count()-1)==']'){
//            for(int i = 0;i<ui->tableWidget->columnCount();i++){
//                QTableWidgetItem *item_t = ui->tableWidget->item(row, i);
//                item_t->setFlags(item_t->flags() & (~Qt::ItemIsEnabled));
//            }
//        }

//        for(int i = 0;i<ui->tableWidget->columnCount();i++){//变成不可编辑
//            QTableWidgetItem *item_t = ui->tableWidget->item(row, i);
//            if(i!=1)
//                item_t->setFlags(item_t->flags() & (~Qt::ItemIsEditable));
//        }
//    }
//}

void HMI_ParaSet::SetLabelPosText(QString str)
{
    ui->label_Pos->setText(tr("参数设置 - ").append(str));
}
