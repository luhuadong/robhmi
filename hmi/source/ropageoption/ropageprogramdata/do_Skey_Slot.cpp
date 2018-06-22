#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

void ropageprogramdata::do_skeyBtnClicked(QString str)
{
    AlterDataType->TableWidgetAlterCurrentItem(str);
}

void ropageprogramdata::do_skeyCancelBtnClicked( )
{
    do_AlterDataType_btnEnabled(true);
    AlterDataType->TableWidgetSelectRow(AlterDataType->TableWidgetCurrentRow);
}

void ropageprogramdata::do_skeyOkBtnClicked( )
{
    do_AlterDataType_btnEnabled(true);
    AlterDataType->TableWidgetSelectRow(AlterDataType->TableWidgetCurrentRow);

    Synchro(AlterDataType->TableWidgetCurrentRow,
            AlterDataType->TableWidgetItemQString(AlterDataType->TableWidgetCurrentRow,1));
}

//表格内容更改时,同时对ItemIsEnabled不可用的表格也更改
void ropageprogramdata::Synchro(int TableWidgetCurrentRow,QString str)
{
    bool ok;
    double *RobTarget[] = {
        0,0,&(P_AlterTmp.pose.trans.x),&(P_AlterTmp.pose.trans.y),&(P_AlterTmp.pose.trans.z),
        0,&(P_AlterTmp.pose.rot.s),&(P_AlterTmp.pose.rot.x),&(P_AlterTmp.pose.rot.y),&(P_AlterTmp.pose.rot.z),
        0,&(P_AlterTmp.extax.eax[0]),&(P_AlterTmp.extax.eax[1]),&(P_AlterTmp.extax.eax[2]),
        &(P_AlterTmp.extax.eax[3]),&(P_AlterTmp.extax.eax[4]),&(P_AlterTmp.extax.eax[5])
    };

    int *RobTarget_robconf[] = {
        0,&(P_AlterTmp.robconf.cf1),&(P_AlterTmp.robconf.cf4),&(P_AlterTmp.robconf.cf6),&(P_AlterTmp.robconf.cfx),
    };

    double *Joint[] = {
        0,0,&J_AlterTmp.robax.rax[0],&J_AlterTmp.robax.rax[1],&J_AlterTmp.robax.rax[2],
        &J_AlterTmp.robax.rax[3],&J_AlterTmp.robax.rax[4],&J_AlterTmp.robax.rax[5],
        0,&J_AlterTmp.extax.eax[0],&J_AlterTmp.extax.eax[1],&J_AlterTmp.extax.eax[2],
        &J_AlterTmp.extax.eax[3],&J_AlterTmp.extax.eax[4],&J_AlterTmp.extax.eax[5],
    };

    double *WobjData[] = {
        0,0,0,0,0,0,
        &W_AlterTmp.uframe.trans.x,&(W_AlterTmp.uframe.trans.y),&(W_AlterTmp.uframe.trans.z),
        0,&(W_AlterTmp.uframe.rot.s),&(W_AlterTmp.uframe.rot.x),
        &(W_AlterTmp.uframe.rot.y),&(W_AlterTmp.uframe.rot.z)
    };

    double *ToolData[] = {
        0,0,0,0,
        &(T_AlterTmp.tframe.trans.x),&(T_AlterTmp.tframe.trans.y),&(T_AlterTmp.tframe.trans.z),
        0,&(T_AlterTmp.tframe.rot.s),&(T_AlterTmp.tframe.rot.x),
        &(T_AlterTmp.tframe.rot.y),&(T_AlterTmp.tframe.rot.z),
    };

    double *ZoneData[] = {
        0,0,&(Z_AlterTmp.bgnzone.pzone_tcp),&(Z_AlterTmp.bgnzone.pzone_ori),
        &(Z_AlterTmp.bgnzone.pzone_eax),&(Z_AlterTmp.bgnzone.zone_ori),
        &(Z_AlterTmp.bgnzone.zone_leax),&(Z_AlterTmp.bgnzone.zone_reax),
    };

    double *Speed[] = {
        0,&V_AlterTmp.time,&V_AlterTmp.v_tcp,
        &V_AlterTmp.v_ort,&V_AlterTmp.v_leax,&V_AlterTmp.v_reax
    };

    switch(CurrentDataType){
        case DataManage_RobTargetType:
        if(10<TableWidgetCurrentRow&&TableWidgetCurrentRow<15)
            *RobTarget_robconf[TableWidgetCurrentRow-10] = str.toInt(&ok);
        else if(TableWidgetCurrentRow>=15)//减5是因为robconf有四个值加一个robconf
            *RobTarget[TableWidgetCurrentRow-5] = str.toDouble(&ok);
        else
            *RobTarget[TableWidgetCurrentRow] = str.toDouble(&ok);

        ShowAlter_P(&P_AlterTmp,AlterDataName);
        break;

        case DataManage_JointTargetType:
        *Joint[TableWidgetCurrentRow] = str.toDouble(&ok);
        ShowAlter_J(&J_AlterTmp,AlterDataName);
        break;

        case DataManage_WobjDataType:
        *WobjData[TableWidgetCurrentRow] = str.toDouble(&ok);
        ShowAlter_W(&W_AlterTmp,AlterDataName);
        break;

        case DataManage_ToolDataType:
        *ToolData[TableWidgetCurrentRow] = str.toDouble(&ok);
        ShowAlter_T(&T_AlterTmp,AlterDataName);
        break;

        case DataManage_ZoneDataType:
        *ZoneData[TableWidgetCurrentRow] = str.toDouble(&ok);
        ShowAlter_Z(&Z_AlterTmp,AlterDataName);
        break;

        case DataManage_SpeedDataType:
        *Speed[TableWidgetCurrentRow] = str.toDouble(&ok);
        ShowAlter_V(&V_AlterTmp,AlterDataName);
        break;

        default:break;
    }
}
