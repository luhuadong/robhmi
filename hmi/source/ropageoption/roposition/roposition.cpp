#include "header/ropageoption/roposition/roposition.h"
#include "ui_roposition.h"

roposition::roposition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roposition)
{
    ui->setupUi(this);


    init();
    changedire();
}

void roposition::changedire()
{
    QString str4_6[] = {
        tr("5"),
        tr("4"),
        tr("6"),
    };

    QString str1_3[] = {
        tr("2"),
        tr("1"),
        tr("3"),
    };
    QString linear[] = {
        tr("X"),
        tr("Y"),
        tr("Z"),
    };

    for(int i= 3;i<6;i++)
    {
        QLabel *label = labellist.at(i);

        if(ui->btn_2_setaxis->text() == tr("轴1-3")){
            label->setText(str1_3[i-3]);

            ui->label_1_x->setText(tr("1:"));
            ui->label_2_y->setText(tr("2:"));
            ui->label_3_z->setText(tr("3:"));
            ui->label_4_q1->setText(tr("4:"));
            ui->label_5_q2->setText(tr("5:"));
            ui->label_6_q3->setText(tr("6:"));
            ui->label_7_q4->hide();
            ui->label_7_q4_data->hide();

        }
        else if(ui->btn_2_setaxis->text() == tr("轴4-6")){
            label->setText(str4_6[i-3]);

            ui->label_1_x->setText(tr("1:"));
            ui->label_2_y->setText(tr("2:"));
            ui->label_3_z->setText(tr("3:"));
            ui->label_4_q1->setText(tr("4:"));
            ui->label_5_q2->setText(tr("5:"));
            ui->label_6_q3->setText(tr("6:"));
            ui->label_7_q4->hide();
            ui->label_7_q4_data->hide();
        }
        else if(ui->btn_2_setaxis->text() == tr("线性") ||
                ui->btn_2_setaxis->text() == tr("重定位")){
            label->setText(linear[i-3]);

            ui->label_1_x->setText(tr("X:"));
            ui->label_2_y->setText(tr("Y:"));
            ui->label_3_z->setText(tr("Z:"));
            ui->label_4_q1->setText(tr("q1:"));
            ui->label_5_q2->setText(tr("q2:"));
            ui->label_6_q3->setText(tr("q3:"));
            ui->label_7_q4->show();
            ui->label_7_q4_data->show();
            ui->label_7_q4->setText(tr("q4:"));
        }
    }
}

roposition::~roposition()
{
    delete ui;
    delete image;
}

void roposition::changeAxis(int num)
{
    switch(num){
        case 0:
            do_JointOp_SpeedMode(num);
            break;

        case 1:
             do_JointOp_SpeedMode(num);
            break;

        case 2:
            do_CoordinateOp_SpeedMode();
        break;
    }
}

void roposition::changeAxisSpeed(int num)
{
    switch(num){
        case 0:
            pInputData->rate = 0.1;
            break;
        case 1:
            pInputData->rate=0.2;
            break;
        case 2:
            pInputData->rate=0.5;
            break;
        case 3:
            pInputData->rate=1;
            break;
    }
}

void roposition::changeCoord(int num)
{
    pInputData->flagCoordinate=num;
}

void roposition::changeModel(int num)
{
    switch(num){
        case 0:
        case 1:
            pInputData->mode = ITP_Mode_JointOp_SpeedAndIncMode;
            break;

        case 2:
            pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;
            break;
    }
}

void roposition::do_JointOp_SpeedMode(int num)
{
    pInputData->mode = ITP_Mode_JointOp_SpeedAndIncMode;
    selectaxis = num;
    ui->btn_1_coord->setEnabled(false);
    currentmodel = pInputData->mode;
}

void roposition::do_CoordinateOp_SpeedMode()
{
    pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;
    ui->btn_1_coord->setEnabled(true);
    currentmodel = pInputData->mode;
}
