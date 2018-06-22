#include "header/ropageoption/roprogram/RoProgram.h"
#include "ui_RoProgram.h"

RoProgram::RoProgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoProgram)
{
    ui->setupUi(this);

    Init();
}

RoProgram::~RoProgram()
{
    delete ui;
}

void RoProgram::Init()
{
    ViewInit();
    ConnectInit();

    ShowFileName();

    ui->stackedWidget->setCurrentIndex(0);
}

void RoProgram::ShowFileName()
{
    /*显示文件名的步骤
    1、清除表格
    2、设置行数
    3、设置表格内容
    4、高亮第一行
    */
    bool ok;
    QString path = "D:/MyStudyForQT/Practice/newhmi/hmi_windows/robhmi/hmi/bin/example/";

    DirSuffixFIFO SuffixFIFO = HMI_FindFileBySuffix(path.toLocal8Bit().data(),
                                                    "pgf",&ok);;	//目录下某后缀信息

    ProChoose->TableWidgetClear();
    ProChoose->TableWidgetSetRowCount(SuffixFIFO.FileNum);
    for(int i = 0 ;i<SuffixFIFO.FileNum;i++){
        ProChoose->TableWidgetSetItem(i,0,new QTableWidgetItem("ASDF"));
        ProChoose->TableWidgetSetItem
                (i,1,new QTableWidgetItem(QString(SuffixFIFO.FileName[i])));
    }
    ProChoose->TableWidgetSelectRow(vProChoose);
}

void RoProgram::ViewInit()
{
    ProChoose = new ProgramChoose;
    ProShow = new ProgramShow;    
    ProModule = new ProgramModule;//模块
    ProRoupro = new ProgramRoutinePro;//例行程序

    robRM = new robResouceManage;
    Key = new vkeyworld;

    ui->stackedWidget->addWidget(ProChoose);
    ui->stackedWidget->addWidget(ProShow);
    ui->stackedWidget->addWidget(ProModule);
    ui->stackedWidget->addWidget(ProRoupro);
    ui->stackedWidget->addWidget(robRM);
    ui->stackedWidget->addWidget(Key);
}

void RoProgram::ConnectInit()
{
    connect(ProChoose,SIGNAL(TableWidgetCellClicked_SIG(int,int,QString,QString)),
            this,SLOT(do_ProChooseTableWidgetCellClicked(int,int,QString,QString)));
    connect(ProChoose,SIGNAL(BtnOpenClicked_SIG(int,int,QString,QString)),
            this,SLOT(do_ProChooseTableWidgetCellClicked(int,int,QString,QString)));

    connect(ProShow,SIGNAL(Btn_MissionAndProClicked_SIG()),
            this,SLOT(do_MissionAndProClicked()));
    connect(ProShow,SIGNAL(Btn_ModuleClicked_SIG()),
            this,SLOT(do_btnModuleClicked()));
    connect(ProShow,SIGNAL(Btn_RoutineProClicked_SIG()),
            this,SLOT(do_btnRoutineProClicked()));

    connect(ProModule,SIGNAL(BtnBackClicked_SIG()),this,SLOT(do_btnBackClicked()));
    connect(ProRoupro,SIGNAL(BtnBackClicked_SIG()),this,SLOT(do_btnBackClicked()));

    connect(ProChoose->menu,SIGNAL(triggered(QAction*)),this,SLOT(do_MenuTriggered(QAction*)));

    connect(robRM,SIGNAL(btnOkClicked_SIG()),this,SLOT(do_robRMbtnOkClicked()));
    connect(robRM,SIGNAL(btnCancelClicked_SIG()),this,SLOT(do_robRMbtnCancelClicked()));
    connect(robRM,SIGNAL(btnNewClicked_SIG()),this,SLOT(do_robRMbtnNewClicked()));
    connect(robRM,SIGNAL(btnOpenKeyClicked_SIG()),this,SLOT(do_robRMbtnOpenKeyClicked()));

    connect(Key,SIGNAL(sig_ok(QString)),this,SLOT(do_KeyOkClicked(QString)));
    connect(Key,SIGNAL(sig_cancel()),this,SLOT(do_KeyCancelClcked()));
}
