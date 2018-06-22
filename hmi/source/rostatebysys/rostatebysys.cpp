#include "header/rostatebysys/rostatebysys.h"
#include "ui_rostatebysys.h"

RoStateBySys::RoStateBySys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoStateBySys)
{
    ui->setupUi(this);
    this->resize(STATEBYSYSWIDTH,STATEBYSYSHEIGHT);
    ui->pushButton->resize(this->width(),this->height());

    ui->pushButton->setCheckable(true);
    ui->pushButton->setText(tr("报警"));

//    ui->pushButton->setStyleSheet("border:2px solid gray;\
//                       border-radius: 0px;");
}

RoStateBySys::~RoStateBySys()
{
    delete ui;
}
