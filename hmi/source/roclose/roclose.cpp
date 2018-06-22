#include "header/roclose/roclose.h"
#include "ui_roclose.h"
#include <QDebug>

roClose::roClose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roClose)
{
    ui->setupUi(this);
    this->resize(CLOSEBTNWIDTH,CLOSEBTNHEIGHT);
    ui->pushButton_close->resize(this->width(),this->height());

    ui->pushButton_close->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_close->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
}

roClose::~roClose()
{
    delete ui;
}

void roClose::on_pushButton_close_clicked()
{
    emit closeviewflag();
}
