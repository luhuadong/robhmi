#include "header/ropageoption/AutoProduct/AutoProduct.h"
#include "ui_AutoProduct.h"

AutoProduct::AutoProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoProduct)
{
    ui->setupUi(this);

    Init();
}

AutoProduct::~AutoProduct()
{
    delete ui;
}

void AutoProduct::Init()
{
//    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);
//    LineList.clear();
//    ui->stackedWidget->hide();

    TextBrowserInit();
    ConnectInit();
}

void AutoProduct::TextBrowserInit()
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

void AutoProduct::ConnectInit()
{
    connect(ui->btn_Debug,SIGNAL(clicked()),this,SIGNAL(btn_DebugClicked_SIG()));
    connect(ui->btn_load,SIGNAL(clicked()),this,SIGNAL(btn_loadClicked_SIG()));
    connect(ui->btn_PPtoMain,SIGNAL(clicked()),this,SIGNAL(btn_PPtoMainClicked_SIG()));

    connect(ui->textBrowser_ShowPro->verticalScrollBar(),
            SIGNAL(valueChanged(int)),this,SLOT(do_VerticalValueChanged(int)));

    connect(ui->textBrowser_ShowPro->document(),
            SIGNAL(blockCountChanged(int)),this,SLOT(do_blockCountChanged(int)));
}

void AutoProduct::do_VerticalValueChanged(int value)
{
    if(ui->textBrowser_ShowPro->verticalScrollBar()->value() != value)
        ui->textBrowser_line->verticalScrollBar()->
                setValue(ui->textBrowser_ShowPro->verticalScrollBar()->value());

    ui->textBrowser_line->verticalScrollBar()->setValue(value);
}

void AutoProduct::do_blockCountChanged(int )
{
    ui->textBrowser_line->verticalScrollBar()->
            setValue(ui->textBrowser_ShowPro->verticalScrollBar()->value());
}
