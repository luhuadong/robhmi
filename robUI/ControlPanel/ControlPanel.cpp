#include "ControlPanel.h"
#include "ui_ControlPanel.h"
#include <QDebug>

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    Init();

    const QString Info[10][2] = {
       {tr("外观"),tr("自定义显示器")},{tr("监控"),tr("动作监控和执行设置")},
       {tr("FlexPendant"),tr("配置FlexPendant系统")},{tr("I/O"),tr("配置常用I/O信号")},
       {tr("语言"),tr("设置当前语言")},{tr("ProgKeys"),tr("配置可编程按键")},
       {tr("日期和时间"),tr("设置机器人控制器的日期和时间")},{tr("诊断"),tr("系统诊断")},
       {tr("配置"),tr("配置系统参数")},{tr("触摸屏"),tr("校准触摸屏")}
    };

    for(int i = 0 ;i <10 ;i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(Info[i][0]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Info[i][1]));
    }
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);
    ViewInit();
    TableWidgetInit();
    ConnectInit();
}

void ControlPanel::TableWidgetInit()
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
    //列数
    ui->tableWidget->setColumnCount(2);
    //表头名称
    QStringList header;
    header<<tr("名称")<<tr("备注");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //表头对齐方式
    ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    ui->tableWidget->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    //设置充满表宽度
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true) ;
    //设置表头不可点击（默认点击后进行排序）
    ui->tableWidget->horizontalHeader()->setDisabled(true);
    //设置间距
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40) ; //设置行距
    //列宽
//    ui->tableWidget->setColumnWidth(1,560);
    ui->tableWidget->setColumnWidth(0,240);
    //设置选中背景色
    ui->tableWidget->setStyleSheet("selection-background-color:green;") ;
    //设置行数
    ui->tableWidget->setRowCount(10);
    //设置点击聚集
    ui->tableWidget->setFocusPolicy(Qt::ClickFocus);
}

void ControlPanel::setPosText(QString str)
{
    ui->label_Pos->setText(ui->label_Pos->text().append(" - ").append(str));
}

void ControlPanel::ConnectInit()
{
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),
            this,SLOT(do_tableWidgetCellClicked(int,int)));

    connect(CPLanguage,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPConfign,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPAppearance,SIGNAL(btn_CancelClicked_SIG()),
            this,SLOT(do_btnCancelClicked()));
    connect(CPFlexPendant,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPTouchScreen,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPIO,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPMonitoring,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPProgKeys,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));    
    connect(CPDateTime,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
    connect(CPDiagnosis,SIGNAL(btn_CancelClicked_SIG()),
           this,SLOT(do_btnCancelClicked()));
}

void ControlPanel::do_tableWidgetCellClicked(int row,int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    if(item==NULL)
        return;

    ui->stackedWidget->setCurrentIndex(row+1);

    item = ui->tableWidget->item(row,0);

    setPosText(item->text());
}

void ControlPanel::ViewInit()
{
    CPAppearance = new Appearance;
    CPMonitoring = new Monitoring;
    CPFlexPendant = new FlexPendant;
    CPIO = new IO;
    CPLanguage = new Language;
    CPProgKeys = new ProgKeys;
    CPDateTime = new DateTime;
    CPDiagnosis = new Diagnosis;
    CPConfign = new Configuration;
    CPTouchScreen = new TouchScreen;

    ui->stackedWidget->addWidget(CPAppearance);
    ui->stackedWidget->addWidget(CPMonitoring);
    ui->stackedWidget->addWidget(CPFlexPendant);
    ui->stackedWidget->addWidget(CPIO);
    ui->stackedWidget->addWidget(CPLanguage);
    ui->stackedWidget->addWidget(CPProgKeys);
    ui->stackedWidget->addWidget(CPDateTime);
    ui->stackedWidget->addWidget(CPDiagnosis);
    ui->stackedWidget->addWidget(CPConfign);
    ui->stackedWidget->addWidget(CPTouchScreen);
}

void ControlPanel::do_btnCancelClicked()
{
    ui->stackedWidget->setCurrentIndex(CPanelWidget);
    ui->tableWidget->clearFocus();
    ui->tableWidget->clearSelection();

    ui->label_Pos->setText(tr("控制面板"));
}
