#include "skeyWorld.h"
#include "ui_skeyWorld.h"
//纯数字虚拟键盘
skeyWorld::skeyWorld(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::skeyWorld)
{
    ui->setupUi(this);

    Init();
}

skeyWorld::~skeyWorld()
{
    delete ui;
}

void skeyWorld::Init()
{
    btnInit();

    ConnectInit();
}

void skeyWorld::btnInit()
{
    btnlist = this->findChildren<QPushButton*>(QString(), Qt::FindChildrenRecursively);

    for(int i = 0;i<btnlist.count();i++){
        btnlist.at(i)->setFocusPolicy(Qt::NoFocus);
    }
}

void skeyWorld::ConnectInit()
{
    connect(ui->pushButton_cancel,SIGNAL(clicked()),this,SLOT(vkeyClose()));
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(zeroBtnClicked()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(oneBtnClicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(twoBtnClicked()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(threeBtnClicked()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(fourBtnClicked()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(fiveBtnClicked()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(sixBtnClicked()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(sevenBtnClicked()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(eightBtnClicked()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(nineBtnClicked()));
    connect(ui->pushButton_del,SIGNAL(clicked()),this,SLOT(delBtnClicked()));
    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(okClicked()));

    connect(ui->pushButton_add_red,SIGNAL(clicked()),this,SLOT(add_redBtnClicked()));
    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(dotBtnClicked()));

    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(clrBtnClicked()));
}

void skeyWorld::vkeyClose()
{
    emit btnClicked_SIG(st);
    emit cancelBtn_SIG();
    this->close();
}

void skeyWorld::zeroBtnClicked()//单击‘0’按钮触发的事件
{
    vKeyStr = vKeyStr+"0";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::oneBtnClicked()//单击‘1’按钮
{
    vKeyStr = vKeyStr+"1";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::twoBtnClicked()//单击'2'按钮
{
    vKeyStr = vKeyStr+"2";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::threeBtnClicked()//单机'3'按钮
{
    vKeyStr = vKeyStr+"3";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::fourBtnClicked()//4
{
    vKeyStr = vKeyStr+"4";    
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::fiveBtnClicked()//5
{
    vKeyStr = vKeyStr+"5";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::sixBtnClicked()//6
{
    vKeyStr = vKeyStr+"6";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::sevenBtnClicked()//7
{
    vKeyStr = vKeyStr+"7";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::eightBtnClicked()//8
{
    vKeyStr = vKeyStr+"8";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::nineBtnClicked()//9
{
    vKeyStr = vKeyStr+"9";
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::delBtnClicked()//退格键
{
    QString s = vKeyStr ;
    int len = s.length();
    QString s2 = s.remove(len-1,1);

    vKeyStr = s2;
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::dotBtnClicked()//.
{
    for(int i = 0;i<vKeyStr.count();i++){
        if(vKeyStr.at(i)=='.'){
            break;
        }else if(i == vKeyStr.count()-1)
             vKeyStr = vKeyStr+".";
    }

    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::add_redBtnClicked()//+/-
{
    if(vKeyStr.isEmpty())
        vKeyStr = vKeyStr.insert(0,QString("-"));
    else{
        if(vKeyStr.at(0) == '-')
            vKeyStr = vKeyStr.remove(0,1);
        else
            vKeyStr = vKeyStr.insert(0,QString("-"));
    }

    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::okClicked()//ok
{
    emit okBtn_SIG();
    this->close();
}

void skeyWorld::clrBtnClicked()//clear
{
    vKeyStr.clear();
    emit btnClicked_SIG(vKeyStr);
}

void skeyWorld::skeyWorldInput(QString str)
{
    st = str;
    vKeyStr.clear();
}
