#include "header/rostatebar/rostatebar.h"
#include "ui_rostatebar.h"
#include <QDebug>

rostatebar::rostatebar(romenu *menu,QStackedWidget *stack, roClose *closeview,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rostatebar)
{
    ui->setupUi(this);

    this->resize(STATEBARWIDTH,STATEBARHEIGHT);

    this->menu = menu;
    this->stack = stack;

    Init();
    connect(closeview,SIGNAL(closeviewflag()),this,SLOT(closeView()));
}

rostatebar::~rostatebar()
{
    delete ui;
}

void rostatebar::Init()
{
    btnlist = btnInit();

    ListStr = ListStrInit();

    btnShowList.clear();

    HideAllBtn();
    ConnectInit();
}

void rostatebar::ConnectInit()
{
    connect(menu,SIGNAL(sendmenu(int)),this,SLOT(Showbtn(int)));

    for(int i = 0 ;i<btnlist.count();i++)
        connect(btnlist.at(i),SIGNAL(clicked()),this,SLOT(ChangeView()));
}

//将ui->widget_digit所有按钮装入一个Qlist中
QList<QPushButton*> rostatebar::btnInit()
{
    QList<QPushButton*> list;
    list = ui->widget_digit->findChildren<QPushButton*>();
    return list;
}

//保存菜单界面的ACtion字符后面加"..."
QList <QString > rostatebar::ListStrInit()
{
    QList <QString > list;
    for(int i=0;i<this->menu->menu->actions().count();i++)
        list.append(this->menu->menu->actions().at(i)->text()+"...");

    return list;
}

void rostatebar::HideAllBtn()//隐藏ui->widget_digit所有的按钮
{
    for(int i = 0 ;i< btnlist.count();i++)
        btnlist.at(i)->hide();
}

void rostatebar::getBtnStyle(int num)//获取焦点  即按钮变色
{
    btnlist.at(num)->setFocus();//聚焦
    for(int i =0;i<btnlist.count()-1;i++){
            btnlist.at(i)->setStyleSheet("border:1px groove gray;border-radius:10px;\
                                padding:4px 4px;background-color: rgb(250,235,215);");
    }
    btnlist.at(num)->setStyleSheet("border:4px groove gray;border-radius:10px;\
                        padding:4px 4px;background-color: rgb(105,105,105);");
}

void rostatebar::Showbtn(int Index)
{
    if(btnShowList.count()>btnlist.count()-1)
        return;//改,报警
    //先判断是否已打开一个相同的界面(先不管)
    btnlist.at(btnShowList.count())->show();    //显示
    btnlist.at(btnShowList.count())->setText(ListStr.at(Index));//设置文字
    getBtnStyle(btnShowList.count());
    btnShowList.append(btnlist.at(btnShowList.count()));//显示按钮列表+1
}

void rostatebar::ChangeView()
{
    if(btnShowList.isEmpty())//当显示的按键列表为空时,显示GSK logo;
        stack->setCurrentIndex(0);
    for(int i = 0 ,index = -1 ;i<btnShowList.count();i++){
        if(btnShowList.at(i)->hasFocus()){
            //根据被按下按钮的text,在ListStr排位来确定要切换的界面
            stack->setCurrentIndex(ListStr.lastIndexOf(btnShowList.at(i)->text()));
            getBtnStyle(i);
            index = 0;
        }else if(i==btnShowList.count()-1&&index==-1){//说明没聚点
            getBtnStyle(i/*btnShowList.lastIndexOf(btnShowList.last())*/);//聚焦最后一个
            stack->setCurrentIndex(ListStr.lastIndexOf(btnShowList.at(i)->text()));//并显示最后一个界面
        }
    }
}

void rostatebar::closeView()
{
    if(btnShowList.isEmpty())//当显示的按键列表为空时,显示GSK logo;
        return;

    for(int i = 0,index = -1 ;i<btnShowList.count();i++){
        if(btnShowList.at(i)->hasFocus()){
            stack->widget(ListStr.lastIndexOf(btnShowList.at(i)->text()))->close();
            for(index = i;index<btnShowList.count()-1;index++)
                btnShowList.at(index)->setText(btnShowList.at(index+1)->text());
        }
    }
    btnShowList.last()->close();
    btnShowList.removeLast();

    ChangeView();//聚点改变界面改变
}
