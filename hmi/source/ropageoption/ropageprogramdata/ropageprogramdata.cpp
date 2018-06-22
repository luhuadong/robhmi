#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

ropageprogramdata::ropageprogramdata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ropageprogramdata)
{
    ui->setupUi(this);
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);
    ui->stackedWidget->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    Init();
    DataConnectInit();
}

ropageprogramdata::~ropageprogramdata()
{
    delete ui;
}

void ropageprogramdata::Init()
{
    skey = new skeyWorld(this);
    skey->close();

    DataInit();
}

void ropageprogramdata::DataInit()
{
    ChooseDataType = new ProgramData_ChooseDataType;
    ChooseAndExitDataType = new ProgramData_ChooseAndExitDataType;
    NewDataView = new ProgramData_New;
    AlterDataType = new ProgramData_Alter;

    ui->stackedWidget->addWidget(ChooseDataType);
    ui->stackedWidget->addWidget(ChooseAndExitDataType);
    ui->stackedWidget->addWidget(NewDataView);
    ui->stackedWidget->addWidget(AlterDataType);

    ChooseDataTypeShow();
}

void ropageprogramdata::DataConnectInit()
{
    connect(ChooseDataType,SIGNAL(btnShowDataClicked_SIG()),
            this,SLOT(do_ChooseDataType_ShowData()));
    connect(ChooseDataType,SIGNAL(btnViewClicked_SIG()),
            this,SLOT(do_ChooseDataType_View()));
    connect(ChooseDataType,SIGNAL(TableWidgetCellDoubleClicked_SIG(int,int,QString)),
            this,SLOT(do_ChooseDataType_TableWidgetCellDoubleClicked(int,int,QString)));
    connect(ChooseDataType,SIGNAL(TableWidgetCellPressed_SIG(int,int,QString)),
            this,SLOT(do_ChooseDataType_TableWidgetCellClicked(int,int,QString)));

    connect(ChooseAndExitDataType,SIGNAL(btnFilterClicked_SIG()),
            this,SLOT(do_ChooseAndExitDataType_FilterBtnClicked()));
    connect(ChooseAndExitDataType,SIGNAL(btnRefreshClicked_SIG()),
            this,SLOT(do_ChooseAndExitDataType_Refresh()));
    connect(ChooseAndExitDataType,SIGNAL(btnShowDataTypeClicked_SIG()),
            this,SLOT(do_ChooseAndExitDataType_ShowDataType()));
    connect(ChooseAndExitDataType,SIGNAL(btnNewDataClicked_SIG()),
            this,SLOT(do_ChooseAndExitDataType_NewDataBtnClicked()));
    connect(ChooseAndExitDataType,SIGNAL(btnExitDataClicked_SIG()),
            this,SLOT(do_ChooseAndExitDataType_ExitDataBtnClicked()));

    connect(ChooseAndExitDataType,SIGNAL(TableWidgetCellPressed_SIG(int,int,QString)),
            this,SLOT(do_ChooseAndExitDataType_TableWidgetCellClicked(int,int,QString)));
    connect(ChooseAndExitDataType,SIGNAL(TableWidgetCellDoubleClicked_SIG(int,int,QString,QString)),
            this,SLOT(do_ChooseAndExitDataType_TableWidgetCellDoubleClicked(int,int,QString,QString)));

    connect(NewDataView,SIGNAL(CancelBtnClicked_SIG()),
            this,SLOT(do_NewDataView_CancelBtnClicked()));
    connect(NewDataView,SIGNAL(InitDataBtnClicked_SIG()),
            this,SLOT(do_NewDataView_InitDataBtnClicked()));
    connect(NewDataView,SIGNAL(OkBtnClicked_SIG()),
            this,SLOT(do_NewDataView_OkBtnClicked()));

    connect(AlterDataType,SIGNAL(CancelBtnClicked_SIG()),
            this,SLOT(do_AlterDataType_CancelBtnClicked()));
    connect(AlterDataType,SIGNAL(UndoBtnClicked_SIG()),
            this,SLOT(do_AlterDataType_UndoBtnClicked()));
    connect(AlterDataType,SIGNAL(TRUEBtnClicked_SIG()),
            this,SLOT(do_AlterDataType_TRUEBtnClicked()));
    connect(AlterDataType,SIGNAL(FALSEBtnClicked_SIG()),
            this,SLOT(do_AlterDataType_FALSEBtnClicked()));
    connect(AlterDataType,SIGNAL(OkBtnClicked_SIG()),
            this,SLOT(do_AlterDataType_OkBtnClicked()));
    connect(AlterDataType,SIGNAL(TableWidgetCellPressed_SIG(int,int,QString)),
            this,SLOT(do_AlterDataType_TableWidgetCellPressed(int,int,QString)));
    connect(AlterDataType,SIGNAL(TableWidgetItemClicked_SIG(QTableWidgetItem*)),
            this,SLOT(do_AlterDataType_TableWidgetItemClicked(QTableWidgetItem*)));

    connect(skey,SIGNAL(btnClicked_SIG(QString)),this,SLOT(do_skeyBtnClicked(QString)));
    connect(skey,SIGNAL(cancelBtn_SIG()),this,SLOT(do_skeyCancelBtnClicked()));
    connect(skey,SIGNAL(okBtn_SIG()),this,SLOT(do_skeyOkBtnClicked()));
}

QString ropageprogramdata::ShowToLineEdit()
{
    //每组数据都有默认的变量名前缀:RobTargetType:P   JointTargetType:J   W   T   Z   V...
    switch (CurrentDataType) {
        case DataManage_RobTargetType:
            return ObtainMax(DataManage_RobTargetType,robDataName.PNum,
                             robDataName.PName);

            break;
        case DataManage_JointTargetType:
            return ObtainMax(DataManage_JointTargetType,robDataName.JNum,
                             robDataName.JName);

            break;
        case DataManage_WobjDataType:
            return ObtainMax(DataManage_WobjDataType,robDataName.WNum,
                             robDataName.WName);

            break;
        case DataManage_ToolDataType:
            return ObtainMax(DataManage_ToolDataType,robDataName.TNum,
                             robDataName.TName);
            break;
        case DataManage_ZoneDataType:
            return ObtainMax(DataManage_ZoneDataType,robDataName.VNum,
                             robDataName.ZName);

            break;
        case DataManage_SpeedDataType:
            return ObtainMax(DataManage_SpeedDataType,robDataName.VNum,
                             robDataName.VName);
            break;
        default:break;
    }
    return NULL;
}

QString ropageprogramdata::ObtainNamePrefix(QString DataName)
{
    QString NamePrefix = DataName ;

    for(int i = NamePrefix.length()-1;i>0;i--){
        if(NamePrefix.at(i).digitValue() != -1)
            NamePrefix.remove(i,1);
        else
            break;
    }
    return NamePrefix;
}

void *ropageprogramdata::ObtainCurrentNewData()
{
    void* Data;
    switch (CurrentDataType) {
        case DataManage_RobTargetType:Data = &P_NewDataTmp;break;
        case DataManage_JointTargetType:Data = &J_NewDataTmp;break;
        case DataManage_WobjDataType:Data = &W_NewDataTmp;break;
        case DataManage_ToolDataType:Data = &T_NewDataTmp;break;
        case DataManage_ZoneDataType:Data = &Z_NewDataTmp;break;
        case DataManage_SpeedDataType:Data = &V_NewDataTmp;break;
        default:break;
    }
    return Data;
}

QString ropageprogramdata::ObtainMax(int flagType, int Num, char s[][16])
{
    QString DataName_tmp;
    QString DataName , NamePrefix;
    int snum,i;

    QString DataType[DataManage_DataNum] = {
        "P","J","W","T","Z","V"
    };

    for(i=0;i<Num;i++){
        DataName_tmp = QString(s[i]);
        if(ObtainNamePrefix(s[i]) == DataType[flagType]){
            if(QString::compare(DataName_tmp,DataName,Qt::CaseSensitive)>0||
                    DataName_tmp.length()>DataName.length()||i==1)
                DataName = DataName_tmp;
        }
    }

    if(DataName.isEmpty()){
        snum = 0;
    }else
        snum = Obtain_Snum(DataName.toLocal8Bit().data())+1;

    NamePrefix = DataType[flagType];

    return NamePrefix.append("%0").arg(snum);
}

void ropageprogramdata::NewDataInit()
{
    switch (CurrentDataType) {
        case DataManage_RobTargetType:NewDataRob_RobTargetTypeInit();break;
        case DataManage_JointTargetType:NewDataRob_JointTargetTypeInit();break;
        case DataManage_WobjDataType:NewDataRob_WobjDataTypeInit();break;
        case DataManage_ToolDataType:NewDataRob_TargetTypeInit();break;
        case DataManage_ZoneDataType:NewDataRob_ZoneDataTypeInit();break;
        case DataManage_SpeedDataType:NewDataRob_SpeedDataTypeInit();break;
        default:break;
    }
}

void ropageprogramdata::NewDataRob_RobTargetTypeInit()
{
    P_NewDataTmp.pose.trans.x = 0;
    P_NewDataTmp.pose.trans.y = 0;
    P_NewDataTmp.pose.trans.z = 0;

    P_NewDataTmp.pose.rot.s = 0;
    P_NewDataTmp.pose.rot.x = 0;
    P_NewDataTmp.pose.rot.y = 0;
    P_NewDataTmp.pose.rot.z = 0;

    P_NewDataTmp.robconf.cf1 = 0;
    P_NewDataTmp.robconf.cf4 = 0;
    P_NewDataTmp.robconf.cf6 = 0;
    P_NewDataTmp.robconf.cfx = 0;

    for(int i =0;i<6;i++)
        P_NewDataTmp.extax.eax[i] = 0;
}

void ropageprogramdata::NewDataRob_JointTargetTypeInit()
{
    for(int i =0;i<6;i++){
        J_NewDataTmp.robax.rax[i] = 0;
        J_NewDataTmp.extax.eax[i] = 0;
    }
}

void ropageprogramdata::NewDataRob_WobjDataTypeInit()
{
    W_NewDataTmp.robhold = '1';
    W_NewDataTmp.ufmec = NULL;
    W_NewDataTmp.ufprog = '1';

    W_NewDataTmp.uframe.trans.x = 0;
    W_NewDataTmp.uframe.trans.y = 0;
    W_NewDataTmp.uframe.trans.z = 0;

    W_NewDataTmp.uframe.rot.s = 0;
    W_NewDataTmp.uframe.rot.x = 0;
    W_NewDataTmp.uframe.rot.y = 0;
    W_NewDataTmp.uframe.rot.z = 0;
}

void ropageprogramdata::NewDataRob_TargetTypeInit()
{
    T_NewDataTmp.robhold = '1';

    T_NewDataTmp.tframe.trans.x = 0;
    T_NewDataTmp.tframe.trans.y = 0;
    T_NewDataTmp.tframe.trans.z = 0;

    T_NewDataTmp.tframe.rot.s = 0;
    T_NewDataTmp.tframe.rot.x = 0;
    T_NewDataTmp.tframe.rot.y = 0;
    T_NewDataTmp.tframe.rot.z = 0;
}

void ropageprogramdata::NewDataRob_ZoneDataTypeInit()
{
    Z_NewDataTmp.finep = '0';

    Z_NewDataTmp.inpos.followtime = 0;
    Z_NewDataTmp.inpos.progsynch = 0;
    Z_NewDataTmp.inpos.stoppoint = 0;
    Z_NewDataTmp.inpos.stoptime = 0;

    Z_NewDataTmp.inpos.inpos.maxtime = 0;
    Z_NewDataTmp.inpos.inpos.mintime = 0;
    Z_NewDataTmp.inpos.inpos.position = 0;
    Z_NewDataTmp.inpos.inpos.speed = 0;

    Z_NewDataTmp.bgnzone.pzone_eax = 0;
    Z_NewDataTmp.bgnzone.pzone_ori = 0;
    Z_NewDataTmp.bgnzone.zone_leax = 0;
    Z_NewDataTmp.bgnzone.pzone_tcp = 0;
    Z_NewDataTmp.bgnzone.zone_ori = 0;
    Z_NewDataTmp.bgnzone.zone_reax = 0;
}

void ropageprogramdata::NewDataRob_SpeedDataTypeInit()
{
    V_NewDataTmp.time = 0;
    V_NewDataTmp.v_tcp = 0;
    V_NewDataTmp.v_leax = 0;
    V_NewDataTmp.v_reax = 0;
    V_NewDataTmp.v_ort = 0;
}
