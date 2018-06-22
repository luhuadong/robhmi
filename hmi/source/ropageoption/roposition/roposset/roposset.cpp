#include "header/ropageoption/roposition/roposset/roposset.h"
#include "ui_roposset.h"
#include <QDebug>

roposset::roposset(QPushButton *btn, int robtnNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roposset)
{
    ui->setupUi(this);

    QPalette p = this->palette();
    p.setBrush(QPalette::Window,Qt::white);
    this->setPalette(p);//背景色

    btninit();
    labelinit();
    setbtn(btn,robtnNum);
}

roposset::~roposset()
{
    delete ui;
}

void roposset::setbtn(QPushButton *btn,int robtnNum)
{
    ui->label_current->setText(btn->text());

    switch (robtnNum) {
    case 0://坐标系
         coord();
        break;
    case 1://设置轴
        setaxis();
        break;
    case 2://设置轴速度
        setaxisspeed();
        break;
    case 3://打开工具坐标数据
//        lockoper();
        break;
    case 4://打开工件坐标数据
//        incr();
        break;
    case 5://操作杆锁定
        lockoper();
        break;
    case 6://增量
        incr();
        break;

    default:
        break;
    }

    int Num = 0;
    for(labellist_i=labellist.begin();labellist_i!=labellist.end();++labellist_i)
    {
        QLabel *label = *labellist_i;
        if(btn->text() == label->text()){
            getBtnFocus(Num);
            StrEnsure = ui->label_current->text();
            btnNum = Num;
        }
        Num++;
    }
}

void roposset::btninit()
{
    btnlist.append(ui->pushButton_1);
    btnlist.append(ui->pushButton_2);
    btnlist.append(ui->pushButton_3);
    btnlist.append(ui->pushButton_4);

    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;
        connect(btn,SIGNAL(clicked()),this,SLOT(sbtn()));
    }
}

void roposset::labelinit()
{
    labellist.append(ui->label_1);
    labellist.append(ui->label_2);
    labellist.append(ui->label_3);
    labellist.append(ui->label_4);
}

void roposset::sbtn()
{
    int Num = 0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;

        if(btn->hasFocus()){
            getBtnFocus(Num);
            ui->label_current->setText(labellist.at(Num)->text());
            StrEnsure = ui->label_current->text();
            btnNum = Num;
            break;
        }
        Num++;
    }
}

void roposset::getBtnFocus(int num)//获取焦点  即按钮变色
{
    int j=0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;

        if(num == j)
        {
            btn->setFocus();
            btn->setStyleSheet("background-color: rgb(255, 55, 15);");
        }
        else
        {
            btn->clearFocus();
            btn->setStyleSheet("background-color: rgb(135,206,250);");
        }
        j++;
    }
}

void roposset::coord()
{
    QString coordimages[] = {
        "./resource/images/a.png",
        "./resource/images/b.png",
        "./resource/images/c.png",
        "./resource/images/d.png",
    };

    QString coordtext[] = {
        tr("基坐标"),
        tr("工具坐标"),
        tr("用户坐标"),
        tr("用户坐标"),
    };

    int Num = 0;
    for(labellist_i=labellist.begin();labellist_i!=labellist.end();++labellist_i)
    {
        QLabel *label = *labellist_i;
        label->setText(coordtext[Num]);
        Num++;
    }

    QPixmap pixmap;
    Num = 0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;
        pixmap.load(coordimages[Num]);

        btn->setIcon(pixmap);
        btn->setIconSize(QSize(ui->pushButton_1->width(),ui->pushButton_1->height()));
        Num++;
    }
}

void roposset::setaxis()
{
    QString setaxisimages[] = {
        "./resource/images/a.png",
        "./resource/images/b.png",
        "./resource/images/c.png",
        "./resource/images/d.png",
    };

    QString setaxistext[] = {
        tr("轴1-3"),
        tr("轴4-6"),
        tr("线性"),
        tr("重定位"),
    };

    int Num = 0;
    for(labellist_i=labellist.begin();labellist_i!=labellist.end();++labellist_i)
    {
        QLabel *label = *labellist_i;
        label->setText(setaxistext[Num]);
        Num++;
    }

    QPixmap pixmap;

    Num = 0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;
        pixmap.load(setaxisimages[Num]);

        btn->setIcon(pixmap);
        btn->setIconSize(QSize(ui->pushButton_1->width(),ui->pushButton_1->height()));
        Num++;
    }
}

void roposset::setaxisspeed()
{
    QString setaxisspeedimages[] = {
        "./resource/images/speed_1.png",
        "./resource/images/speed_2.png",
        "./resource/images/speed_5.png",
        "./resource/images/speed_all.png",
    };

    QString setaxisspeedtext[] = {
        tr("10%"),
        tr("20%"),
        tr("50%"),
        tr("100%"),
    };

    int Num = 0;
    for(labellist_i=labellist.begin();labellist_i!=labellist.end();++labellist_i)
    {
        QLabel *label = *labellist_i;
        label->setText(setaxisspeedtext[Num]);
        Num++;
    }

    QPixmap pixmap;

    Num = 0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;
        pixmap.load(setaxisspeedimages[Num]);

        btn->setIcon(pixmap);
        btn->setIconSize(QSize(ui->pushButton_1->width(),ui->pushButton_1->height()));
        Num++;
    }
}

void roposset::lockoper()
{
    QString lockoperimages[] = {
        "./resource/images/a.png",
        "./resource/images/b.png",
        "./resource/images/c.png",
        "./resource/images/d.png",
    };

    QString lockopertext[] = {
        tr("无"),
        tr("水平方向"),
        tr("垂直方向"),
        tr("旋转"),
    };

    int Num = 0;
    for(labellist_i=labellist.begin();labellist_i!=labellist.end();++labellist_i)
    {
        QLabel *label = *labellist_i;
        label->setText(lockopertext[Num]);
        Num++;
    }
    QPixmap pixmap;

     Num = 0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;
        pixmap.load(lockoperimages[Num]);

        btn->setIcon(pixmap);
        btn->setIconSize(QSize(ui->pushButton_1->width(),ui->pushButton_1->height()));
        Num++;
    }
}

void roposset::incr()
{
    QString incrimages[] = {
        "./resource/images/a.png",
        "./resource/images/b.png",
        "./resource/images/c.png",
        "./resource/images/d.png",
    };

    QString incrtext[] = {
        tr("无"),
        tr("小"),
        tr("中"),
        tr("大"),
    };

    int Num = 0;
    for(labellist_i=labellist.begin();labellist_i!=labellist.end();++labellist_i)
    {
        QLabel *label = *labellist_i;
        label->setText(incrtext[Num]);
        Num++;
    }
    QPixmap pixmap;

    Num = 0;
    for(btnlist_i=btnlist.begin();btnlist_i!=btnlist.end();++btnlist_i)
    {
        QPushButton *btn = *btnlist_i;
        pixmap.load(incrimages[Num]);

        btn->setIcon(pixmap);
        btn->setIconSize(QSize(ui->pushButton_1->width(),ui->pushButton_1->height()));
        Num++;
    }
}

void roposset::on_pushButton_ok_clicked()
{
    emit sendbtn(btnNum);
    this->close();
}

void roposset::on_pushButton_cancel_clicked()
{
    this->close();
}
