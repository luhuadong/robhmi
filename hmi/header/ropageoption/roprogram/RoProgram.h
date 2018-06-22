#ifndef ROPROGRAM_H
#define ROPROGRAM_H

#include <QWidget>
#include <QDebug>
#include <QAction>
#include "header/FileAndDirOperate/FileAndDirOperate.h"
#include "header/UI/Program/ProgramChoose/ProgramChoose.h"
//#include "ProgramChoose.h"
#include "header/UI/Program/ProgramShow/ProgramShow.h"
#include "header/UI/Program/ProgramModule/ProgramModule.h"
#include "header/UI/Program/ProgramRoutinePro/ProgramRoutinePro.h"

#include "header/UI/robResouceManage/robResouceManage.h"
#include "header/UI/keyworld/vkeyworld/vkeyworld.h"

//#include "header/decode_prg/robotdecodepublic.h"
#include "robotdecodepublic.h"
#include "robotprgfilestruct.h"
#include "decode_datatype.h"
#include "decode_instructions.h"
#include "decode_lexical_analysis.h"
#include "decode_typestructs.h"

namespace Ui {
class RoProgram;
}

class RoProgram : public QWidget
{
    Q_OBJECT

public:
    explicit RoProgram(QWidget *parent = 0);
    ~RoProgram();

private slots:
    void do_ProChooseTableWidgetCellClicked(int , int , QString, QString ProgramName);
    void do_MissionAndProClicked();

    void do_btnModuleClicked();
    void do_btnRoutineProClicked();
    void do_btnBackClicked();

    void do_MenuTriggered(QAction* action);
    void do_robRMbtnCancelClicked();
    void do_robRMbtnOkClicked();
    void do_robRMbtnNewClicked();
    void do_robRMbtnOpenKeyClicked();
    void do_KeyOkClicked(QString);
    void do_KeyCancelClcked();

private:
    Ui::RoProgram *ui;
    ProgramChoose *ProChoose;//选择
    ProgramShow *ProShow;//显示
    ProgramModule *ProModule;//模块
    ProgramRoutinePro *ProRoupro;//例行程序

    robResouceManage *robRM;
    vkeyworld *Key;

    void Init();
    void ViewInit();
    void ConnectInit();

    void ShowFileName();
//    void ShowFileContent(QString ProgramName);
//    DirSuffixFIFO SuffixFIFO;//目录下某后缀信息

    enum ChangeView{
        vProChoose,vProShow,vProModule,vProRoupro,
        vRobRM,//资源管理器
        vKey,//输入法
    }vChangeView;

    enum currentAction{

    }acurrentAction;
};

#endif // ROPROGRAM_H
