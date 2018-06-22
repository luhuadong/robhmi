#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

void ropageprogramdata::do_ChooseAndExitDataType_FilterBtnClicked()
{

}

void ropageprogramdata::do_ChooseAndExitDataType_Refresh()
{

}

void ropageprogramdata::do_ChooseAndExitDataType_ShowDataType()
{
    ui->stackedWidget->setCurrentIndex(ChooseDataTypeView);
}

void ropageprogramdata::do_ChooseAndExitDataType_NewDataBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(NewDataTypeView);

    NewDataInit();//新建数据初始化

    NewDataView->setNameLineEditText(ShowToLineEdit());
}

void ropageprogramdata::do_ChooseAndExitDataType_ExitDataBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(AlterDataTypeView);
}

void ropageprogramdata::do_ChooseAndExitDataType_TableWidgetCellClicked(int ,int ,QString )
{

}

void ropageprogramdata::do_ChooseAndExitDataType_TableWidgetCellDoubleClicked(int row,int,QString,QString firstLineQS)
{
    ui->stackedWidget->setCurrentIndex(AlterDataTypeView);

    AlterDataNum = row;

    AlterDataName = firstLineQS;
    AlterDataType->TableWidgetClear();

    switch (CurrentDataType) {
        case DataManage_RobTargetType:
            P_Alter = (ITP_RobTarget*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_P(P_Alter,AlterDataName);
        break;

        case DataManage_JointTargetType:
            J_Alter = (ITP_JointTarget*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_J(J_Alter,AlterDataName);
        break;

        case DataManage_WobjDataType:
            W_Alter = (ITP_WobjData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_W(W_Alter,AlterDataName);
        break;

        case DataManage_ToolDataType:
            T_Alter = (ITP_ToolData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_T(T_Alter,AlterDataName);
        break;

        case DataManage_ZoneDataType:
            Z_Alter = (ITP_ZoneData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_Z(Z_Alter,AlterDataName);
        break;

        case DataManage_SpeedDataType:
            V_Alter = (ITP_SpeedData*)getData(CurrentDataType,AlterDataName.toLocal8Bit().data());
            ShowAlter_V(V_Alter,AlterDataName);
        break;
        default:break;
    }
}

