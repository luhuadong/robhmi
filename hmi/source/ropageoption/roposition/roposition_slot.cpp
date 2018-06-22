
#include "header/ropageoption/roposition/roposition.h"
#include "ui_roposition.h"

void roposition::setbtn()
{
    for(int i = 0; i < thisallbtn.count();i++)
    {
        if(thisallbtn.at(i)->hasFocus())
        {
            if(i!=3&&i!=4){
                btnflat = thisallbtn.at(i);     // 记住键值
                posset = new roposset(thisallbtn.at(i),i,this);
                posset->setGeometry(0,0,680,500);
                posset->show();
                posset->setAutoFillBackground(true);
                connect(posset,SIGNAL(sendbtn(int)),this,SLOT(change(int)));
            }else if(i==3){//工具坐标

            }else if(i==4){//工件坐标

            }
        }
    }
}

void roposition::change(int btnnum)
{
    btnflat->setText(posset->StrEnsure);
    for(int i = 0;i<thisallbtn.count();i++){
        if(thisallbtn.at(i)==btnflat){
            switch(i){
            case 0://坐标系
                changeCoord(btnnum);
                break;
            case 1://设置轴
                changeAxis(btnnum);
                break;
            case 2://设置轴速度
                changeAxisSpeed(btnnum);
                break;
            case 3://打开工具坐标数据
                break;
            case 4://打开工件坐标数据
                break;

            case 5://操作杆锁定
                break;
            case 6://增量
                break;
            default:
                break;
            }
        }
    }

    changedire();
}

void roposition::showData(ITP_OutputData *OutputData)
{
    if(!OutputData){
        ITP_OutputData Data[512];
        OutputData = Data;        
    }
    if(currentmodel == 2){
//        ui->label_1_x_data->setText(QString::number(ITP_radian2angle(OutputData->.robax.rax[0])));
//        ui->label_2_y_data->setText(QString::number(ITP_radian2angle(OutputData->curJoint.robax.rax[1])));
//        ui->label_3_z_data->setText(QString::number(ITP_radian2angle(OutputData->curJoint.robax.rax[2])));
//        ui->label_4_q1_data->setText(QString::number(ITP_radian2angle(OutputData->curJoint.robax.rax[3])));
//        ui->label_5_q2_data->setText(QString::number(ITP_radian2angle(OutputData->curJoint.robax.rax[4])));
//        ui->label_6_q3_data->setText(QString::number(ITP_radian2angle(OutputData->curJoint.robax.rax[5])));

        ui->label_1_x_unit->setText("°");
        ui->label_2_y_unit->setText("°");
        ui->label_3_z_unit->setText("°");
        ui->label_4_q1_unit->setText("°");
        ui->label_5_q2_unit->setText("°");
        ui->label_6_q3_unit->setText("°");
    }
    else if(currentmodel == 12){
        ui->label_1_x_data->setText(QString::number(OutputData->curRob.pose.trans.x));
        ui->label_2_y_data->setText(QString::number(OutputData->curRob.pose.trans.y));
        ui->label_3_z_data->setText(QString::number(OutputData->curRob.pose.trans.z));
        ui->label_4_q1_data->setText(QString::number(OutputData->curRob.pose.rot.s));
        ui->label_5_q2_data->setText(QString::number(OutputData->curRob.pose.rot.z));
        ui->label_6_q3_data->setText(QString::number(OutputData->curRob.pose.rot.y));
        ui->label_7_q4_data->setText(QString::number(OutputData->curRob.pose.rot.z));

        ui->label_1_x_unit->setText("mm");
        ui->label_2_y_unit->setText("mm");
        ui->label_3_z_unit->setText("mm");
        ui->label_4_q1_unit->setText("");
        ui->label_5_q2_unit->setText("");
        ui->label_6_q3_unit->setText("");
        ui->label_7_q4_unit->setText("");
    }
    ui->label_moving->setText(QString::number(OutputData->moving));
    ui->label_alarm->setText(QString::number(OutputData->alarmNo));
    if(OutputData->alarmNo == 1){
//        qDebug()<<"DF";
        RobAlarm(1,1006);
    }
    ui->label_model->setText(QString::number(OutputData->modeReal));
}

void roposition::roMoving()
{
    for(int i = 0;i<dirbtnlist.count();i++){
        if(dirbtnlist.at(i)->hasFocus()){
            switch(i){
                case 0:
                    pInputData->robotMove[axis[selectaxis][1]]=
                            /*ui->lineEdit_speed->text().toFloat(&ok)**/pInputData->rate;
                    break;
                case 3:
                    pInputData->robotMove[axis[selectaxis][1]]=
                            -(/*ui->lineEdit_speed->text().toFloat(&ok)**/pInputData->rate);
                    break;

                case 1:
                    pInputData->robotMove[axis[selectaxis][0]]=
                            /*ui->lineEdit_speed->text().toFloat(&ok)**/pInputData->rate;
                    break;
                case 2:
                    pInputData->robotMove[axis[selectaxis][0]]=
                            -(/*ui->lineEdit_speed->text().toFloat(&ok)**/pInputData->rate);
                    break;

                case 4:
                    pInputData->robotMove[axis[selectaxis][2]]=
                            /*ui->lineEdit_speed->text().toFloat(&ok)**/pInputData->rate;
                    break;
                case 5:
                    pInputData->robotMove[axis[selectaxis][2]]=
                            -(/*ui->lineEdit_speed->text().toFloat(&ok)**/pInputData->rate);
                    break;
            }
        }
    }
}

void roposition::rostopMoving()
{
    for(int i = 0;i<dirbtnlist.count();i++){
        if(dirbtnlist.at(i)->hasFocus()){
            switch(i){
                case 0:
                    pInputData->robotMove[axis[selectaxis][1]]=0;
                    break;
                case 3:
                    pInputData->robotMove[axis[selectaxis][1]]=0;
                    break;

                case 1:
                    pInputData->robotMove[axis[selectaxis][0]]=0;
                    break;
                case 2:
                    pInputData->robotMove[axis[selectaxis][0]]=0;
                    break;

                case 4:
                    pInputData->robotMove[axis[selectaxis][2]]=0;
                    break;
                case 5:
                    pInputData->robotMove[axis[selectaxis][2]]=0;
                    break;
            }
        }
    }
}
