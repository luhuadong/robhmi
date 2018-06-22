#include "vkeyworld.h"
#include "ui_vkeyworld.h"

void vkeyworld::Init()
{
    ui->lineEdit->setFocus();
    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);

    btnInit();

    str = ui->lineEdit->text();
}

void vkeyworld::btnInit()
{
    btnList_digit = ui->widget_digit->findChildren<QPushButton *>();
    for(int i =0;i<btnList_digit.count();i++){
        connect(btnList_digit.at(i),SIGNAL(clicked()),this,SLOT(digitClicked()));
    }

    btnList_character_qp =
            ui->widget_character_qp->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);
    for(int i =0;i<btnList_character_qp.count();i++){
        connect(btnList_character_qp.at(i),SIGNAL(clicked()),this,SLOT(character_qpClicked()));
    }

    btnList_character_al =
            ui->widget_character_al->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);
    for(int i =0;i<btnList_character_al.count();i++){
        connect(btnList_character_al.at(i),SIGNAL(clicked()),this,SLOT(character_alClicked()));
    }

    btnList_character_zm =
            ui->widget_character_zm->findChildren<QPushButton *>(QString(), Qt::FindDirectChildrenOnly);
    for(int i =0;i<btnList_character_zm.count();i++){
        connect(btnList_character_zm.at(i),SIGNAL(clicked()),this,SLOT(character_zmClicked()));
    }

    btnList_symbol =
            ui->widget_symbol->findChildren<QPushButton *>(QString(),Qt::FindDirectChildrenOnly);
    for(int i = 0 ;i<btnList_symbol.count();i++){
        connect(btnList_symbol.at(i),SIGNAL(clicked()),this,SLOT(symbolClicked()));
    }

    ui->btn_CAP->setCheckable(true);
    ui->btn_Shift->setCheckable(true);

    connect(ui->btn_CAP,SIGNAL(clicked(bool)),this,SLOT(CAPClicked(bool)));//CAP键
    connect(ui->btn_Shift,SIGNAL(clicked(bool)),this,SLOT(ShiftClicked(bool)));//Shift键

    connect(this,SIGNAL(sig_Change_CAPModal(int)),this,SLOT(doChange_CAPModal(int)));//CAP
    connect(this,SIGNAL(sig_Change_ShiftModal(int)),this,SLOT(doChange_ShiftModal(int)));//Shift

    connect(ui->btn_Backspace,SIGNAL(clicked()),this,SLOT(BackspaceClicked()));//退格键
    connect(ui->btn_space,SIGNAL(clicked()),this,SLOT(spaceClicked()));//空格键

    //方向键
    connect(ui->btn_up,SIGNAL(clicked()),this,SLOT(upClicked()));//上
    connect(ui->btn_down,SIGNAL(clicked()),this,SLOT(downClicked()));//下
    connect(ui->btn_left,SIGNAL(clicked()),this,SLOT(leftClicked()));//左
    connect(ui->btn_right,SIGNAL(clicked()),this,SLOT(rightClicked()));//右

    connect(ui->btn_Home,SIGNAL(clicked()),this,SLOT(HomeClicked()));//Home
    connect(ui->btn_End,SIGNAL(clicked()),this,SLOT(EndClicked()));//End
}

