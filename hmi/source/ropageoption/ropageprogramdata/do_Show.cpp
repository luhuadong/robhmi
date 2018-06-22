#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

void ropageprogramdata::ChooseDataTypeShow()
{
    QString DataType[2][3]= {
        {"RobTarget","JointTarget","WobjData"},	//位姿坐标  关节坐标 用户坐标系
        {"ToolData","ZoneData","SpeedData"},	//工具数据 指定平滑开始距离和角度 速度数据
    };

    for(int i = 0;i<2;i++){
        ChooseDataType->TableWidgetInsertRow(ChooseDataType->TableWidgetRowCount);
        ChooseDataType->TableWidgetSetItem(ChooseDataType->TableWidgetRowCount-1,0,
                                           new QTableWidgetItem(DataType[i][0]));
        ChooseDataType->TableWidgetSetItem(ChooseDataType->TableWidgetRowCount-1,1,
                                           new QTableWidgetItem(DataType[i][1]));
        ChooseDataType->TableWidgetSetItem(ChooseDataType->TableWidgetRowCount-1,2,
                                           new QTableWidgetItem(DataType[i][2]));
    }
}

void ropageprogramdata::ChooseAndExitDataTypeShow()
{
    ChooseAndExitDataType->TableWidgetClear();
    switch (CurrentDataType) {
        case DataManage_RobTargetType:
            for(int i = 0;i<robDataName.PNum;i++){
                ChooseAndExitDataType->TableWidgetInsertRow(ChooseAndExitDataType->TableWidgetRowCount);
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,0,
                                                          new QTableWidgetItem(robDataName.PName[i]));
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,1,
                                                          new QTableWidgetItem(mergeRobTarget(robDataBuffer.P[i])));
            }break;

        case DataManage_JointTargetType:
            for(int i = 0;i<robDataName.JNum;i++){
                ChooseAndExitDataType->TableWidgetInsertRow(ChooseAndExitDataType->TableWidgetRowCount);
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,0,
                                                          new QTableWidgetItem(robDataName.JName[i]));
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,1,
                                                          new QTableWidgetItem(mergeJointTarget(robDataBuffer.J[i])));
            }break;

        case DataManage_WobjDataType:
            for(int i = 0;i<robDataName.WNum;i++){
                ChooseAndExitDataType->TableWidgetInsertRow(ChooseAndExitDataType->TableWidgetRowCount);
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,0,
                                                          new QTableWidgetItem(robDataName.WName[i]));
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,1,
                                                          new QTableWidgetItem(mergeWobjData(robDataBuffer.W[i])));
            }break;

        case DataManage_ToolDataType:
            for(int i = 0;i<robDataName.TNum;i++){
                ChooseAndExitDataType->TableWidgetInsertRow(ChooseAndExitDataType->TableWidgetRowCount);
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,0,
                                                          new QTableWidgetItem(robDataName.TName[i]));
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,1,
                                                          new QTableWidgetItem(mergeToolData(robDataBuffer.T[i])));
            }break;

        case DataManage_ZoneDataType:
            for(int i = 0;i<robDataName.ZNum;i++){
                ChooseAndExitDataType->TableWidgetInsertRow(ChooseAndExitDataType->TableWidgetRowCount);
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,0,
                                                          new QTableWidgetItem(robDataName.ZName[i]));
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,1,
                                                          new QTableWidgetItem(mergeZoneData(robDataBuffer.Z[i])));
            }break;

        case DataManage_SpeedDataType:
            for(int i = 0;i<robDataName.VNum;i++){                
                ChooseAndExitDataType->TableWidgetInsertRow(ChooseAndExitDataType->TableWidgetRowCount);
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,0,
                                                          new QTableWidgetItem(robDataName.VName[i]));
                ChooseAndExitDataType->TableWidgetSetItem(ChooseAndExitDataType->TableWidgetRowCount-1,1,
                                                          new QTableWidgetItem(mergeSpeed(robDataBuffer.V[i])));
            }break;

        default:break;
    }
}

void ropageprogramdata::ShowAlter_P(ITP_RobTarget *P, QString DataName)
{
    P_AlterTmp = *P;

    QString roPName[] = {
        DataName,
        "trans:","x :=","y :=","z :=",
        "rot:","q1 :=","q2 :=","q3 :=","q4 :=",
        "robconf:","cf1 :=","cf4 :=","cf6 :=","cfx :=",
        "extax:","eax_a :=","eax_b :=","eax_c :=","eax_d :=","eax_e :=","eax_f :="
    };

    QString roPunit[]={
        "RobTarget",
        "Pos","Num","Num","Num",
        "Orient","Num","Num","Num","Num",
        "ConfData","Num","Num","Num","Num",
        "ExtJoint","Num","Num","Num","Num","Num","Num"
    };

    QString roPData[] = {
        mergeRobTarget(*P),
        mergeRobTarget_Pose(P->pose.trans),DoubleToString(P->pose.trans.x),
        DoubleToString(P->pose.trans.y),DoubleToString(P->pose.trans.z),
        mergeRobTarget_Orient(P->pose.rot),DoubleToString(P->pose.rot.s),
        DoubleToString(P->pose.rot.x),DoubleToString(P->pose.rot.y),DoubleToString(P->pose.rot.z),
        mergeRobTarget_ConfData(P->robconf),DoubleToString(P->robconf.cf1),
        DoubleToString(P->robconf.cf4),DoubleToString(P->robconf.cf6),DoubleToString(P->robconf.cfx),
        mergeRobTarget_ExtJoint(P->extax),DoubleToString(P->extax.eax[0]),DoubleToString(P->extax.eax[1]),
        DoubleToString(P->extax.eax[2]),DoubleToString(P->extax.eax[3]),DoubleToString(P->extax.eax[4]),
        DoubleToString(P->extax.eax[5])
    };

    AlterDataType->TableWidgetSetRowCount(roP_TableWidget_RowCount);
    for(int i = 0; i <AlterDataType->TableWidgetRowCount;i++){
        AlterDataType->TableWidgetSetItem(i,0,
                                          new QTableWidgetItem(roPName[i]));
        AlterDataType->TableWidgetSetItem(i,1,
                                          new QTableWidgetItem(roPData[i]));
        AlterDataType->TableWidgetSetItem(i,2,
                                          new QTableWidgetItem(roPunit[i]));
    }
}

void ropageprogramdata::ShowAlter_J(ITP_JointTarget *J,QString DataName)
{    J_AlterTmp = *J;

    QString roJName[] = {
        DataName,"robax:","rax_1 :=","rax_2 :=","rax_3 :=","rax_4 :=","rax_5 :=","rax_6 :=",
        "extax:","eax_a :=","eax_b :=","eax_c :=","eax_d :=","eax_e :=","eax_f :="
    };

    QString roJunit[]={
        "JointTarget",
        "RobJoint","Num","Num","Num","Num","Num","Num",
        "ExtJoint","Num","Num","Num","Num","Num","Num"
    };

    QString roJData[] = {
        mergeJointTarget(*J),
        mergeJointTarget_RobJoint(J->robax),DoubleToString(J->robax.rax[0]),
        DoubleToString(J->robax.rax[1]),DoubleToString(J->robax.rax[2]),DoubleToString(J->robax.rax[3]),
        DoubleToString(J->robax.rax[4]),DoubleToString(J->robax.rax[5]),
        mergeJointTarget_ExtJoint(J->extax),DoubleToString(J->extax.eax[0]),
        DoubleToString(J->extax.eax[1]),DoubleToString(J->extax.eax[2]),DoubleToString(J->extax.eax[3]),
        DoubleToString(J->extax.eax[4]),DoubleToString(J->extax.eax[5])
    };

     AlterDataType->TableWidgetSetRowCount(roJ_TableWidget_RowCount);
     for(int i = 0; i <AlterDataType->TableWidgetRowCount;i++){
        AlterDataType->TableWidgetSetItem(i,0,
                                          new QTableWidgetItem(roJName[i]));
        AlterDataType->TableWidgetSetItem(i,1,
                                          new QTableWidgetItem(roJData[i]));
        AlterDataType->TableWidgetSetItem(i,2,
                                          new QTableWidgetItem(roJunit[i]));
    }
}

void ropageprogramdata::ShowAlter_W(ITP_WobjData *W,QString DataName)
{
    W_AlterTmp = *W;

    QString roWName[] = {
        DataName,"robhold :=","ufprog :=","ufmec :=","uframe :=",
        "trans:","x :=","y :=","z :=",
        "rot:","q1 :=","q2 :=","q3 :=","q4 :=",
    };

    QString roWunit[]={
        "wobjdata","bool","bool","string",
        "Pose","Pos","Num","Num","Num",
        "Orient","Num","Num","Num","Num"
    };

    QString robhold;
    QString ufprog;
    QString ufmec = QString(W->ufmec);

    if(W->robhold=='1')
        robhold="TRUE";
    else
        robhold="FALSE";

    if(W->ufprog=='1')
        ufprog="TRUE";
    else
        ufprog="FALSE";

    QString roWData[] = {
        mergeWobjData(*W),robhold,ufprog,ufmec,
        mergeWobjData_Uframe(W->uframe),mergeWobjData_Pose(W->uframe.trans),
        DoubleToString(W->uframe.trans.x),DoubleToString(W->uframe.trans.y),DoubleToString(W->uframe.trans.z),
        mergeWobjData_Orient(W->uframe.rot),DoubleToString(W->uframe.rot.s),DoubleToString(W->uframe.rot.x),
        DoubleToString(W->uframe.rot.y),DoubleToString(W->uframe.rot.z)
    };

    AlterDataType->TableWidgetSetRowCount(roW_TableWidget_RowCount);
    for(int i = 0; i <AlterDataType->TableWidgetRowCount;i++){
        AlterDataType->TableWidgetSetItem(i,0,
                                          new QTableWidgetItem(roWName[i]));
        AlterDataType->TableWidgetSetItem(i,1,
                                          new QTableWidgetItem(roWData[i]));
        AlterDataType->TableWidgetSetItem(i,2,
                                          new QTableWidgetItem(roWunit[i]));
    }
}

void ropageprogramdata::ShowAlter_T(ITP_ToolData *T, QString DataName)
{
    T_AlterTmp = *T;

    QString roTName[] = {
        DataName,"robhold :=","tframe:","trans:","x :=","y :=","z :=",
        "rot:","q1 :=","q2 :=","q3 :=","q4 :=",
    };

    QString roTunit[]={
        "ToolData","bool",
        "Pose","Pos","Num","Num","Num",
        "Orient","Num","Num","Num","Num"
    };

    QString robhold;
    if(T->robhold == '1')
        robhold = "TRUE";
    else
        robhold = "FALSE";

    QString roTData[]={
        mergeToolData(*T),robhold,mergeTobjData_Pose(T->tframe),mergeToolData_Pos(T->tframe.trans),
        DoubleToString(T->tframe.trans.x),DoubleToString(T->tframe.trans.y),DoubleToString(T->tframe.trans.z),
        mergeToolData_Orient(T->tframe.rot),DoubleToString(T->tframe.rot.s),DoubleToString(T->tframe.rot.x),
        DoubleToString(T->tframe.rot.y),DoubleToString(T->tframe.rot.z)
    };

    AlterDataType->TableWidgetSetRowCount(roT_TableWidget_RowCount);
    for(int i = 0; i <AlterDataType->TableWidgetRowCount;i++){
        AlterDataType->TableWidgetSetItem(i,0,
                                          new QTableWidgetItem(roTName[i]));
        AlterDataType->TableWidgetSetItem(i,1,
                                          new QTableWidgetItem(roTData[i]));
        AlterDataType->TableWidgetSetItem(i,2,
                                          new QTableWidgetItem(roTunit[i]));
    }
}

void ropageprogramdata::ShowAlter_Z(ITP_ZoneData *Z,QString DataName)
{
    Z_AlterTmp = *Z;

    QString roZName[] = {
        DataName,"finep :=","pzone_tcp :=","pzone_ori :=",
        "pzone_eax :=","zone_ori :=","zone_leax :=","zone_reax :="
    };

    QString roZunit[]={
        "ZoneData","bool","Num","Num","Num","Num","Num","Num"
    };
    QString finep;

    if(Z->finep==1){
        finep="TRUE";
    }else
        finep="FALSE";

    QString roZData[]={
        mergeZoneData(*Z),finep,DoubleToString(Z->bgnzone.pzone_tcp),DoubleToString(Z->bgnzone.pzone_ori),
        DoubleToString(Z->bgnzone.pzone_eax),DoubleToString(Z->bgnzone.zone_ori),
        DoubleToString(Z->bgnzone.zone_leax),DoubleToString(Z->bgnzone.zone_reax)
    };

    AlterDataType->TableWidgetSetRowCount(roZ_TableWidget_RowCount);
    for(int i = 0; i <AlterDataType->TableWidgetRowCount;i++){
        AlterDataType->TableWidgetSetItem(i,0,
                                          new QTableWidgetItem(roZName[i]));
        AlterDataType->TableWidgetSetItem(i,1,
                                          new QTableWidgetItem(roZData[i]));
        AlterDataType->TableWidgetSetItem(i,2,
                                          new QTableWidgetItem(roZunit[i]));
    }
}

void ropageprogramdata::ShowAlter_V(ITP_SpeedData *V,QString DataName)
{    
    V_AlterTmp = *V;

    QString roVName[] = {
        DataName,"time :=","v_tcp :=","v_ort :=","v_leax :=","v_reax :="
    };

    QString roVunit[]={
        "SpeedData","Num","Num","Num","Num","Num"
    };

    QString roVData[] = {
        mergeSpeed(*V),DoubleToString(V->time),DoubleToString(V->v_tcp),
        DoubleToString(V->v_ort),DoubleToString(V->v_leax),DoubleToString(V->v_reax)
    };

    AlterDataType->TableWidgetSetRowCount(roV_TableWidget_RowCount);
    for(int i = 0; i <AlterDataType->TableWidgetRowCount;i++){
        AlterDataType->TableWidgetSetItem(i,0,
                                          new QTableWidgetItem(roVName[i]));
        AlterDataType->TableWidgetSetItem(i,1,
                                          new QTableWidgetItem(roVData[i]));
        AlterDataType->TableWidgetSetItem(i,2,
                                          new QTableWidgetItem(roVunit[i]));
    }
}
