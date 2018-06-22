#include "header/ropageoption/ropagealarm/ropagealarm.h"
#include "ui_ropagealarm.h"

void RoPageAlarm::do_btnSaveClicked()
{    
    ui->stackedWidget->setCurrentIndex(aRMView);

    QDateTime tm = QDateTime::currentDateTime();//获取系统现在的时间
    QString TimeStr = tm.toString("yyMMdd"); //设置显示格式.
    robRM->setLineEditText(TimeStr+".txt");
}

void RoPageAlarm::do_btnDelClicked()
{

}

void RoPageAlarm::do_btnRefreshClicked()
{

}

void RoPageAlarm::do_btnOkClicked()
{
    ui->stackedWidget->setCurrentIndex(aShowView);
}

void RoPageAlarm::do_btnViewClicked()
{

}

void RoPageAlarm::do_Alarm()
{
    qDebug()<<"do_Alarm";
    memset(RobAlarmBuffer.InfoQueue,0,sizeof(RobAlarmBuffer.InfoQueue));
    for(int i = 0;i<5;i++)
        ExpAlarmData[i].clear();
    emit isAlarm(3); //  发送报警产生信号 3是报警界面序号
    QDateTime tm = QDateTime::currentDateTime();//获取系统现在的时间
    QString TimeStr = tm.toString("hh:mm:ss"); //设置显示格式.

    QString AlarmContent ;
    AlarmContent = AlarmContent.fromLocal8Bit(RobAlarmBuffer.RobAlarmContent[1]);
    QString AlarmExp;
    AlarmExp = AlarmExp.fromLocal8Bit(RobAlarmBuffer.RobAlarmContent[2]);
    QString AlarmDeal;
    AlarmDeal = AlarmDeal.fromLocal8Bit(RobAlarmBuffer.RobAlarmContent[3]);
///报警内容、说明、处理方法
//    QString usAl[3];
    ExpAlarmData[0] = QString::number(RobAlarmBuffer.RobAlarmNum);
    ExpAlarmData[1] = AlarmContent;
    ExpAlarmData[2] = TimeStr;
    ExpAlarmData[3] = AlarmExp;
    ExpAlarmData[4] = AlarmDeal;

//    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
qDebug() << ui->tableWidget->rowCount();
qDebug()<<ExpAlarmData[1];
    ui->tableWidget->insertRow(0);//插入一行
    for(int j = 0;j<ui->tableWidget->columnCount();j++)
    {
        ui->tableWidget->setItem(0,j,
                                 new QTableWidgetItem(ExpAlarmData[j]));
    }
}

void RoPageAlarm::do_cellClicked(int row,int column)
{
    column = ui->tableWidget->columnCount()-ui->tableWidget->columnCount();
    QTableWidgetItem *itemNum = ui->tableWidget->item(row,column);  //获取报警号
    QTableWidgetItem *itemTime = ui->tableWidget->item
            (row,ui->tableWidget->columnCount()-1);  //获取报警时间

    if(itemNum==NULL||itemTime==NULL)
        return;

    ui->stackedWidget->setCurrentIndex(aExpView);

    ui->label_AlarmNum->setText("报警号 "+ExpAlarmData[0]);
    ui->label_AlarmTime->setText("报警时间 "+ExpAlarmData[2]);
    ui->label_AlarmContent->setText(ExpAlarmData[1]);
    ui->label_AlarmExp->setText(ExpAlarmData[3]);
    ui->label_AlarmDeal->setText(ExpAlarmData[4]);
}

void RoPageAlarm::do_robRMbtnNewClicked()
{
    currentAction=Action_New;
    ui->stackedWidget->setCurrentIndex(aKeyView);
}

void RoPageAlarm::do_robRMbtnOpenKeyClicked()
{
    currentAction=Action_Rename;
    vkey->vkeyWorldInput(robRM->getLineEditText());
    ui->stackedWidget->setCurrentIndex(aKeyView);
}

void RoPageAlarm::do_robRMbtnOkClicked()
{
    ui->stackedWidget->setCurrentIndex(aShowView);

    TableWidgetToFile(ui->tableWidget,robRM->getLineEditText());
}

void RoPageAlarm::do_robRMbtnCancelClicked()
{
    ui->stackedWidget->setCurrentIndex(aShowView);
}

void RoPageAlarm::do_keyOk(QString str)
{
    switch (currentAction) {
        case Action_Rename:
            robRM->setLineEditText(str);
            break;
        case Action_New:robRM->NewDirectory(str);
            break;
        default:break;
    }

    robRM->dir.setPath(robRM->dirPath);//刷新
    robRM->ShowFile(robRM->dir);//刷新
    ui->stackedWidget->setCurrentIndex(aRMView);
}

void RoPageAlarm::do_keyCancel()
{
    ui->stackedWidget->setCurrentIndex(aRMView);
}

void RoPageAlarm::do_TimerOut()
{
//    qDebug() << strlen(RobAlarmBuffer.InfoQueue);//d
    if(strlen(RobAlarmBuffer.InfoQueue) != 0){
        emit sendAlarm();
        qDebug()<<"sendAlarm";
    }
}
