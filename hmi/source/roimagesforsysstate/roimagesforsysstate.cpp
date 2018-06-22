#include "header/roimagesforsysstate/roimagesforsysstate.h"
#include "ui_roimagesforsysstate.h"

RoImagesForSysState::RoImagesForSysState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoImagesForSysState)
{
    ui->setupUi(this);
    ui->label->resize(IMAGEFORCOORDWIDTH,IMAGEFORCOORDHEIGHT);
    ui->label->resize(IMAGEFORCOORDWIDTH,IMAGEFORCOORDHEIGHT);

    image = new QImage();

//    image->load("./../RobotViews/RoResource/images/MOVE-C.BMP");//"./../RobotViews/RoResource/images/MOVE-C.BMP"
//    image->load(":/images/bin/resource/images/a.png");

    ui->label->setStyleSheet("border:2px solid blue;");//边框颜色

    ui->label->setPixmap(QPixmap::fromImage(*image));
}

RoImagesForSysState::~RoImagesForSysState()
{
    delete ui;
    delete image;
}
