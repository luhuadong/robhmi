#ifndef ROPAGEPROGRAMDATA_H
#define ROPAGEPROGRAMDATA_H

#include <QWidget>

#include "header/UI/ProgramData/ProgramData.h"
#include "header/UI/ProgramData/ProgramData_Alter.h"
#include "header/UI/ProgramData/ProgramData_ChooseDataType.h"
#include "header/UI/ProgramData/ProgramData_ChooseAndExitDataType.h"

#include "header/DataManage/DataManage.h"
#include "header/DataManage/DataProcess.h"

#include "header/Common/Common.h"
#include "header/UI/keyworld/skeyworld/skeyWorld.h"
#include "header/UI/keyworld/vkeyworld/vkeyWorld.h"

#include <QDebug>

#define roP_TableWidget_RowCount 22
#define roJ_TableWidget_RowCount 15
#define roW_TableWidget_RowCount 14
#define roT_TableWidget_RowCount 12
#define roZ_TableWidget_RowCount 8
#define roV_TableWidget_RowCount 6

namespace Ui {
class ropageprogramdata;
}

class ropageprogramdata : public QWidget
{
    Q_OBJECT

public:
    explicit ropageprogramdata(QWidget *parent = 0);
    ~ropageprogramdata();

    typedef enum DataTypeView{
        ChooseDataTypeView,ChooseAndExitDataTypeView,NewDataTypeView,AlterDataTypeView
    }DataTypeView;

private slots:
    void do_ChooseDataType_CancelBtnClicked();
    void do_ChooseDataType_ShowData();
    void do_ChooseDataType_View();
    void do_ChooseDataType_TableWidgetCellDoubleClicked(int row, int column, QString);
    void do_ChooseDataType_TableWidgetCellClicked(int row, int column, QString String);

    void do_ChooseAndExitDataType_FilterBtnClicked();
    void do_ChooseAndExitDataType_Refresh();
    void do_ChooseAndExitDataType_ShowDataType();
    void do_ChooseAndExitDataType_NewDataBtnClicked();
    void do_ChooseAndExitDataType_ExitDataBtnClicked();
    void do_ChooseAndExitDataType_TableWidgetCellClicked(int, int, QString);
    void do_ChooseAndExitDataType_TableWidgetCellDoubleClicked(int row, int, QString, QString firstLineQS);

    void do_NewDataView_CancelBtnClicked();
    void do_NewDataView_InitDataBtnClicked();
    void do_NewDataView_OkBtnClicked();

    void do_AlterDataType_OkBtnClicked();
    void do_AlterDataType_UndoBtnClicked();
    void do_AlterDataType_CancelBtnClicked();
    void do_AlterDataType_FALSEBtnClicked();
    void do_AlterDataType_TRUEBtnClicked();

    void do_AlterDataType_TableWidgetCellPressed(int, int colnum, QString String);
    void do_AlterDataType_btnEnabled(bool Enabled);
    void do_AlterDataType_TableWidgetItemClicked(QTableWidgetItem* item);

    void do_skeyBtnClicked(QString str);
    void do_skeyOkBtnClicked();
    void do_skeyCancelBtnClicked();

private:
    Ui::ropageprogramdata *ui;

    ProgramData_ChooseDataType *ChooseDataType;
    ProgramData_ChooseAndExitDataType *ChooseAndExitDataType;
    ProgramData_New *NewDataView;
    ProgramData_Alter *AlterDataType;
    ProgramData_Define *DefineDataType;

    skeyWorld *skey;//纯数字键盘
    vkeyworld *vkey;//

    void Init();
    void DataInit();
    void DataConnectInit();

    void ChooseDataTypeShow();
    void ChooseAndExitDataTypeShow();

    void NewDataInit();//新建数据初始化
    void NewDataRob_RobTargetTypeInit();
    void NewDataRob_JointTargetTypeInit();
    void NewDataRob_WobjDataTypeInit();
    void NewDataRob_ZoneDataTypeInit();
    void NewDataRob_SpeedDataTypeInit();
    void NewDataRob_TargetTypeInit();

    QString ObtainNamePrefix(QString DataName);//
    QString ObtainMax(int flagType, int Num, char s[][16]);//
    void *ObtainCurrentNewData();      //获取当前类型的新建数据

    QString ShowToLineEdit();

    int CurrentDataType;
    int AlterDataNum;//修改第几个
    QString AlterDataName;

    ITP_RobTarget P_NewDataTmp;
    ITP_JointTarget J_NewDataTmp;
    ITP_WobjData W_NewDataTmp;
    ITP_ToolData T_NewDataTmp;
    ITP_ZoneData Z_NewDataTmp;
    ITP_SpeedData V_NewDataTmp;

    ITP_RobTarget P_AlterTmp,*P_Alter;
    ITP_JointTarget J_AlterTmp,*J_Alter;
    ITP_WobjData W_AlterTmp,*W_Alter;
    ITP_ToolData T_AlterTmp,*T_Alter;
    ITP_ZoneData Z_AlterTmp,*Z_Alter;
    ITP_SpeedData V_AlterTmp,*V_Alter;

    void Synchro(int TableWidgetCurrentRow,QString str);

    void ShowAlter_P(ITP_RobTarget *P,QString DataName);
    void ShowAlter_J(ITP_JointTarget *J, QString DataName);
    void ShowAlter_W(ITP_WobjData *W,QString DataName);
    void ShowAlter_T(ITP_ToolData *T,QString DataName);
    void ShowAlter_Z(ITP_ZoneData *Z,QString DataName);
    void ShowAlter_V(ITP_SpeedData *V,QString DataName);
};

#endif // ROPAGEPROGRAMDATA_H
