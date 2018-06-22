#include "header/ropageoption/ropagealarm/alarmthread/alarmthread.h"
#include <QDebug>
AlarmThread::AlarmThread():QThread()
{
    ReadAlarmFile(ALARM_FILE_NAME);

    //新建一个QTimer对象
    timer = new QTimer();
//    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1);
//    //启动定时器
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

AlarmThread::~AlarmThread()
{
    QThread::terminate();
}

void AlarmThread::run()
{
//    while(1){
//        msleep(10);
//        if(strlen(RobAlarmBuffer.InfoQueue) != 0){
//            emit sendAlarm();
//        }
//    }
}

void AlarmThread::onTimerOut()
{
    if(strlen(RobAlarmBuffer.InfoQueue) != 0){
        emit sendAlarm();
        qDebug()<<"sendAlarm";
    }
}

