#include "header/ropageoption/roprogram/RoProgram.h"
#include "ui_RoProgram.h"

void RoProgram::do_MissionAndProClicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ProChoose));
    ProChoose->setMissionAndPro();
}

void RoProgram::do_ProChooseTableWidgetCellClicked(int, int, QString , QString ProgramName)
{
    QString path = "D:/MyStudyForQT/Practice/newhmi/hmi_windows/robhmi/hmi/bin/example/";
    HMI_ReadFile(&ProgramFileInfo,path.toLocal8Bit().data()
                 ,ProgramName.toLocal8Bit().data());
    /*显示程序的步骤
    1、清除表格
    2、插入内容
    3、回到第一行
    4、显示行号
    */
    ProShow->ShowProClear();
    for(int i = ProgramFileInfo.FileLineNum;i>=1;i--){
        ProShow->ShowProgram((ProgramFileInfo.FileContent[i]));
    }
    ProShow->ShowLineNum(ProgramFileInfo.FileLineNum);
    ui->stackedWidget->setCurrentIndex(vProShow);
}

void RoProgram::do_btnBackClicked()
{
    ui->stackedWidget->setCurrentIndex(vProShow);
}

void RoProgram::do_btnRoutineProClicked()
{
    ui->stackedWidget->setCurrentIndex(vProRoupro);
}

void RoProgram::do_btnModuleClicked()
{
    ui->stackedWidget->setCurrentIndex(vProModule);
}

void RoProgram::do_MenuTriggered(QAction *action)
{
    //新建
    //加载
    this->raise();

    for(int i = 0;i<ProChoose->menu->actions().count();i++){
        if(action==ProChoose->menu->actions().at(i)&&i<3){
            ui->stackedWidget->setCurrentIndex(vRobRM);
            robRM->Root();
            robRM->clearLineEditText();
        }
    }
}

void RoProgram::do_robRMbtnCancelClicked()
{
    ui->stackedWidget->setCurrentIndex(vProShow);
}

void RoProgram::do_robRMbtnOkClicked()
{
    if(decodeTaskInit()==-1)
        return;

    ProShow->ShowProClear();
    ProShow->LineNumClear();

    QString str = robRM->dirPath.append('/').append(robRM->getLineEditText());

    ui->stackedWidget->setCurrentIndex(vProShow);

    int channel = 0;
    readRobotPrgFile(channel,str.toLocal8Bit().data());

    char s[256];
    memset(s,0,sizeof(s));

    routine_prg_property routinePro;
    getSelRoutineProperty(channel,0,0,&routinePro);

    for(int lineNum = 0; lineNum<getSelModuleFileLineTotalCnt(channel,routinePro.parentModule);lineNum++){
        getSelectModuleLineStr(channel,routinePro.parentModule,lineNum,s);
        ProShow->ShowProgram(s);
    }
    ProShow->ShowLineNum(getSelModuleFileLineTotalCnt(channel,routinePro.parentModule));
}

void RoProgram::do_robRMbtnNewClicked()
{

}

void RoProgram::do_robRMbtnOpenKeyClicked()
{
    ui->stackedWidget->setCurrentIndex(vKey);
}

void RoProgram::do_KeyOkClicked(QString)
{
    ui->stackedWidget->setCurrentIndex(vRobRM);
}

void RoProgram::do_KeyCancelClcked()
{
    ui->stackedWidget->setCurrentIndex(vProShow);
}
