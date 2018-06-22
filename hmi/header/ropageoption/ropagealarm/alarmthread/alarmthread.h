#ifndef ALARMTHREAD_H
#define ALARMTHREAD_H

#include <QThread>
#include <QTimer>
#include <QTime>
#include <QMutex>

#include "header/ropageoption/ropagealarm/robalarm.h"

class AlarmThread : public QThread
{    
    Q_OBJECT
public:
    explicit AlarmThread();
    ~AlarmThread();

private slots:
    void onTimerOut()  ;


signals:
    void sendAlarm();

protected:
    void run();

private:


    QTimer *timer;


};

#endif // ALARMTHREAD_H
