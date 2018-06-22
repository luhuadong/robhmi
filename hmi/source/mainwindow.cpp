#include "header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(WIDGETWIDTH,WIDGETHEIGHT);
    this->setFixedSize(WIDGETWIDTH, WIDGETHEIGHT);  // by LHD (2015.11.17)
//    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowIcon(QIcon("./resource/images/bmp30.bmp"));

    delete centralWidget();
//    loadSettings();

    Init();
}

void MainWindow::ViewInit()
{
    LeftWidget = new QWidget(splitterMain);
    LeftWidget->resize(LEFTWIDGETWIDTH,LEFTWIDGETHEIGHT);
    Menu = new romenu(LeftWidget);
    ImageForCoord = new RoImagesForSysState(LeftWidget);
    ImageForOrder = new RoImagesForSysState(LeftWidget);
    ImageForState = new RoImagesForSysState(LeftWidget);
    ImageForSpeed = new RoImagesForSysState(LeftWidget);
    roStateBySys = new RoStateBySys(LeftWidget);
    rclose = new roClose(LeftWidget);
    ropageoption = new RoPageOption(Menu,LeftWidget);
    statebar = new rostatebar(Menu,ropageoption->stack,rclose,LeftWidget);

    Menu->setGeometry(QRect(MENU_X,MENU_Y,MENUWIDTH,MENUHEIGHT));
    ImageForCoord->setGeometry(QRect(IMAGEFORCOORD_X,IMAGEFORCOORD_Y,IMAGEFORCOORDWIDTH,IMAGEFORCOORDHEIGHT));
    ImageForOrder->setGeometry(QRect(IMAGEFORORDER_X,IMAGEFORORDER_Y,IMAGEFORORDERWIDTH,IMAGEFORORDERHEIGHT));
    ImageForState->setGeometry(QRect(IMAGEFORSTATE_X,IMAGEFORSTATE_Y,IMAGEFORSTATEWIDTH,IMAGEFORSTATEHEIGHT));
    ImageForSpeed->setGeometry(QRect(IMAGEFORSPEED_X,IMAGEFORSPEED_Y,IMAGEFORSPEEDWIDTH,IMAGEFORSPEEDHEIGHT));
    roStateBySys->setGeometry(QRect(STATEBYSYS_X,STATEBYSYS_Y,STATEBYSYSWIDTH,STATEBYSYSHEIGHT));
    rclose->setGeometry(QRect(CLOSEBTN_X,CLOSEBTN_Y,CLOSEBTNWIDTH,CLOSEBTNHEIGHT));
    ropageoption->setGeometry(QRect(PAGEOPTION_X,PAGEOPTION_Y,PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT));
    statebar->setGeometry((QRect(STATEBAR_X,STATEBAR_Y,STATEBARWIDTH,STATEBARHEIGHT)));


    RightWidget = new QWidget(splitterMain);
    RightWidget->resize(RIGHTWIDGETWIDTH,RIGHTWIDGETHEIGHT);
    rWidget = new rightWidget(RightWidget);

    QSplitterHandle *splitterHandle = splitterMain->handle(1);
    if(splitterHandle){
        splitterHandle->setDisabled(true);//分割线不可用,固定
    }
}

void MainWindow::splitterInit()
{
    splitterMain = new QSplitter(Qt::Horizontal,this);
    splitterMain->resize(this->width(),this->height());

    splitterMain->setHandleWidth(1);//分割线宽度
    //分割线颜色
    splitterMain->setStyleSheet("QSplitter::handle { background-color: black }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    splitterInit();
    ViewInit();
    ConnectInit();
}

void MainWindow::ConnectInit()
{
    connect(rWidget,SIGNAL(btnCloseClicked_SIG()),this,SLOT(do_RightWidgetBtnCloseClicked()));
    connect(rWidget,SIGNAL(btnMinimizeClicked_SIG()),this,SLOT(do_RightWidgetBtnMinimizeClicked()));
}

void MainWindow::loadSettings()
{
    QSettings *ConfigIni = new QSettings("./resource/ini/config.ini",
                                         QSettings::IniFormat,0);
    restoreGeometry(ConfigIni->value("geometry").toByteArray());
    restoreState(ConfigIni->value("windowState").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::saveSettings()
{
    QSettings *ConfigIni = new QSettings("./resource/ini/config.ini",
                                         QSettings::IniFormat,0);
    ConfigIni->setValue("geometry", saveGeometry());
    ConfigIni->setValue("windowState", saveState());

//    ConfigIni->beginGroup("SetPage");
//    ConfigIni->setValue("language",ropageoption->rPopData.SetPage.language);
//    ConfigIni->endGroup();
}

void MainWindow::do_RightWidgetBtnCloseClicked()
{
    this->close();
}

void MainWindow::do_RightWidgetBtnMinimizeClicked()
{
    this->showMinimized();
}
