#include "header/ropageoption/roposition/roposition.h"
#include "ui_roposition.h"


void roposition::init()
{
    read_ITP_Thread = new outputThread;
    read_ITP_Thread->start();    

    shareMemInit();

    datainit();

    connect(read_ITP_Thread,SIGNAL(notify(ITP_OutputData*)),
            this,SLOT(showData(ITP_OutputData *)));

    btninit();

    labelinit();

    QString axistext[] = {
        tr("轴1-3"),
        tr("轴4-6"),
        tr("线性"),
        tr("重定位"),
    };

    QString speedtext[] = {
        tr("10%"),
        tr("20%"),
        tr("50%"),
        tr("100%"),
    };

    for(int i = 0 ; i< 4 ;i++){
        if(axistext[i] == ui->btn_2_setaxis->text())
            changeAxis(i);
    }

    for(int i =0;i<4;i++){
        if(speedtext[i] == ui->btn_3_setaxisspeed->text())
            changeAxisSpeed(i);
    }
}

void roposition::btninit()
{
    thisallbtn = ui->groupBox_option->findChildren<QPushButton *>(QString(),Qt::FindDirectChildrenOnly);
    for(int i = 0;i<thisallbtn.count();i++){
        thisallbtn.at(i)->setFlat(true);//设置按钮为水平状态，默认是突出
        thisallbtn.at(i)->setStyleSheet("border:0px solid gray;\
                                        border-radius: 0px;");
        connect(thisallbtn.at(i),SIGNAL(clicked()),this,SLOT(setbtn()));
    }

    dirbtnlist = ui->dir_widget->findChildren<QPushButton *>();
    for(int i = 0 ;i < dirbtnlist.count(); i ++){
        dirbtnlist.at(i)->setAutoRepeat(true);
        connect(dirbtnlist.at(i),SIGNAL(pressed()),this,SLOT(roMoving()));
        connect(dirbtnlist.at(i),SIGNAL(released()),this,SLOT(rostopMoving()));
    }
}

void roposition::labelinit()
{
    labellist  = ui->groupBox_dir->findChildren<QLabel *>(QString(), Qt::FindChildrenRecursively);

    QString images[] = {
        "./resource/images/appbar.settings.png",
        "./resource/images/appbar.share.open.png",
        "./resource/images/appbar.share.png",
    };
    image = new QImage();

    for(int i= 0;i<3;i++)
    {
        QLabel *label = labellist.at(i);

        image->load(images[i]);
        label->setPixmap(QPixmap::fromImage(*image));
    }
}

void roposition::shareMemInit()
{
#if Linux
    int shmidInput;
//    void *shared_Inputmemory=(void*)0;

     shared_Inputmemory = (void*)0;
    //input mem
    shmidInput=shmget((key_t)ITP_Key_InputShareMem,sizeof(ITP_InputData),0666|IPC_CREAT);//create input share mem
    if(shmidInput==-1)
    {
            exit(EXIT_SUCCESS);
    }

    shared_Inputmemory=shmat(shmidInput,(void*)0,0);
    if(shared_Inputmemory==(void*)-1)
    {
            exit(EXIT_SUCCESS);
    }

    pInputData=(ITP_InputData*)shared_Inputmemory;//get input sharemem pointer

#elif Windows
    DataManage_InitShareMem_InputData(1,(void **)&pInputData);
#endif
}

void roposition::datainit()
{

    for(int i = 0;i<2;i++)
        for(int j = 0 ; j < 3 ; j++)
            axis[i][j] = j+i*3;

    QString str[] = {
        tr("轴1-3"),
        tr("轴4-6"),
        tr("线性"),
        tr("重定位"),
    };

    float AxisSpeed[] = {
        0.1,
        0.2,
        0.5,
        1.0,
    };

    QString AxisSpeed_str[] = {
        tr("10%"),
        tr("20%"),
        tr("50%"),
        tr("100%"),
    };

    for(int i = 0 ; i<4 ;i++){
        if(ui->btn_2_setaxis->text() == str[i]){
            currentaxis = i;
            switch(currentaxis){
                case 0:
                case 1:
                    pInputData->mode = ITP_Mode_JointOp_SpeedAndIncMode;
                    currentmodel = 2;
                    break;
                case 2:
                    pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;
                    currentmodel = 12;
                    break;
            }

        }
    }

    for(int i = 0 ; i<4 ;i++){
        if(ui->btn_3_setaxisspeed->text() == AxisSpeed_str[i])
            pInputData->rate = AxisSpeed[i];
    }
}



