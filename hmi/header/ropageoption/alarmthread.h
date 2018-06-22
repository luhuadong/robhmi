#ifndef ALARMTHREAD_H
#define ALARMTHREAD_H

#include <QThread>
#include "header/ropageoption/ropagealam/robalarm.h"

class AlarmThread : public QThread
{    
    Q_OBJECT
public:
    explicit AlarmThread();
    ~AlarmThread();

signals:
    void sendAlarm();

protected:
    void run();

};

#endif // ALARMTHREAD_H
