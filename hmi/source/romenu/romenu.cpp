#include "header/romenu/romenu.h"
#include "ui_romenu.h"
//#include <QTableWidget>

romenu::romenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::romenu)
{
    ui->setupUi(this);

    this->resize(MENUWIDTH,MENUHEIGHT);
    ui->pushButton->resize(this->width(),this->height());

    QAction *home = new QAction(tr("主页"),this);
    QAction *program = new QAction(tr("程序"),this);
    QAction *CP = new QAction(tr("控制面板"),this);
    QAction *alarm = new QAction(tr("报警"),this);
    QAction *position = new QAction(tr("位置"),this);
    QAction *ProData = new QAction(tr("程序数据"),this);
    QAction *IOput = new QAction(tr("输入输出"),this);
    QAction *BR = new QAction(tr("备份与恢复"),this);
    QAction *RManage = new QAction(tr("资源管理"),this);
    QAction *SysInfo = new QAction(tr("系统信息"),this);
    QAction *ParaSet = new QAction(tr("参数设置"),this);
    QAction *manualAction = new QAction(tr("手动操纵"), this);

    menu=new QMenu;
    menu->setFixedWidth(500);

    menu->addAction(home);
    menu->addAction(program);
    menu->addAction(CP);
    menu->addAction(alarm);
    menu->addAction(position);
    menu->addAction(ProData);
    menu->addAction(IOput);
    menu->addAction(BR);
    menu->addAction(RManage);
    menu->addAction(SysInfo);
    menu->addAction(ParaSet);
    menu->addAction(manualAction);

    ui->pushButton->setMenu(menu);

    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(showaction(QAction*)));
}

romenu::~romenu()
{
    delete ui;
}

void romenu::showaction(QAction *Action)
{
    for(int i = 0;i<menu->actions().count();i++){
        if(Action == menu->actions().at(i)){
            emit sendmenu(i);
            break;
        }
    }
}
