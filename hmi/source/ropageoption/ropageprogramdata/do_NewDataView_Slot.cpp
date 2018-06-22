#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

void ropageprogramdata::do_NewDataView_CancelBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(ChooseAndExitDataTypeView);
}

void ropageprogramdata::do_NewDataView_OkBtnClicked()
{
    DataManage_Add(&robDataBuffer,&robDataName,CurrentDataType,ObtainCurrentNewData(),
                   NewDataView->getnameLineEditText().toLocal8Bit().data());//内存中添加数据

    switch (CurrentDataType) {
        case DataManage_RobTargetType:
            DataManage_WriteFile_Item(DataManage_RobTargetType,robDataName.PNum-1,
                                  &robDataBuffer.P[robDataName.PNum-1]);
        break;
        case DataManage_JointTargetType:
            DataManage_WriteFile_Item(DataManage_JointTargetType,robDataName.JNum-1,
                                  &robDataBuffer.J[robDataName.JNum-1]);
        break;
        case DataManage_WobjDataType:
            DataManage_WriteFile_Item(DataManage_WobjDataType,robDataName.WNum-1,
                                  &robDataBuffer.W[robDataName.WNum-1]);
        break;
        case DataManage_ToolDataType:
            DataManage_WriteFile_Item(DataManage_ToolDataType,robDataName.TNum-1,
                                  &robDataBuffer.T[robDataName.TNum-1]);
        break;
        case DataManage_ZoneDataType:
            DataManage_WriteFile_Item(DataManage_ZoneDataType,robDataName.ZNum-1,
                                  &robDataBuffer.Z[robDataName.ZNum-1]);
        break;
        case DataManage_SpeedDataType:
            DataManage_WriteFile_Item(DataManage_SpeedDataType,robDataName.VNum-1,
                                  &robDataBuffer.V[robDataName.VNum-1]);
        break;
        default:break;
    }

    ui->stackedWidget->setCurrentIndex(ChooseAndExitDataTypeView);
}

void ropageprogramdata::do_NewDataView_InitDataBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(AlterDataTypeView);
}

