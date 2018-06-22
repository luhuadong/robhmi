#include "ProgramShow.h"
#include "ui_ProgramShow.h"

void ProgramShow::Init()
{
    LineList.clear();
    ui->stackedWidget->hide();

    TextBrowserInit();
    ConnectInit();
}

void ProgramShow::BtnInit()
{

}

void ProgramShow::TextBrowserInit()
{
    //不要垂直滚动条
    ui->textBrowser_line->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //不要水平滚动条
    ui->textBrowser_line->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->textBrowser_ShowPro->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //不要水平滚动条
    ui->textBrowser_ShowPro->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //不自动换行
    ui->textBrowser_ShowPro->setWordWrapMode(QTextOption::NoWrap);
    ui->textBrowser_line->setWordWrapMode(QTextOption::NoWrap);

    ui->textBrowser_line->setDisabled(true);
}

void ProgramShow::ConnectInit()
{
    connect(ui->Btn_MissionAndPro,SIGNAL(clicked()),this,SIGNAL(Btn_MissionAndProClicked_SIG()));
    connect(ui->Btn_Module,SIGNAL(clicked()),this,SIGNAL(Btn_ModuleClicked_SIG()));
    connect(ui->Btn_RoutinePro,SIGNAL(clicked()),this,SIGNAL(Btn_RoutineProClicked_SIG()));
    connect(ui->Btn_AddOrder,SIGNAL(clicked()),this,SLOT(do_BtnAddOrderClicked()));
    connect(ui->Btn_Edit,SIGNAL(clicked()),this,SLOT(do_BtnEditClicked()));
    connect(ui->Btn_Debug,SIGNAL(clicked()),this,SLOT(do_BtnDebugClicked()));
    connect(ui->Btn_AlterPos,SIGNAL(clicked()),this,SLOT(do_BtnAlterPosClicked()));
    connect(ui->Btn_HideDeclare,SIGNAL(clicked()),this,SLOT(do_BtnHideDeclareClicked()));
    connect(ui->Btn_HideDeclare,SIGNAL(clicked()),this,SIGNAL(Btn_HideDeclareClicked_SIG()));

    connect(ui->textBrowser_ShowPro->verticalScrollBar(),
            SIGNAL(valueChanged(int)),this,SLOT(do_VerticalValueChanged(int)));

    connect(ui->textBrowser_ShowPro->document(),
            SIGNAL(blockCountChanged(int)),this,SLOT(do_blockCountChanged(int)));
}
