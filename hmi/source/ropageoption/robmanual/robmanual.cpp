#define JOGGING_GLOBALS
#define PROGRAMDATA_GLOBALS
#include "header/ropageoption/robmanual/common.h"

#include "header/ropageoption/robmanual/robmanual.h"

#include <QPalette>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <QAbstractItemView>
#include <QMessageBox>


RobManual::RobManual(QWidget *parent) :
    QWidget(parent)
{
    dataTypesStrList<<tr("robtarget")<<tr("jointtarget")<<tr("tooldata")
                   <<tr("wobjdata")<<tr("loaddata")<<tr("zonedata")
                  <<tr("speeddata")<<tr("bool")<<tr("num")<<tr("string");

    /* ******************** 最大速度定义 ********************* */
    MaxSpeed_Joint[0] = ITP_angle2radian(156);   // 六个关节轴的最大速度（单位：度每秒）[156 140 156 270 180 430]
    MaxSpeed_Joint[1] = ITP_angle2radian(140);
    MaxSpeed_Joint[2] = ITP_angle2radian(156);
    MaxSpeed_Joint[3] = ITP_angle2radian(270);
    MaxSpeed_Joint[4] = ITP_angle2radian(180);
    MaxSpeed_Joint[5] = ITP_angle2radian(430);
    MaxSpeed_Linear = 1500;     // 线性运动最大速度（单位：毫米每秒）1500
    MaxSpeed_Reorient = ITP_angle2radian(180);   // 重定向最大速度（单位：毫米每秒）1200，这里设为180度每秒

    JoggingSpeedRate = 0.5; // 手动操纵的最大速度倍率
    SysSpeedRate = 0.5;     // 机器人系统的速度倍率

    /* ************* 以下是手动操纵界面中用到的结构体（初始化） ************* */
    joggingPar.mechanicalUnit = Jogging::PAR_ROB_1; // 机械单元默认选择ROB_1
    joggingPar.absoluteAccuracy = Jogging::PAR_OFF; // 绝对精度默认选择OFF
    joggingPar.motionMode = Jogging::PAR_AXIS1_6;   // 运动模式默认选择AXIS1_6（关节运动模式）
    joggingPar.coordinateSystem = Jogging::PAR_BASE;// 坐标系默认选择BASE（基坐标）【注意：当运动模式为AXIS1_6时该选项无效】
    joggingPar.increment = Jogging::PAR_NONE;       // 增量默认选择NONE
    joggingPar.maxSpeed = ITP_MaxSpeed;  // 手动操作的最大速度（12000 mm/min）
    joggingPar.curSpeed = 0.0;  // 手动操作的当前速度（单位已转换）

    positionFmt.coordinateSys = Jogging::PAR_SHOW_WORLD;    // 【显示格式】的位置显示方式默认选择<大地坐标>
    positionFmt.orientationFmt = Jogging::PAR_SHOW_QUATERNION;  // 【显示格式】的方向格式默认选择<四元数>
    positionFmt.angleUnit = Jogging::PAR_SHOW_DEGREES;  // 【显示格式】的角度单位默认选择<度>

    SW_Increment = SW_OFF;  // 默认关闭增量开关
    incVal[Jogging::PAR_NONE].axis      = 0.0;      // (rad)    无
    incVal[Jogging::PAR_NONE].linear    = 0.0;      // (mm)
    incVal[Jogging::PAR_NONE].reorient  = 0.0;      // (rad)
    incVal[Jogging::PAR_SMALL].axis     = 0.0001;   // (rad)    小
    incVal[Jogging::PAR_SMALL].linear   = 0.005;    // (mm)
    incVal[Jogging::PAR_SMALL].reorient = 0.0005;   // (rad)
    incVal[Jogging::PAR_MEDIUM].axis    = 0.0004;   // (rad)    中
    incVal[Jogging::PAR_MEDIUM].linear  = 1.0;      // (mm)
    incVal[Jogging::PAR_MEDIUM].reorient= 0.004;    // (rad)
    //incVal[Jogging::PAR_LARGE].axis     = 0.0025;   // (rad)    大
    incVal[Jogging::PAR_LARGE].axis     = 0.025;   // (rad)    大
    incVal[Jogging::PAR_LARGE].linear   = 5.0;      // (mm)
    incVal[Jogging::PAR_LARGE].reorient = 0.009;    // (rad)
    incVal[Jogging::PAR_USER] = incVal[Jogging::PAR_SMALL]; // 用户增量的缺省值等于小增量的值


#ifdef Windows
    DataManage_InitShareMem_InputData(1, (void **)&pInputData); // 初始化手动操纵的参数输入（共享内存）
    DataManage_InitShareMem_OutputData(0,(void **)&pOutputData);    // 初始化手动操纵的位置数据输出（共享内存）

    // ITP_Mode_JointOp_SpeedMode为关节模式，ITP_Mode_CoordinateOp_SpeedMode为坐标模式，-1为未定义
    if(Jogging::PAR_AXIS1_6 == joggingPar.motionMode) {pInputData->mode = ITP_Mode_JointOp_SpeedAndIncMode;}
    else if(Jogging::PAR_LINEAR == joggingPar.motionMode) {pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;}
    else if(Jogging::PAR_REORIENT == joggingPar.motionMode) {pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;}

    // -1表示未定义，0表示基坐标系，1表示工具坐标系，2表示用户自定义坐标系（基准坐标系为基坐标系）
    if(Jogging::PAR_WORLD == joggingPar.coordinateSystem) {pInputData->flagCoordinate = -1;}
    else if(Jogging::PAR_BASE == joggingPar.coordinateSystem) {pInputData->flagCoordinate = 0;}
    else if(Jogging::PAR_TOOL == joggingPar.coordinateSystem) {pInputData->flagCoordinate = 1;}
    else if(Jogging::PAR_WORKOBJECT == joggingPar.coordinateSystem) {pInputData->flagCoordinate = 2;}

    // 速度倍率设为0.2
    //pInputData->rate = 0.2;

    for(int i=0; i<ITP_RobotJointNum; i++) {pInputData->robotMove[i] = 0;}  // 机器人停止
    for(int i=0; i<ITP_ExtaxAxisNum; i++) {pInputData->extaxRotate[i] = 0;} // 外部轴停止

    pInputData->flagIncUpdate = 0;  // 增量标识
    pInputData->jogMoveVal = 0.0;   // 增量距离，初始值设为任意值即可，因为操纵杆动作时会对其重新赋值

    sysInitRobTarget = pOutputData->curRob; // 定义一个机器人位置点，用于测试【转到】功能

#endif

    /* ************* 以下是手动操纵界面中用到的全局字符串或字符串链表（初始化） ************* */
    mechanicalUnitStrList<<tr("ROB_1");      // 机械单元选项文字
    absoluteAccuracyStrList<<tr("Off")<<tr("On");    // 绝对精度选项文字
    motionModeStrList<<tr("轴 1 - 6")<<tr("线性")<<tr("重定位");          // 动作模式选项文字
    coordinateSystemStrList<<tr("大地坐标")<<tr("基坐标")<<tr("工具坐标")<<tr("工件坐标");    // 坐标系选项文字
    //toolStrList;                // 工具坐标选项文字
    //workObjectStrList;          // 工件坐标选项文字
    //payloadStrList;             // 有效载荷选项文字
    //joystickLockStrList;        // 操纵杆锁定选项文字
    incrementStrList<<tr("无")<<tr("小")<<tr("中")<<tr("大")<<tr("用户");           // 增量选项文字
    propertyTipsStrList<<tr("选择要更改其状态的机械单元。")<<("选择是否开启绝对精度。")<<tr("选择动作模式。")
                      <<tr("选择坐标系。")<<tr("从列表中选择一个工具坐标。")<<tr("从列表中选择一个工件坐标。")
                     <<tr("从列表中选择一个有效载荷。")<<tr("选择需要锁定的操纵杆方向。")<<tr("选择增量模式。");

    jointOpKeyStrList<<tr("1:")<<tr("2:")<<tr("3:")<<tr("4:")<<tr("5:")<<tr("6:")<<tr(" ");
    cooOpKeyStrList_Qua<<tr("X:")<<tr("Y:")<<tr("Z:")<<tr("q1:")<<tr("q2:")<<tr("q3")<<tr("q4");
    cooOpKeyStrList_Eul<<tr("X:")<<tr("Y:")<<tr("Z:")<<tr("EZ:")<<tr("EY:")<<tr("EX:")<<tr(" ");
    jointOpUnitStrList_Deg<<tr("°")<<tr("°")<<tr("°")<<tr("°")<<tr("°")<<tr("°")<<tr(" ");
    jointOpUnitStrList_Rad<<tr("rad")<<tr("rad")<<tr("rad")<<tr("rad")<<tr("rad")<<tr("rad")<<tr(" ");
    cooOpUnitStrList_Qua<<tr("mm")<<tr("mm")<<tr("mm")<<(" ")<<(" ")<<(" ")<<(" ");
    cooOpUnitStrList_Eul_Deg<<tr("mm")<<tr("mm")<<tr("mm")<<tr("°")<<tr("°")<<tr("°")<<tr(" ");
    cooOpUnitStrList_Eul_Rad<<tr("mm")<<tr("mm")<<tr("mm")<<tr("rad")<<tr("rad")<<tr("rad")<<tr(" ");

    jointMoveBtnStrList<<tr("J1+")<<tr("J1-")<<tr("J2+")<<tr("J2-")<<tr("J3+")<<tr("J3-")
                         <<tr("J4+")<<tr("J4-")<<tr("J5+")<<tr("J5-")<<tr("J6+")<<tr("J6-");
    coordMoveBtnStrList<<tr("X+")<<tr("X-")<<tr("Y+")<<tr("Y-")<<tr("Z+")<<tr("Z-")
                         <<tr("A+")<<tr("A-")<<tr("B+")<<tr("B-")<<tr("C+")<<tr("C-");


    /* ************************** propertyGroupBox ****************************** */
    this->initPropertyTable();
    /* ************************** poseInfoGroupBox ****************************** */
    this->initPositionTable();
    /* ****************************** directionGroupBox ********************************** */
    this->initDirectionBtnBox();

    /* ************************** optionBarFrame ****************************** */
    optionBarFrame = new QFrame(this);
//    optionBarFrame->setFrameStyle(QFrame::Box);
//    optionBarFrame->setAutoFillBackground(true);
//    QPalette p = palette();
//    p.setColor(QPalette::Window, Qt::gray);
//    optionBarFrame->setPalette(p);
    optionBarFrame->setStyleSheet("background-color: Gray;");

    alignBtn = new QPushButton(tr("对准..."));
    gotoBtn = new QPushButton(tr("转到..."));
    activateBtn = new QPushButton(tr("启动..."));
    //newBtn = new QPushButton(tr("新建..."));
    //editBtn = new QPushButton(tr("编辑"));
    //okBtn = new QPushButton(tr("确定"));
    //cancelBtn = new QPushButton(tr("取消"));
    //optionBarSpacer = new QSpacerItem;
    optionBarLayout = new QHBoxLayout(optionBarFrame);
    optionBarLayout->addWidget(alignBtn);
    optionBarLayout->addWidget(gotoBtn);
    optionBarLayout->addWidget(activateBtn);
    optionBarLayout->addStretch();
    connect(alignBtn, SIGNAL(clicked()), this, SLOT(alignBtnClicked()));
    connect(gotoBtn, SIGNAL(clicked()), this, SLOT(gotoBtnClicked()));
    connect(activateBtn, SIGNAL(clicked()), this, SLOT(activateBtnClicked()));



    /* ************************** mainLayout ****************************** */
    topRightLayout = new QVBoxLayout;
    topRightLayout->addWidget(poseInfoGroupBox, 2);
    topRightLayout->addWidget(directionGroupBox, 1);

    topLayout = new QHBoxLayout;
    //topLayout->setMargin(15);
    topLayout->setContentsMargins(15, 15, 15, 10);
    topLayout->setSpacing(5);
    topLayout->addWidget(propertyGroupBox, 3);
    topLayout->addLayout(topRightLayout, 2);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout, 9);
    mainLayout->addWidget(optionBarFrame, 1);


    settingWidget = new SettingWidget(this);
    //settingWidget->setGeometry(0, 0, 680, 500);
    settingWidget->setGeometry(0, 0, 800, 500);
    settingWidget->hide();  // 隐藏子界面

    connect(settingWidget, SIGNAL(propertyChanged(int,QString)), this, SLOT(propertyChanged(int,QString)));
    connect(settingWidget, SIGNAL(positionChanged()), this, SLOT(updatePositionTable()));

    updatePoseDataThread = new UpdatePoseDataThread();
    updatePoseDataThread->start();
    connect(updatePoseDataThread, SIGNAL(poseDataUpdated(QString*)), this, SLOT(updatePoseData(QString*)));

    //connect(settingWidget, SIGNAL(closeSubWidget()), this, SLOT(closeSubWidget()));
    keyLongPressListener = new QTimer;
    keyLongPressListener->setSingleShot(true);  // 只做一次定时操作
    connect(keyLongPressListener, SIGNAL(timeout()), this, SLOT(keyLongPressListenerRespond()));

    incrementTimer = new QTimer;
    connect(incrementTimer, SIGNAL(timeout()), this, SLOT(incrementTimerRespond()));
}

RobManual::~RobManual()
{

}



// 【属性】框初始化
void RobManual::initPropertyTable()
{
    propertyGroupBox = new QGroupBox(tr("点击属性并更改"));
    propertyGroupBox->setStyleSheet("border-color:Black");
    propertyTabWidget = new QTableWidget(PROPERTY_ROWS, PROPERTY_COLUMNS); // 创建一个9行2列的表格对象
    propertyTabWidget->setShowGrid(false);  // 不显示网格
    propertyTabWidget->setFrameShape(QFrame::NoFrame);  // 去除表格边框
    propertyTabWidget->setEditTriggers(false);  // 设置为不可编辑
    propertyTabWidget->horizontalHeader()->hide();  // setVisible(false)和setHidden(true)方法也可以隐藏表头
    propertyTabWidget->verticalHeader()->hide();
    propertyTabWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    propertyTabWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    propertyTabWidget->setSelectionBehavior(QAbstractItemView::SelectItems);    // 一次选择一个item
    propertyTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);    // 不允许多选
    propertyTabWidget->setFont(QFont("ZYSong18030", 14));   // 设置14号字体大小

    QGridLayout *layout = new QGridLayout;
    layout->setMargin(18);
    //layout->setSpacing(5);
    layout->addWidget(propertyTabWidget, 0, 0, 1, 2);
    propertyGroupBox->setLayout(layout);

    /* ***********************************************************************
     * 属性表的Key的text在这里设置好，而Value的text则要根据手动操纵模块的参数来设置。
    *********************************************************************** */

    propertyTabMecKeyItem = new QTableWidgetItem(tr("机械单元："));    // 机械单元
    propertyTabMecValItem = new QTableWidgetItem(tr("ROB_1"));

    propertyTabAbsKeyItem = new QTableWidgetItem(tr("绝对精度"));    // 绝对精度（设置为不使能，暂不支持此功能）
    propertyTabAbsKeyItem->setFlags(propertyTabAbsKeyItem->flags() & ~(Qt::ItemIsEnabled));
    propertyTabAbsValItem = new QTableWidgetItem(tr("off"));
    propertyTabAbsValItem->setFlags(propertyTabAbsValItem->flags() & ~(Qt::ItemIsEnabled));

    propertyTabMotKeyItem = new QTableWidgetItem(tr("动作模式："));    // 动作模式
    propertyTabMotValItem = new QTableWidgetItem(tr("轴 1 - 6"));

    propertyTabCooKeyItem = new QTableWidgetItem(tr("坐标系："));    // 坐标系（当模式为【坐标操作】时有效，默认为【关节操作】，故不使能）
    propertyTabCooKeyItem->setFlags(propertyTabCooKeyItem->flags() & ~(Qt::ItemIsEnabled));
    propertyTabCooValItem = new QTableWidgetItem(tr("基坐标"));
    propertyTabCooValItem->setFlags(propertyTabCooValItem->flags() & ~(Qt::ItemIsEnabled));

    propertyTabTooKeyItem = new QTableWidgetItem(tr("工具坐标："));    // 工具坐标
    propertyTabTooValItem = new QTableWidgetItem(tr("tool0"));

    propertyTabWorKeyItem = new QTableWidgetItem(tr("工件坐标："));    // 工件坐标
    propertyTabWorValItem = new QTableWidgetItem(tr("wobj0"));

    propertyTabPayKeyItem = new QTableWidgetItem(tr("有效载荷："));    // 有效载荷（设置为不使能，暂不支持此功能）
    //propertyTabPayKeyItem->setFlags(propertyTabPayKeyItem->flags() & ~(Qt::ItemIsEnabled));
    propertyTabPayValItem = new QTableWidgetItem(tr("load0"));
    //propertyTabPayValItem->setFlags(propertyTabPayValItem->flags() & ~(Qt::ItemIsEnabled));

    propertyTabJoyKeyItem = new QTableWidgetItem(tr("操纵杆锁定："));    // 操纵杆锁定（设置为不使能，暂不支持此功能）
    propertyTabJoyKeyItem->setFlags(propertyTabJoyKeyItem->flags() & ~(Qt::ItemIsEnabled));
    propertyTabJoyValItem = new QTableWidgetItem(tr("无"));
    propertyTabJoyValItem->setFlags(propertyTabJoyValItem->flags() & ~(Qt::ItemIsEnabled));

    propertyTabIncKeyItem = new QTableWidgetItem(tr("增量："));    // 增量
    propertyTabIncValItem = new QTableWidgetItem(tr("无"));


    propertyTabWidget->setItem(0, 0, propertyTabMecKeyItem);
    propertyTabWidget->setItem(0, 1, propertyTabMecValItem);

    propertyTabWidget->setItem(1, 0, propertyTabAbsKeyItem);
    propertyTabWidget->setItem(1, 1, propertyTabAbsValItem);

    propertyTabWidget->setItem(2, 0, propertyTabMotKeyItem);
    propertyTabWidget->setItem(2, 1, propertyTabMotValItem);

    propertyTabWidget->setItem(3, 0, propertyTabCooKeyItem);
    propertyTabWidget->setItem(3, 1, propertyTabCooValItem);

    propertyTabWidget->setItem(4, 0, propertyTabTooKeyItem);
    propertyTabWidget->setItem(4, 1, propertyTabTooValItem);

    propertyTabWidget->setItem(5, 0, propertyTabWorKeyItem);
    propertyTabWidget->setItem(5, 1, propertyTabWorValItem);

    propertyTabWidget->setItem(6, 0, propertyTabPayKeyItem);
    propertyTabWidget->setItem(6, 1, propertyTabPayValItem);

    propertyTabWidget->setItem(7, 0, propertyTabJoyKeyItem);
    propertyTabWidget->setItem(7, 1, propertyTabJoyValItem);

    propertyTabWidget->setItem(8, 0, propertyTabIncKeyItem);
    propertyTabWidget->setItem(8, 1, propertyTabIncValItem);
    // -------------------------------------------

    //tab->resizeRowsToContents();
    //tab->resizeColumnsToContents();
    propertyTabWidget->setColumnWidth(0, 173);
    //propertyTabWidget->setColumnWidth(0, propertyTabWidget->width() / 2);
    //propertyTabWidget->setColumnWidth(1, 173);
    propertyTabWidget->horizontalHeader()->setStretchLastSection(true);
    propertyTabWidget->setRowHeight(0, 41);
    propertyTabWidget->setRowHeight(1, 41);
    propertyTabWidget->setRowHeight(2, 41);
    propertyTabWidget->setRowHeight(3, 41);
    propertyTabWidget->setRowHeight(4, 41);
    propertyTabWidget->setRowHeight(5, 41);
    propertyTabWidget->setRowHeight(6, 41);
    propertyTabWidget->setRowHeight(7, 41);
    //propertyTabWidget->setRowHeight(8, 41);
    propertyTabWidget->verticalHeader()->setStretchLastSection(true);
    //tab->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //tab->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    //connect(propertyTabWidget, SIGNAL(cellClicked(int ,int )), this, SLOT(showInformationMsg(int ,int )));
    connect(propertyTabWidget, SIGNAL(cellPressed(int,int)), this, SLOT(changeProperties(int,int)));
}

// 【位置】框初始化
void RobManual::initPositionTable()
{
    poseInfoGroupBox = new QGroupBox(tr("位置"));
    poseInfoGroupBox->setStyleSheet("border-color:rgb(0, 0, 0)");
    poseLabel = new QLabel(tr("坐标中的位置：..."));

    poseTableWidget = new QTableWidget(POSITION_ROWS, POSITION_COLUMNS);
    poseTableWidget->horizontalHeader()->hide();
    poseTableWidget->verticalHeader()->hide();
    //poseTableWidget->setFrameRect(QRect(0, 0, 200, 200));
    poseTableWidget->setEditTriggers(false);
    poseTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    poseTableWidget->setColumnWidth(0, 75);
    poseTableWidget->setColumnWidth(1, 150);
    //poseTableWidget->setColumnWidth(2, 50);
    poseTableWidget->horizontalHeader()->setStretchLastSection(true);
    poseTableWidget->setRowHeight(0, 26);
    poseTableWidget->setRowHeight(1, 26);
    poseTableWidget->setRowHeight(2, 26);
    poseTableWidget->setRowHeight(3, 26);
    poseTableWidget->setRowHeight(4, 26);
    poseTableWidget->setRowHeight(5, 26);
    //poseTableWidget->setRowHeight(6, 26);
    poseTableWidget->verticalHeader()->setStretchLastSection(true);
    poseFormatBtn = new QPushButton(tr("位置格式..."));
    poseFormatBtn->setFixedHeight(25);
    QVBoxLayout *poseBoxLayout = new QVBoxLayout;
    //poseBoxLayout->setMargin(10);
    poseBoxLayout->setContentsMargins(10, 15, 10, 10);
    poseBoxLayout->setSpacing(11);
    poseBoxLayout->addWidget(poseLabel);
    poseBoxLayout->addWidget(poseTableWidget);
    poseBoxLayout->addWidget(poseFormatBtn);
    poseInfoGroupBox->setLayout(poseBoxLayout);



    // 根据当前对关节、坐标操作，四元数、欧拉角的选择来确定【位置】表中第一列的显示格式
    if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)   // 关节操作
    {
        poseLabel->setText(tr(" "));    // 关节操作没有坐标概念，故隐藏坐标提示
        poseKeyItemStrList = &jointOpKeyStrList;
        if(positionFmt.angleUnit == Jogging::PAR_SHOW_DEGREES) {poseUnitItemStrList = &jointOpUnitStrList_Deg;}// 度
        else if(positionFmt.angleUnit == Jogging::PAR_SHOW_RADIANS) {poseUnitItemStrList = &jointOpUnitStrList_Rad;}// 弧度
    }
    else    // 坐标操作
    {
        // 坐标操作有必要显示位置数据是在哪个坐标系中表示的
        poseLabel->setText(tr("Positions in Coord: ") + settingWidget->getPositionShownInWhichCoord());
        if(positionFmt.orientationFmt == Jogging::PAR_SHOW_QUATERNION)  // 四元数
        {
            poseKeyItemStrList = &cooOpKeyStrList_Qua;
            poseUnitItemStrList = &cooOpUnitStrList_Qua;
        }
        else if(positionFmt.orientationFmt == Jogging::PAR_SHOW_EULERANGLES)    // 欧拉角
        {
            poseKeyItemStrList = &cooOpKeyStrList_Eul;
            if(positionFmt.angleUnit == Jogging::PAR_SHOW_DEGREES) {poseUnitItemStrList = &cooOpUnitStrList_Eul_Deg;}// 度
            else if(positionFmt.angleUnit == Jogging::PAR_SHOW_RADIANS) {poseUnitItemStrList = &cooOpUnitStrList_Eul_Rad;}// 弧度
        }
    }

    for(int i=0; i<POSITION_ROWS; i++)
    {
        // 第一列
        QTableWidgetItem *keyItem = new QTableWidgetItem(poseKeyItemStrList->at(i));
        keyItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        keyItem->setTextColor(QColor("Blue"));
        poseTabKeyItemList.append(keyItem);
        poseTableWidget->setItem(i, 0, keyItem);

        // 第二列
        QTableWidgetItem *valItem = new QTableWidgetItem(tr("0.00"));
        valItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        valItem->setTextColor(QColor("Blue"));
        poseTabValItemList.append(valItem);
        poseTableWidget->setItem(i, 1, valItem);

        // 第三列
        QTableWidgetItem *unitItem = new QTableWidgetItem(poseUnitItemStrList->at(i));
        unitItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        unitItem->setTextColor(QColor("Blue"));
        poseTabUnitItemList.append(unitItem);
        poseTableWidget->setItem(i, 2, unitItem);
    }
    //QTableWidget *poseData1 = new QTableWidgetItem(tr(QString::number(ITP_radian2angle())))

    connect(poseFormatBtn, SIGNAL(clicked()), this, SLOT(poseFormatBtnClicked()));

}
// 更新【位置】数据的显示格式
void RobManual::updatePositionTable()
{
    // 根据当前对关节、坐标操作，四元数、欧拉角的选择来确定【位置】表中第一列的显示格式
    if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)   // 关节操作
    {
        poseLabel->setText(tr(" "));    // 关节操作没有坐标概念，故隐藏坐标提示
        poseKeyItemStrList = &jointOpKeyStrList;
        if(positionFmt.angleUnit == Jogging::PAR_SHOW_DEGREES) {poseUnitItemStrList = &jointOpUnitStrList_Deg;}// 度
        else if(positionFmt.angleUnit == Jogging::PAR_SHOW_RADIANS) {poseUnitItemStrList = &jointOpUnitStrList_Rad;}// 弧度
    }
    else    // 坐标操作
    {
        // 坐标操作有必要显示位置数据是在哪个坐标系中表示的
        poseLabel->setText(tr("Positions in Coord: ") + settingWidget->getPositionShownInWhichCoord());
        if(positionFmt.orientationFmt == Jogging::PAR_SHOW_QUATERNION)  // 四元数
        {
            poseKeyItemStrList = &cooOpKeyStrList_Qua;
            poseUnitItemStrList = &cooOpUnitStrList_Qua;
        }
        else if(positionFmt.orientationFmt == Jogging::PAR_SHOW_EULERANGLES)    // 欧拉角
        {
            poseKeyItemStrList = &cooOpKeyStrList_Eul;
            if(positionFmt.angleUnit == Jogging::PAR_SHOW_DEGREES) {poseUnitItemStrList = &cooOpUnitStrList_Eul_Deg;}// 度
            else if(positionFmt.angleUnit == Jogging::PAR_SHOW_RADIANS) {poseUnitItemStrList = &cooOpUnitStrList_Eul_Rad;}// 弧度
        }
    }

    for(int i=0; i<POSITION_ROWS; i++)
    {
        poseTabKeyItemList.at(i)->setText(poseKeyItemStrList->at(i));   // 第一列
        poseTabUnitItemList.at(i)->setText(poseUnitItemStrList->at(i)); // 第三列
    }
}

// 实时更新位置数据
void RobManual::updatePoseData(QString *poseData)
{
    for(int i=0; i<POSITION_ROWS; i++)
    {
        poseTabValItemList.at(i)->setText(poseData[i]);
    }
}

// 方向操纵键的初始化
void RobManual::initDirectionBtnBox()
{
    directionGroupBox = new QGroupBox(tr("方向操纵键"));
    directionGroupBox->setStyleSheet("border-color:rgb(0, 0, 0)");

    QGridLayout *directionBtnLayout = new QGridLayout;
    directionBtnLayout->setMargin(10);
    directionBtnLayout->setSpacing(5);

    if(joggingPar.motionMode == Jogging::PAR_AXIS1_6) {moveBtnTextStrList = &jointMoveBtnStrList;}
    else {moveBtnTextStrList = &coordMoveBtnStrList;}

    // 2015.09.10 改到这里
    QSignalMapper *joggingSigMapper = new QSignalMapper;    // bundles signals from identifiable senders.
    QSignalMapper *standingSigMapper = new QSignalMapper;

    for(int i=0; i<moveBtnTextStrList->size(); i++) // 12个方向操纵键
    {
        QPushButton *moveBtn = new QPushButton(moveBtnTextStrList->at(i));
        moveBtnList.append(moveBtn);
        moveBtn->setStyleSheet("border: 2px solid gray");

        // 将按键加到布局中
        if(0 == i % 2) {directionBtnLayout->addWidget(moveBtn, 0, i/2);}    // 偶数在上排
        else {directionBtnLayout->addWidget(moveBtn, 1, (i-1)/2);}  // 奇数在下排

        //if(i < moveBtnTextStrList->size()/2) {directionBtnLayout->addWidget(moveBtn, 0, i);}
        //else {directionBtnLayout->addWidget(moveBtn, 1, i-(moveBtnTextStrList->size()/2));}

        connect(moveBtn, SIGNAL(pressed()), joggingSigMapper, SLOT(map()));
        connect(moveBtn, SIGNAL(released()), standingSigMapper, SLOT(map()));

        joggingSigMapper->setMapping(moveBtn, Btn_Pos_J1 + i);
        standingSigMapper->setMapping(moveBtn, Btn_Pos_J1 + i);
        //connect(toolBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        //signalMapper->setMapping(toolBtn, (Jogging::PAR_AXIS1_6)+i);
    }
    connect(joggingSigMapper, SIGNAL(mapped(int)), this, SLOT(robotJogging(int)));
    connect(standingSigMapper, SIGNAL(mapped(int)), this, SLOT(robotStanding(int)));
    //connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(motionModeToolBtnClicked(int)));

    directionGroupBox->setLayout(directionBtnLayout);

    this->changeDirectionBtnBox();  // 刷新一下

    //directionBtn11->setObjectName("blueButton");
}

// 改变方向操纵键的显示形式
void RobManual::changeDirectionBtnBox()
{
    if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)   // 关节模式
    {
        moveBtnTextStrList = &jointMoveBtnStrList;
        for(int i=0; i<moveBtnTextStrList->size(); i++)
        {
            moveBtnList.at(i)->setEnabled(true);
            moveBtnList.at(i)->setText(moveBtnTextStrList->at(i));
        }
    }
    else
    {
        moveBtnTextStrList = &coordMoveBtnStrList;

        if(joggingPar.motionMode == Jogging::PAR_LINEAR)    // 线性模式
        {
            for(int i=0; i<moveBtnTextStrList->size(); i++)
            {
                // 前6个使能，后6个屏蔽
                if(i < moveBtnTextStrList->size()/2) {moveBtnList.at(i)->setEnabled(true);}
                else {moveBtnList.at(i)->setEnabled(false);}
                moveBtnList.at(i)->setText(moveBtnTextStrList->at(i));
            }
        }
        else if(joggingPar.motionMode == Jogging::PAR_REORIENT) // 重定位模式
        {
            for(int i=0; i<moveBtnTextStrList->size(); i++)
            {
                // 后6个使能，前6个屏蔽
                if(i < moveBtnTextStrList->size()/2) {moveBtnList.at(i)->setEnabled(false);}
                else {moveBtnList.at(i)->setEnabled(true);}
                moveBtnList.at(i)->setText(moveBtnTextStrList->at(i));
            }
        }
    }
}

// 机器人动
void RobManual::robotJogging(int id)
{
    /* 2015.11.11
     * 增量运动模式下，若用户操作按钮太频繁机器人系统上一步增量运动还未到位，则忽略此次请求；
     * 另一种做法是我们要记录下用户请求的增量运动次数，然后在适当的时候进行移动。
     * 这里采用第一种处理方式，即直接忽略。
    */
    if(pOutputData->moving == 1) return;

    /*
     * 清除上一次操作留下的数据
    */
    pInputData->jogMoveVal = 0.0;
    for(int i=0; i<ITP_RobotJointNum; i++) {pInputData->robotMove[i] = 0;}
    pInputData->moveSpeed = 0;

    if(SW_Increment == SW_OFF)
    {
        // 增量开关关闭时 2015.11.09
        //pInputData->jogMoveVal = 0.0; // 插补模块通过判断 jogMoveVal 的值来确定当前是否处于增量模式 ？
        if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)
        {
            // 每个关节不一样（单位：弧度/插补周期）
            joggingPar.curSpeed = (MaxSpeed_Joint[id/2] * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
            // 设置速度和关节运动轴（通过 robotMove[x] ）
            pInputData->robotMove[id/2] = (id%2 == 0)?(joggingPar.curSpeed):-(joggingPar.curSpeed);
        }
        else if(joggingPar.motionMode == Jogging::PAR_LINEAR)
        {
            // 笛卡尔坐标系下的轴运动速度 = 最大速度 × 速度倍率。注意单位转换（mm/min --> mm/插补周期）
            joggingPar.curSpeed = (MaxSpeed_Linear * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
            // 设置速度和线性运动轴（通过 moveSpeed 和 flagMoveItem ）
            pInputData->moveSpeed = (id%2 == 0)?(joggingPar.curSpeed):-(joggingPar.curSpeed);
            pInputData->flagMoveItem = id/2;
        }
        else if(joggingPar.motionMode == Jogging::PAR_REORIENT)
        {
            joggingPar.curSpeed = (MaxSpeed_Reorient * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
            // 设置速度和重定向运动轴（通过 moveSpeed 和 flagMoveItem ）
            pInputData->moveSpeed = (id%2 == 0)?(joggingPar.curSpeed):-(joggingPar.curSpeed);
            pInputData->flagMoveItem = id/2;
        }

        // 上排按键正向运动，下排按键反向运动 ------ 旧版代码
        //if(0 != id % 2) joggingPar.curSpeed = -(joggingPar.curSpeed);   // 速度运动模式的正反用pInputData->robotMove[x]表示
        //pInputData->robotMove[id/2] = joggingPar.curSpeed;
    }
    else if(SW_Increment == SW_ON)
    {
        keyLongPressListener->start(900);   // 如果按钮长按一秒（900+100）以上，就进入增量模式下的持续运动状态
        //pInputData->jogMoveVal = 1.0;   // 插补模块通过判断 jogMoveVal 的值来确定当前是否处于增量模式，那么我需要先对其赋一个非零的值吗？
        // 增量开关开启时 2015.11.09
        if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)
        {
            // 每个关节不一样（单位：弧度/插补周期）
            joggingPar.curSpeed = (MaxSpeed_Joint[id/2] * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
            // 设置速度和关节运动轴（通过 robotMove[x] ）
            pInputData->robotMove[id/2] = joggingPar.curSpeed;
            // 设置增量大小和正反方向（只与 jogMoveVal 有关）
            pInputData->jogMoveVal = (id%2 == 0)?(incVal[joggingPar.increment].axis):-(incVal[joggingPar.increment].axis);
            //pInputData->jogMoveVal = 0;
        }
        else if(joggingPar.motionMode == Jogging::PAR_LINEAR)
        {
            // 笛卡尔坐标系下的轴运动速度 = 最大速度 × 速度倍率。注意单位转换（mm/min --> mm/插补周期）
            joggingPar.curSpeed = (MaxSpeed_Linear * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
            // 设置速度和线性运动轴（通过 moveSpeed 和 flagMoveItem ）
            pInputData->moveSpeed = joggingPar.curSpeed;
            pInputData->flagMoveItem = id/2;
            // 设置增量大小和正反方向（只与 jogMoveVal 有关）
            pInputData->jogMoveVal = (id%2 == 0)?(incVal[joggingPar.increment].linear):-(incVal[joggingPar.increment].linear);
        }
        else if(joggingPar.motionMode == Jogging::PAR_REORIENT)
        {
            joggingPar.curSpeed = (MaxSpeed_Reorient * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
            // 设置速度和重定向运动轴（通过 moveSpeed 和 flagMoveItem ）
            pInputData->moveSpeed = joggingPar.curSpeed;
            pInputData->flagMoveItem = id/2;
            // 设置增量大小和正反方向（只与 jogMoveVal 有关）
            pInputData->jogMoveVal = (id%2 == 0)?(incVal[joggingPar.increment].reorient):-(incVal[joggingPar.increment].reorient);
        }

        // 上排按键正向运动，下排按键反向运动 ------ 旧版代码
        //if(0 != id % 2) pInputData->jogMoveVal = -(pInputData->jogMoveVal); // 增量运动模式的正反用pInputData->jogMoveVal表示
        //pInputData->robotMove[id/2] = joggingPar.curSpeed;

        pInputData->flagIncUpdate = !(pInputData->flagIncUpdate);   // 最后，记得要更新增量标识！
    }


    /* ********************************** Debug **********************************
     * 插补周期为 1ms，Windows系统达不到要求，所以动起来会慢14倍左右
     * **********************************       ********************************** */
    if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)
    {
        qDebug("<Button_%d pressed> speed: %.4lf(rad/period) %.4lf(°/period) %.2lf(rad/s) %.2lf(°/s)", id,
               joggingPar.curSpeed, ITP_radian2angle(joggingPar.curSpeed),
               joggingPar.curSpeed * 1000, ITP_radian2angle(joggingPar.curSpeed) * 1000);
    }
    else if(joggingPar.motionMode == Jogging::PAR_LINEAR)
    {
        qDebug("<Button_%d pressed> speed: %.4lf(mm/period) %.2lf(mm/min) %.2lf(mm/s)", id, joggingPar.curSpeed,
               ITP_PeriodToSpeedUnit(joggingPar.curSpeed), ITP_PeriodToSpeedUnit(joggingPar.curSpeed)/60);
    }
    else if(joggingPar.motionMode == Jogging::PAR_REORIENT)
    {
        qDebug("<Button_%d pressed> speed: %.4lf", id, joggingPar.curSpeed);
    }
    /* ********************************** Debug ********************************** */
}


// 机器人不动
void RobManual::robotStanding(int id)
{
    if(SW_Increment == SW_OFF)
    {
        pInputData->jogMoveVal = 0.0;
        pInputData->robotMove[id/2] = 0;
        pInputData->moveSpeed = 0;    // 设置速度
    }
    else if(SW_Increment == SW_ON)
    {
        keyLongPressListener->stop();
        // 如果松开按钮，则停止计时
        if(incrementTimer->isActive()) {incrementTimer->stop();}

        //pInputData->jogMoveVal = 0.0;
        //pInputData->robotMove[id/2] = 0;

    }

    qDebug("<Button_%d released> X:%.4lf, Y:%.4lf, Z:%.4lf", id, pOutputData->curRob.pose.trans.x,
           pOutputData->curRob.pose.trans.y, pOutputData->curRob.pose.trans.z);
}

void RobManual::keyLongPressListenerRespond()
{
    //keyLongPressListener->stop();   // 本来就是 SingleShot 模式，不用 stop 也行;
    incrementTimer->start(100);     // 启动增量模式下的持续运动
}

void RobManual::incrementTimerRespond()
{
    // 机器人持续移动（速率为每秒10步），这里规定当机器人正在运动的时候修改速度倍率和增量大小无效
    pInputData->flagIncUpdate = !(pInputData->flagIncUpdate);   // 更新增量标识
}


/*
 * @brief 属性更改
 *
 * @param 行号row，列号column
 *
 * @return 返回void
 */
void RobManual::changeProperties(int row, int column)
{
    switch(row)
    {
    case 0:
        {   //QMessageBox::information(this, tr("Information"), tr("Hello Testing (%1, %2)").arg(row+1).arg(column+1));
            settingWidget->currSubWidget = Jogging::MECHANICAL_UNIT;
        }
        break;
    case 1:
        {
            settingWidget->currSubWidget = Jogging::ABSOLUTE_ACCURACY;
        }
        break;
    case 2:
        {
            settingWidget->currSubWidget = Jogging::MOTION_MODE;
        }
        break;
    case 3:
        {
            settingWidget->currSubWidget = Jogging::COORDINATE_SYSTEM;
        }
        break;
    case 4:
        {
            settingWidget->currSubWidget = Jogging::TOOL;
        }
        break;
    case 5:
        {
            settingWidget->currSubWidget = Jogging::WORK_OBJECT;
        }
        break;
    case 6:
        {
            settingWidget->currSubWidget = Jogging::PAY_LOAD;
        }
        break;
    case 7:
        {
            settingWidget->currSubWidget = Jogging::JOYSTICK_LOCK;
        }
        break;
    case 8:
        {
            settingWidget->currSubWidget = Jogging::INCREMENT;
        }
        break;
    default:break;
    }
    settingWidget->setCurrentWidget(settingWidget->currSubWidget);
    settingWidget->show();
}

void RobManual::poseFormatBtnClicked()
{
    settingWidget->currSubWidget = Jogging::POSITION_FORMAT;
    settingWidget->setCurrentWidget(settingWidget->currSubWidget);
    settingWidget->show();
}

void RobManual::alignBtnClicked()
{
    settingWidget->currSubWidget = Jogging::ALIGN;
    settingWidget->setCurrentWidget(settingWidget->currSubWidget);
    settingWidget->show();
}

void RobManual::gotoBtnClicked()
{
    settingWidget->currSubWidget = Jogging::GO_TO;
    settingWidget->setCurrentWidget(settingWidget->currSubWidget);
    settingWidget->show();
}

void RobManual::activateBtnClicked()
{
    settingWidget->currSubWidget = Jogging::ACTIVATE;
    settingWidget->setCurrentWidget(settingWidget->currSubWidget);
    settingWidget->show();
}

// 根据id更新属性框中的数据
void RobManual::propertyChanged(int id, QString text)
{
    switch (id) {
    case Jogging::MECHANICAL_UNIT:
    {
        ;
    }
        break;
    case Jogging::ABSOLUTE_ACCURACY:
    {
        ;
    }
        break;
    case Jogging::MOTION_MODE:
    {
        if(joggingPar.motionMode == Jogging::PAR_AXIS1_6)   // 关节操作模式下坐标系设置无效
        {
            propertyTabCooKeyItem->setFlags(propertyTabCooKeyItem->flags() & ~(Qt::ItemIsEnabled));
            propertyTabCooValItem->setFlags(propertyTabCooValItem->flags() & ~(Qt::ItemIsEnabled));
        }else{
            propertyTabCooKeyItem->setFlags(propertyTabCooKeyItem->flags() | Qt::ItemIsEnabled);
            propertyTabCooValItem->setFlags(propertyTabCooValItem->flags() | Qt::ItemIsEnabled);
        }
        propertyTabMotValItem->setText(text);
        this->updatePositionTable();    // 刷新【位置】框
        this->changeDirectionBtnBox();  // 刷新【方向操纵键】框
    }
        break;
    case Jogging::COORDINATE_SYSTEM:
    {
        propertyTabCooValItem->setText(text);
    }
        break;
    case Jogging::TOOL:
    {
        ;
    }
        break;
    case Jogging::WORK_OBJECT:
    {
        ;
    }
        break;
    case Jogging::PAY_LOAD:
    {
        ;
    }
        break;
    case Jogging::JOYSTICK_LOCK:
    {
        ;
    }
        break;
    case Jogging::INCREMENT:
    {
        propertyTabIncValItem->setText(text);
    }
        break;
    default:
        break;
    }
}
