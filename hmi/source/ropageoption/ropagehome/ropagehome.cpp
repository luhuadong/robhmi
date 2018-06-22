#include "header/ropageoption/ropagehome/ropagehome.h"
#include "ui_ropagehome.h"

RoPageHome::RoPageHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoPageHome)
{
    ui->setupUi(this);

    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);
    ui->label->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    image = new QImage();

    image->load(":/images/bin/resource/images/GSK_800_500.bmp");
//    image->load("./resource/images/GSK_800_500.bmp");
    ui->label->setPixmap(QPixmap::fromImage(*image));
}

RoPageHome::~RoPageHome()
{
    delete ui;
    delete image;
}
