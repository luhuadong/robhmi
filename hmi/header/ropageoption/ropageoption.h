#ifndef ROPAGEOPTION_H
#define ROPAGEOPTION_H

#include <QWidget>

#include "header/ropageoption/ropagehome/ropagehome.h"

#include "header/ropageoption/ropagealarm/ropagealarm.h"
#include "header/ropageoption/roposition/roposition.h"
#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"

#include "header/UI/InputOutput/InputOutput.h"
#include "header/UI/BackupRecover/BackupRecover.h"
#include "header/UI/ResourceManage/ResourceManage.h"
#include "header/UI/SystemInfo/SystemInfo.h"
#include "header/UI/ControlPanel/ControlPanel.h"
//#include "header/UI/Program/Program.h"
#include "header/ropageoption/roprogram/RoProgram.h"
#include "header/ropageoption/HMI_ParaSet/HMI_ParaSet.h"
#include "header/ropageoption/robmanual/robmanual.h"

#include "header/romenu/romenu.h"

#include "header/Common/Common.h"



class QStackedWidget;

namespace Ui {
class RoPageOption;
}

class RoPageOption : public QWidget
{
    Q_OBJECT

public:
    explicit RoPageOption(romenu *Menu, QWidget *parent = 0);
    ~RoPageOption();

    QStackedWidget *stack;

public slots:

private slots:
    void changeView(int num);

private:
    Ui::RoPageOption *ui;
    romenu *Menu;

    RoPageHome *home ;
    ControlPanel *CP;
    RoPageAlarm *alarm ;
    roposition *pos;
    ropageprogramdata *prodata;
    InputOutput *IOput;
    BackupRecover *BR;
    ResourceManage *RManage;
    SystemInfo *SysInfo;
//    Program *rProgram;
    RoProgram *Program;

    HMI_ParaSet *ParaSet;
    RobManual *manual;

    void ConnectInit();

    void Init();
    void ViewsInit();
};

#endif // ROPAGEOPTION_H
