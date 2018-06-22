#include "header/ropageoption/roposition/outputthread.h"
#include "header/ropageoption/ropagealarm/robalarm.h"

outputThread::outputThread() : QThread()
{
#if Linux
    int shmidOutput;

    void *shared_Outputmemory=(void*)0;

//output mem
    shmidOutput=shmget((key_t)ITP_Key_OutputShareMem,sizeof(ITP_OutputData),0666|IPC_CREAT);
    if(shmidOutput==-1)
    {
            exit(EXIT_SUCCESS);
    }

    shared_Outputmemory=shmat(shmidOutput,(void*)0,0);
    if(shared_Outputmemory==(void *)-1)
    {
            exit(EXIT_SUCCESS);
    }

    pOutputData=(ITP_OutputData*)shared_Outputmemory;//get input sharemem pointer
#elif Windows
    DataManage_InitShareMem_OutputData(0,(void **)&pOutputData);
#endif

    if(!pOutputData){
        RobAlarm(0,6);
    }

    RobAlarm(1,1000);
    RobAlarm(2,2001);
    RobAlarm(2,2002);
    RobAlarm(2,2003);
}

outputThread::~outputThread()
{
    QThread::terminate();
}

void outputThread::run()
{
    while(1){
        msleep(100);
        emit notify(pOutputData);
    }
}
