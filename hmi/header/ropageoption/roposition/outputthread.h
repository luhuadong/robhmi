#ifndef OUTPUTTHREAD_H
#define OUTPUTTHREAD_H

#include <QThread>
#include "header/ITP_Interface.h"
#include <QDebug>

#include "header/DataManage_WinShareMem.h"


class outputThread : public QThread
{
    Q_OBJECT
public:
    explicit outputThread();
    ~outputThread();

    ITP_OutputData *pOutputData;	//share mem

signals:
    void notify(ITP_OutputData *pOutputData);

protected:
    void run();

private:


//    void *shared_Outputmemory;

};

#endif // OUTPUTTHREAD_H
