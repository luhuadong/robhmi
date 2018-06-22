#include "header/ropageoption/ropagealarm/ropagealarm.h"
#include "ui_ropagealarm.h"

RoPageAlarm::RoPageAlarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoPageAlarm)
{
    ui->setupUi(this);
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);
    ui->stackedWidget->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT/*-ui->widget_btn->height()*/);

//    robAlarmThread = new AlarmThread();
//    robAlarmThread->start();

    QTimer* timer = new QTimer();
//    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1);
//    //启动定时器
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(do_TimerOut()));

    Init();
}

RoPageAlarm::~RoPageAlarm()
{
    delete ui;
}

void RoPageAlarm::TableWidgetToFile(QTableWidget *TableWidget, QString filename)
{
    QString str;
    str.append(robRM->dirPath).append('/').append(filename);
    QFile file(str);
    file.open( QIODevice::WriteOnly);

    for(int i = 0;i<TableWidget->rowCount();i++){
        for(int j=0;j<TableWidget->columnCount();j++){
            file.write("\t",qstrlen("\t"));
            file.write(TableWidget->item(i,j)->text().toLocal8Bit().data(),
                       qstrlen(TableWidget->item(i,j)->text().toLocal8Bit().data()));
        }
//        file.write("\n",qstrlen("\n"));
    }

    file.close();
}
