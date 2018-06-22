#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

void ropageprogramdata::do_AlterDataType_OkBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(ChooseAndExitDataTypeView);

    switch (CurrentDataType) {
        case DataManage_RobTargetType:
        robDataBuffer.P[AlterDataNum] = P_AlterTmp;
        ChooseAndExitDataType->TableWidgetAlterItem(ChooseAndExitDataType->TableWidgetCurrentRow,1,
                                                    mergeRobTarget(robDataBuffer.P[AlterDataNum]));
        break;

        case DataManage_JointTargetType:
        robDataBuffer.J[AlterDataNum] = J_AlterTmp;
        ChooseAndExitDataType->TableWidgetAlterItem(ChooseAndExitDataType->TableWidgetCurrentRow,1,
                                                    mergeJointTarget(robDataBuffer.J[AlterDataNum]));
        break;

        case DataManage_WobjDataType:
        robDataBuffer.W[AlterDataNum] = W_AlterTmp;
        ChooseAndExitDataType->TableWidgetAlterItem(ChooseAndExitDataType->TableWidgetCurrentRow,1,
                                                    mergeWobjData(robDataBuffer.W[AlterDataNum]));
        break;

        case DataManage_ToolDataType:
        robDataBuffer.T[AlterDataNum] = T_AlterTmp;
        ChooseAndExitDataType->TableWidgetAlterItem(ChooseAndExitDataType->TableWidgetCurrentRow,1,
                                                    mergeToolData(robDataBuffer.T[AlterDataNum]));
        break;

        case DataManage_ZoneDataType:
        robDataBuffer.Z[AlterDataNum] = Z_AlterTmp;
        ChooseAndExitDataType->TableWidgetAlterItem(ChooseAndExitDataType->TableWidgetCurrentRow,1,
                                                    mergeZoneData(robDataBuffer.Z[AlterDataNum]));
        break;

        case DataManage_SpeedDataType:
        robDataBuffer.V[AlterDataNum] = V_AlterTmp;
        ChooseAndExitDataType->TableWidgetAlterItem(ChooseAndExitDataType->TableWidgetCurrentRow,1,
                                                    mergeSpeed(robDataBuffer.V[AlterDataNum]));

//        DataManage_WriteFile(&robDataBuffer);
//        DataManage_AlterFile(DataManage_SpeedDataType,AlterDataNum,&robDataBuffer.V[AlterDataNum]);
//        DataManage_WriteFile_Item(DataManage_SpeedDataType,AlterDataNum,
//                                  &robDataBuffer.V[AlterDataNum]);//新加数据
        break;
        default:break;
    }
}

void ropageprogramdata::do_AlterDataType_TRUEBtnClicked()
{

}

void ropageprogramdata::do_AlterDataType_FALSEBtnClicked()
{

}

void ropageprogramdata::do_AlterDataType_UndoBtnClicked()
{
    AlterDataType->TableWidgetClear();
    switch (CurrentDataType) {
        case DataManage_RobTargetType:
//            P_Alter = (ITP_RobTarget*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_P(P_Alter,AlterDataName);
        break;

        case DataManage_JointTargetType:
//            J_Alter = (ITP_JointTarget*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_J(J_Alter,AlterDataName);
        break;

        case DataManage_WobjDataType:
//            W_Alter = (ITP_WobjData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_W(W_Alter,AlterDataName);
        break;

        case DataManage_ToolDataType:
//            T_Alter = (ITP_ToolData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_T(T_Alter,AlterDataName);
        break;

        case DataManage_ZoneDataType:
//            Z_Alter = (ITP_ZoneData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_Z(Z_Alter,AlterDataName);
        break;

        case DataManage_SpeedDataType:
//            V_Alter = (ITP_SpeedData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
        qDebug()<<V_Alter->time;
        ShowAlter_V(V_Alter,AlterDataName);qDebug()<<"JE";
        break;
        default:break;
    }
}

void ropageprogramdata::do_AlterDataType_CancelBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(ChooseAndExitDataTypeView);
}

void ropageprogramdata::do_AlterDataType_TableWidgetCellPressed(int,int colnum,QString String)
{
    AlterDataType->setFALSEBtnHide(true);
    AlterDataType->setTRUEBtnHide(true);
    if(colnum==1&&String!="TRUE"&&String!="FALSE"){
        skey->show();
        do_AlterDataType_btnEnabled(false);
        skey->skeyWorldInput(String);
        skey->setGeometry(QRect(this->width()-skey->width(),this->height()-51-skey->height(),
                                skey->width(),skey->height()));
    }else if(colnum!=1){
        skey->close();
        Synchro(AlterDataType->TableWidgetCurrentRow,
                AlterDataType->TableWidgetItemQString(AlterDataType->TableWidgetCurrentRow,1));
        AlterDataType->setCancelBtnEnabled(true);
        AlterDataType->setUndoBtnEnabled(true);
        AlterDataType->setOKBtnEnabled(true);
    }else if(colnum==1&&(String=="TRUE"||String=="FALSE")){
        Synchro(AlterDataType->TableWidgetCurrentRow,
                AlterDataType->TableWidgetItemQString(AlterDataType->TableWidgetCurrentRow,1));
        AlterDataType->setFALSEBtnHide(false);
        AlterDataType->setTRUEBtnHide(false);
    }
}

void ropageprogramdata::do_AlterDataType_btnEnabled(bool Enabled)
{
    AlterDataType->setCancelBtnEnabled(Enabled);
    AlterDataType->setUndoBtnEnabled(Enabled);
    AlterDataType->setOKBtnEnabled(Enabled);
}

void ropageprogramdata::do_AlterDataType_TableWidgetItemClicked(QTableWidgetItem *item)
{
    if(item->flags()==(item->flags() & (~Qt::ItemIsEditable))||
            item->flags()==(item->flags() & (~Qt::ItemIsEnabled)))
        skey->close();
}
