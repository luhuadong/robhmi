#include "header/ropageoption/ropagealam/alarmthread/alarmthread.h"
#include <QDebug>
AlarmThread::AlarmThread():QThread()
{
    ReadAlarmFile(ALARM_FILE_NAME);
//    qDebug() << RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[2] ;
}

AlarmThread::~AlarmThread()
{
    QThread::terminate();
}

void AlarmThread::run()
{
    while(1){
        msleep(100);
//        qDebug() << RobAlarmBuffer.RobAlarmNum ;
        if(strlen(RobAlarmBuffer.InfoQueue) != 0)
            emit sendAlarm();
    }
}
