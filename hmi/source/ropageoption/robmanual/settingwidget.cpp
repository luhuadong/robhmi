#include "header/ropageoption/robmanual/settingwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QSize>
#include <QPixmap>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <QSignalMapper>
#include <QTableView>
#include <qtableview.h>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QAbstractItemView>

#include "decode_datatype.h"
#include "decode_typestructs.h"
#include "robotdecodepublic.h"
#include "robotprgfilestruct.h"


QString toolBtnCheckedStyleSheet("border-style: solid; background-color: LightGray;");
QString toolBtnUncheckedStyleSheet("border-style: solid; background-color: transparent;");

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent)
{
    mainStackedLayout = new QStackedLayout;

    decodeTaskInit();
    readRobotPrgFile(0, "D:/workspace/Qt_Project/GSK_Robot/robhmi_1/robhmi/hmi/bin/example/example.pgf");

    mechanicalUnitWidget = new ManualSubTemplateWidget(this);
    absoluteAccuracyWidget = new ManualSubTemplateWidget;
    MotionModeWidget = new ManualSubTemplateWidget;
    CoordinateSystemWidget = new ManualSubTemplateWidget;
    ToolWidget = new ManualTableWidget(Jogging::TOOL, this);
    WorkObjectWidget = new ManualTableWidget(Jogging::WORK_OBJECT, this);
    PayloadWidget = new ManualTableWidget(Jogging::PAY_LOAD, this);
    JoystickLockWidget = new ManualSubTemplateWidget;
    IncrementWidget = new ManualSubTemplateWidget;
    PositionFormatWidget = new ManualSubTemplateWidget;
    AlignWidget = new ManualSubTemplateWidget;
    //GoToWidget = new ManualSubTemplateWidget;
    GoToWidget = new GoToPosTemplateWidget;
    ActivateWidget = new ManualSubTemplateWidget;

    mainStackedLayout->addWidget(mechanicalUnitWidget);
    mainStackedLayout->setCurrentWidget(mechanicalUnitWidget);
    currSubWidget = Jogging::MECHANICAL_UNIT;
    mainStackedLayout->addWidget(absoluteAccuracyWidget);
    mainStackedLayout->addWidget(MotionModeWidget);
    mainStackedLayout->addWidget(CoordinateSystemWidget);
    mainStackedLayout->addWidget(ToolWidget);
    mainStackedLayout->addWidget(WorkObjectWidget);
    mainStackedLayout->addWidget(PayloadWidget);
    mainStackedLayout->addWidget(JoystickLockWidget);
    mainStackedLayout->addWidget(IncrementWidget);
    mainStackedLayout->addWidget(PositionFormatWidget);
    mainStackedLayout->addWidget(AlignWidget);
    mainStackedLayout->addWidget(GoToWidget);
    mainStackedLayout->addWidget(ActivateWidget);

    cancelSignalMapper = new QSignalMapper(this);   // 取消按钮的信号集合
    okSignalMapper = new QSignalMapper(this);       // 确定按钮的信号集合

    this->initMechanicalUnitWidget();
    this->initAbsoluteAccuracyWidget();
    this->initMotionModeWidget();
    this->initCoordinateSystemWidget();
    this->initToolWidget();
    this->initWorkObjectWidget();
    this->initPayloadWidget();
    this->initJoystickLockWidget();
    this->initIncrementWidget();
    this->initPositionFormatWidget();
    this->initAlignWidget();
    this->initGoToWidget();
    this->initActivateWidget();

    connect(cancelSignalMapper, SIGNAL(mapped(int)), this, SLOT(cancelBtnRespond(int)));
    connect(okSignalMapper, SIGNAL(mapped(int)), this, SLOT(okBtnRespond(int)));
    //connect(this, SIGNAL(initPropertyData(int)), this, SLOT(okBtnRespond(int)));

    this->setLayout(mainStackedLayout);

    // 更新属性表中的数据（好像没起作用耶）
//    for(int i=0; i<9; i++)
//    {
//        emit initPropertyData(i);
//    }
}

void SettingWidget::setCurrentWidget(Jogging::MANUALSUBWIDGET ManualSubWidget)
{
    switch (ManualSubWidget)
    {
    // 属性更改界面
    case Jogging::MECHANICAL_UNIT:
        mainStackedLayout->setCurrentWidget(mechanicalUnitWidget);
        break;
    case Jogging::ABSOLUTE_ACCURACY:
        mainStackedLayout->setCurrentWidget(absoluteAccuracyWidget);
        break;
    case Jogging::MOTION_MODE:
        mainStackedLayout->setCurrentWidget(MotionModeWidget);
        break;
    case Jogging::COORDINATE_SYSTEM:
        mainStackedLayout->setCurrentWidget(CoordinateSystemWidget);
        break;
    case Jogging::TOOL:
        mainStackedLayout->setCurrentWidget(ToolWidget);
        break;
    case Jogging::WORK_OBJECT:
        mainStackedLayout->setCurrentWidget(WorkObjectWidget);
        break;
    case Jogging::PAY_LOAD:
        mainStackedLayout->setCurrentWidget(PayloadWidget);
        break;
    case Jogging::JOYSTICK_LOCK:
        mainStackedLayout->setCurrentWidget(JoystickLockWidget);
        break;
    case Jogging::INCREMENT:
        mainStackedLayout->setCurrentWidget(IncrementWidget);
        break;
    // 位置格式更改界面
    case Jogging::POSITION_FORMAT:
        mainStackedLayout->setCurrentWidget(PositionFormatWidget);
        break;
    // button栏操作界面
    case Jogging::ALIGN:
        mainStackedLayout->setCurrentWidget(AlignWidget);
        break;
    case Jogging::GO_TO:
        mainStackedLayout->setCurrentWidget(GoToWidget);
        break;
    case Jogging::ACTIVATE:
        mainStackedLayout->setCurrentWidget(ActivateWidget);
        break;
    default:
        break;
    }
}

/* ************************* 子界面初始化开始 *************************** */

/*
 * @brief 【机械单元】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initMechanicalUnitWidget()
{
    mechanicalUnitWidget->setTipsText(propertyTipsStrList.at(Jogging::MECHANICAL_UNIT));

    QStringList tableHeaderLabelList;
    tableHeaderLabelList << tr("机械单元") << tr("状态");
    QTableWidget *MechanicalUnitTabWidget = new QTableWidget(1, 2);
    MechanicalUnitTabWidget->verticalHeader()->hide();
    MechanicalUnitTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择一行
    MechanicalUnitTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);  // 单选
    MechanicalUnitTabWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    // 不可编辑
    MechanicalUnitTabWidget->setFont(QFont("Times", 8));
    MechanicalUnitTabWidget->setHorizontalHeaderLabels(tableHeaderLabelList);
    MechanicalUnitTabWidget->setColumnWidth(0, 330);
    MechanicalUnitTabWidget->setColumnWidth(1, 330);
    MechanicalUnitTabWidget->setRowHeight(0, 50);

    QPixmap robPixmap(":/images/bin/resource/images/Jogging_Mechanical_Unit_Robot.png");
    QTableWidgetItem *rob1Item = new QTableWidgetItem(QIcon(robPixmap), tr("ROB_1"));
    MechanicalUnitTabWidget->setItem(0, 0, rob1Item);
    MechanicalUnitTabWidget->setItem(0, 1, new QTableWidgetItem(tr("已启动")));


    //QLabel *label = new QLabel(tr("【机械单元】"));
    //label->setAlignment(Qt::AlignCenter);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(MechanicalUnitTabWidget);
    mechanicalUnitWidget->setContentWidgetLayout(mainLayout);

    // mapped signals of cancel and ok button
    connect(mechanicalUnitWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(mechanicalUnitWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(mechanicalUnitWidget, Jogging::MECHANICAL_UNIT);
    okSignalMapper->setMapping(mechanicalUnitWidget, Jogging::MECHANICAL_UNIT);
}

/*
 * @brief 【绝对精度】界面的初始化函数（预留）
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initAbsoluteAccuracyWidget()
{
    absoluteAccuracyWidget->setTipsText(propertyTipsStrList.at(Jogging::ABSOLUTE_ACCURACY));

    QLabel *label = new QLabel(tr("【绝对精度】"));
    label->setAlignment(Qt::AlignCenter);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(label);
    absoluteAccuracyWidget->setContentWidgetLayout(mainLayout);
}

/*
 * @brief 【动作模式】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initMotionModeWidget()
{
    MotionModeWidget->setTipsText(propertyTipsStrList.at(Jogging::MOTION_MODE));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(60);
    mainLayout->addStretch();

    QSize size(70, 70); // iconSize

    QStringList iconStringList, textStringList;
    iconStringList<<"Axis"<<"Linear"<<"Reorient";
    textStringList<<tr("轴 1 - 6")<<tr("线性")<<tr("重定位");
    QSignalMapper *signalMapper = new QSignalMapper;    // bundles signals from identifiable senders.

    for(int i=0; i<iconStringList.size(); i++)
    {
        QToolButton *toolBtn = new QToolButton;
        MotionModeWidget->toolBtnList.append(toolBtn);  // 存放动作模式的选项按钮
        toolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QPixmap pixmap(QString(":/images/bin/resource/images/Jogging_Motion_Mode_%1.png").arg(iconStringList.at(i)));
        toolBtn->setIcon(pixmap);   // 为按钮设置图标
        toolBtn->setIconSize(size);
        toolBtn->setFixedSize(size.width()+30, size.height()+30);
        toolBtn->setText(textStringList.at(i)); // 设置提示文字
        toolBtn->setCheckable(true);
        toolBtn->setStyleSheet(toolBtnUncheckedStyleSheet); // 所有按钮初始状态为unchecked

        connect(toolBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(toolBtn, (Jogging::PAR_AXIS1_6)+i);

        mainLayout->addWidget(toolBtn);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(motionModeToolBtnClicked(int)));

    mainLayout->addStretch();
    MotionModeWidget->setContentWidgetLayout(mainLayout);

    // 设置初选项
    setThisToolBtnchecked(MotionModeWidget, MotionModeWidget->toolBtnList, joggingPar.motionMode);

    // mapped signals of cancel and ok button
    connect(MotionModeWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(MotionModeWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(MotionModeWidget, Jogging::MOTION_MODE);
    okSignalMapper->setMapping(MotionModeWidget, Jogging::MOTION_MODE);
}

/*
 * @brief 【动作模式】界面的ToolButton点击事件处理
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::motionModeToolBtnClicked(int id)
{
    switch (id) {
    case Jogging::PAR_AXIS1_6:
    {
        setAllToolBtnUnchecked(MotionModeWidget->toolBtnList);
        setThisToolBtnchecked(MotionModeWidget, MotionModeWidget->toolBtnList, Jogging::PAR_AXIS1_6);
    }
        break;
    case Jogging::PAR_LINEAR:
    {
        setAllToolBtnUnchecked(MotionModeWidget->toolBtnList);
        setThisToolBtnchecked(MotionModeWidget, MotionModeWidget->toolBtnList, Jogging::PAR_LINEAR);
    }
        break;
    case Jogging::PAR_REORIENT:
    {
        setAllToolBtnUnchecked(MotionModeWidget->toolBtnList);
        setThisToolBtnchecked(MotionModeWidget, MotionModeWidget->toolBtnList, Jogging::PAR_REORIENT);
    }
        break;
    default:
        break;
    }
}

/*
 * @brief 【坐标系】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initCoordinateSystemWidget()
{
    CoordinateSystemWidget->setTipsText(propertyTipsStrList.at(Jogging::COORDINATE_SYSTEM));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(30);
    mainLayout->addStretch();

    QSize size(61, 61);

    QStringList iconStringList, textStringList;
    iconStringList<<"World"<<"Base"<<"Tool"<<"WorkObject";
    textStringList<<tr("大地坐标")<<tr("基坐标")<<tr("工具坐标")<<tr("工件坐标");
    QSignalMapper *signalMapper = new QSignalMapper;    // bundles signals from identifiable senders.

    for(int i=0; i<iconStringList.size(); i++)
    {
        QToolButton *toolBtn = new QToolButton;
        CoordinateSystemWidget->toolBtnList.append(toolBtn);  // 存放动作模式的选项按钮
        toolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QPixmap pixmap(QString(":/images/bin/resource/images/Coordinate_%1.png").arg(iconStringList.at(i)));
        toolBtn->setIcon(pixmap);   // 为按钮设置图标
        toolBtn->setIconSize(pixmap.size());
        toolBtn->setFixedSize(size.width()+30, size.height()+30);
        toolBtn->setText(textStringList.at(i)); // 设置提示文字
        toolBtn->setCheckable(true);
        toolBtn->setStyleSheet(toolBtnUncheckedStyleSheet); // 所有按钮初始状态为unchecked

        connect(toolBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(toolBtn, (Jogging::PAR_WORLD)+i);

        mainLayout->addWidget(toolBtn);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(coordinateSystemToolBtnClicked(int)));

    mainLayout->addStretch();
    CoordinateSystemWidget->setContentWidgetLayout(mainLayout);

    // 设置初选项
    setThisToolBtnchecked(CoordinateSystemWidget, CoordinateSystemWidget->toolBtnList, joggingPar.coordinateSystem);

    // mapped signals of cancel and ok button
    connect(CoordinateSystemWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(CoordinateSystemWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(CoordinateSystemWidget, Jogging::COORDINATE_SYSTEM);
    okSignalMapper->setMapping(CoordinateSystemWidget, Jogging::COORDINATE_SYSTEM);
}

/*
 * @brief 【坐标系】界面的ToolButton点击事件处理
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::coordinateSystemToolBtnClicked(int id)
{
    switch (id) {
    case Jogging::PAR_WORLD:
    {
        setAllToolBtnUnchecked(CoordinateSystemWidget->toolBtnList);
        setThisToolBtnchecked(CoordinateSystemWidget, CoordinateSystemWidget->toolBtnList, Jogging::PAR_WORLD);
    }
        break;
    case Jogging::PAR_BASE:
    {
        setAllToolBtnUnchecked(CoordinateSystemWidget->toolBtnList);
        setThisToolBtnchecked(CoordinateSystemWidget, CoordinateSystemWidget->toolBtnList, Jogging::PAR_BASE);

    }
        break;
    case Jogging::PAR_TOOL:
    {
        setAllToolBtnUnchecked(CoordinateSystemWidget->toolBtnList);
        setThisToolBtnchecked(CoordinateSystemWidget, CoordinateSystemWidget->toolBtnList, Jogging::PAR_TOOL);
    }
        break;
    case Jogging::PAR_WORKOBJECT:
    {
        setAllToolBtnUnchecked(CoordinateSystemWidget->toolBtnList);
        setThisToolBtnchecked(CoordinateSystemWidget, CoordinateSystemWidget->toolBtnList, Jogging::PAR_WORKOBJECT);
    }
        break;
    default:
        break;
    }
}

/*
 * @brief 【工具坐标】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initToolWidget()
{
    // mapped signals of cancel and ok button
    connect(ToolWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(ToolWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(ToolWidget, Jogging::TOOL);
    okSignalMapper->setMapping(ToolWidget, Jogging::TOOL);
}

/*
 * @brief 【工件坐标】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initWorkObjectWidget()
{
    // mapped signals of cancel and ok button
    connect(WorkObjectWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(WorkObjectWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(WorkObjectWidget, Jogging::WORK_OBJECT);
    okSignalMapper->setMapping(WorkObjectWidget, Jogging::WORK_OBJECT);
}

/*
 * @brief 【有效载荷】界面的初始化函数（预留）
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initPayloadWidget()
{
    connect(PayloadWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(PayloadWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(PayloadWidget, Jogging::PAY_LOAD);
    okSignalMapper->setMapping(PayloadWidget, Jogging::PAY_LOAD);
}

/*
 * @brief 【操纵杆锁定】界面的初始化函数（预留）
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initJoystickLockWidget()
{
    JoystickLockWidget->setTipsText(propertyTipsStrList.at(Jogging::JOYSTICK_LOCK));

    QLabel *label = new QLabel(tr("【操纵杆锁定】"));
    label->setAlignment(Qt::AlignCenter);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(label);
    JoystickLockWidget->setContentWidgetLayout(mainLayout);
}

/*
 * @brief 【增量】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initIncrementWidget()
{
    IncrementWidget->setTipsText(propertyTipsStrList.at(Jogging::INCREMENT));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(20);
    mainLayout->addStretch();

    QSize size(61, 61);

    QStringList iconStringList, textStringList;
    iconStringList<<"None"<<"Small"<<"Medium"<<"Large"<<"User";
    textStringList<<tr("无")<<tr("小")<<tr("中")<<tr("大")<<tr("用户");
    QSignalMapper *signalMapper = new QSignalMapper;    // bundles signals from identifiable senders.

    for(int i=0; i<iconStringList.size(); i++)
    {
        QToolButton *toolBtn = new QToolButton;
        IncrementWidget->toolBtnList.append(toolBtn);  // 存放动作模式的选项按钮
        toolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        QPixmap pixmap(QString(":/images/bin/resource/images/Increment_%1.png").arg(iconStringList.at(i)));
        toolBtn->setIcon(pixmap);   // 为按钮设置图标
        toolBtn->setIconSize(pixmap.size());
        toolBtn->setFixedSize(size.width()+30, size.height()+30);
        toolBtn->setText(textStringList.at(i)); // 设置提示文字
        toolBtn->setCheckable(true);
        toolBtn->setStyleSheet(toolBtnUncheckedStyleSheet); // 所有按钮初始状态为unchecked

        connect(toolBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(toolBtn, (Jogging::PAR_NONE)+i);

        mainLayout->addWidget(toolBtn);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(incrementToolBtnClicked(int)));

    mainLayout->addStretch();
    IncrementWidget->setContentWidgetLayout(mainLayout);

    // 设置初选项
    setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, joggingPar.increment);

    // mapped signals of cancel and ok button
    connect(IncrementWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(IncrementWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(IncrementWidget, Jogging::INCREMENT);
    okSignalMapper->setMapping(IncrementWidget, Jogging::INCREMENT);
}

/*
 * @brief 【增量】界面的ToolButton点击事件处理
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::incrementToolBtnClicked(int id)
{
    switch (id) {
    case Jogging::PAR_NONE:
    {
        setAllToolBtnUnchecked(IncrementWidget->toolBtnList);
        setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, Jogging::PAR_NONE);
    }
        break;
    case Jogging::PAR_SMALL:
    {
        setAllToolBtnUnchecked(IncrementWidget->toolBtnList);
        setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, Jogging::PAR_SMALL);
    }
        break;
    case Jogging::PAR_MEDIUM:
    {
        setAllToolBtnUnchecked(IncrementWidget->toolBtnList);
        setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, Jogging::PAR_MEDIUM);
    }
        break;
    case Jogging::PAR_LARGE:
    {
        setAllToolBtnUnchecked(IncrementWidget->toolBtnList);
        setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, Jogging::PAR_LARGE);
    }
        break;
    case Jogging::PAR_USER:
    {
        setAllToolBtnUnchecked(IncrementWidget->toolBtnList);
        setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, Jogging::PAR_USER);
    }
        break;
    default:
        break;
    }
}


/*
 * @brief 【位置格式】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initPositionFormatWidget()
{
    QString tips(tr("【位置格式】"));
    PositionFormatWidget->setTipsText(tips);

    QLabel *positionShownInLabel = new QLabel(tr("位置显示方式："));
    positionShownInComboBox = new QComboBox;
    positionShownInComboBox->addItem(tr("大地坐标"));
    positionShownInComboBox->addItem(tr("基坐标"));
    positionShownInComboBox->addItem(tr("工件坐标"));

    QLabel *orientationFormatLabel = new QLabel(tr("方向格式："));
    orientationFormatComboBox = new QComboBox;
    orientationFormatComboBox->addItem(tr("四元组"));
    orientationFormatComboBox->addItem(tr("欧拉角"));

    QLabel *angleFormatLabel = new QLabel(tr("角度格式："));
    angleFormatComboBox = new QComboBox;
    angleFormatComboBox->addItem(tr("角度"));

    QLabel *angleUnitLabel = new QLabel(tr("角度单位："));
    angleUnitComboBox = new QComboBox;
    angleUnitComboBox->addItem(tr("度数"));
    angleUnitComboBox->addItem(tr("弧度"));

    QGridLayout *contentLayout = new QGridLayout;
    contentLayout->addWidget(positionShownInLabel, 0, 0);
    contentLayout->addWidget(positionShownInComboBox, 0, 1);
    contentLayout->addWidget(orientationFormatLabel, 1, 0);
    contentLayout->addWidget(orientationFormatComboBox, 1, 1);
    contentLayout->addWidget(angleFormatLabel, 2, 0);
    contentLayout->addWidget(angleFormatComboBox, 2, 1);
    contentLayout->addWidget(angleUnitLabel, 3, 0);
    contentLayout->addWidget(angleUnitComboBox, 3, 1);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch();
    PositionFormatWidget->setContentWidgetLayout(mainLayout);

    // 为ComboBox设置初选项
    positionShownInComboBox->setCurrentIndex(Jogging::PAR_SHOW_BASE);
    orientationFormatComboBox->setCurrentIndex(Jogging::PAR_SHOW_QUATERNION);
    angleUnitComboBox->setCurrentIndex(Jogging::PAR_SHOW_DEGREES);


    // mapped signals of cancel and ok button
    connect(PositionFormatWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(PositionFormatWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(PositionFormatWidget, Jogging::POSITION_FORMAT);
    okSignalMapper->setMapping(PositionFormatWidget, Jogging::POSITION_FORMAT);
}

QString SettingWidget::getPositionShownInWhichCoord()
{
    return positionShownInComboBox->currentText();
}

/*
 * @brief 【对准】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initAlignWidget()
{
    AlignWidget->setCurrentKeyText((tr("当前工具：\t")));
    AlignWidget->setCurrentValText(tr(""));
    AlignWidget->setTipsText(tr(""));

    QLabel *alignStep1Label = new QLabel(tr("1、选择与当前选定工具对准的坐标系："));
    QLabel *alignCoordinateLabel = new QLabel(tr("坐标："));
    QComboBox *alignCoordinateComboBox = new QComboBox;
    alignCoordinateComboBox->addItem(tr("大地坐标"));
    alignCoordinateComboBox->addItem(tr("基坐标"));
    alignCoordinateComboBox->addItem(tr("工件坐标"));
    QLabel *alignStep2Label = new QLabel(tr("2、按住使动装置，然后点按“开始对准”。"));
    QPushButton *alignStartBtn = new QPushButton(tr("开始对准"));
    QLabel *alignStep3Label = new QLabel(tr("3、就绪时点击“关闭”。"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setMargin(60);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(alignStep1Label, 0, 0, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(alignCoordinateLabel, 1, 0, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(alignCoordinateComboBox, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(alignStep2Label, 2, 0, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(alignStartBtn, 3, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(alignStep3Label, 4, 0, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    AlignWidget->setContentWidgetLayout(mainLayout);

    // mapped signals of cancel and ok button
    connect(AlignWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(AlignWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(AlignWidget, Jogging::ALIGN);
    okSignalMapper->setMapping(AlignWidget, Jogging::ALIGN);
}

/*
 * @brief 【转到】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initGoToWidget()
{
//    QLabel *label = new QLabel(tr("【转到】"));
//    label->setAlignment(Qt::AlignCenter);
//    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(label);
//    GoToWidget->setContentWidgetLayout(mainLayout);

    // mapped signals of cancel and ok button
    connect(GoToWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    //connect(GoToWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(GoToWidget, Jogging::GO_TO);
    //okSignalMapper->setMapping(GoToWidget, Jogging::GO_TO);
}

/*
 * @brief 【启动】界面的初始化函数
 *
 * @param 无
 *
 * @return void
 */
void SettingWidget::initActivateWidget()
{
    QLabel *label = new QLabel(tr("【启动】"));
    label->setAlignment(Qt::AlignCenter);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(label);
    ActivateWidget->setContentWidgetLayout(mainLayout);

    // mapped signals of cancel and ok button
    connect(ActivateWidget, SIGNAL(cancelBtnClicked()), cancelSignalMapper, SLOT(map()));
    connect(ActivateWidget, SIGNAL(okBtnClicked()), okSignalMapper, SLOT(map()));
    cancelSignalMapper->setMapping(ActivateWidget, Jogging::ACTIVATE);
    okSignalMapper->setMapping(ActivateWidget, Jogging::ACTIVATE);
}


/*
 * @brief 将toolBtnList中的所有QToolButton设置为unchecked状态
 *
 * @param toolBtnList: QToolButton列表集合
 *
 * @return void
 */
void SettingWidget::setAllToolBtnUnchecked(QList<QToolButton *> toolBtnList)
{
    for(int i=0; i<toolBtnList.size(); i++)
    {
        toolBtnList.at(i)->setChecked(false);
        toolBtnList.at(i)->setStyleSheet(toolBtnUncheckedStyleSheet);
    }
}

/*
 * @brief 将toolBtnList中对应id的QToolButton设置为checked状态
 *
 * @param currentPage: 当前页面
 *        toolBtnList: QToolButton列表集合
 *        id: 按钮id
 *
 * @return void
 */
void SettingWidget::setThisToolBtnchecked(ManualSubTemplateWidget *currentPage, QList<QToolButton *> toolBtnList, int id)
{
    toolBtnList.at(id)->setChecked(true);
    toolBtnList.at(id)->setStyleSheet(toolBtnCheckedStyleSheet);
    currentPage->setCurrentValText(toolBtnList.at(id)->text());
}

void SettingWidget::cancelBtnRespond(int id)
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
        setAllToolBtnUnchecked(MotionModeWidget->toolBtnList);
        setThisToolBtnchecked(MotionModeWidget, MotionModeWidget->toolBtnList, joggingPar.motionMode);
    }
        break;
    case Jogging::COORDINATE_SYSTEM:
    {
        setAllToolBtnUnchecked(CoordinateSystemWidget->toolBtnList);
        setThisToolBtnchecked(CoordinateSystemWidget, CoordinateSystemWidget->toolBtnList, joggingPar.coordinateSystem);
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
        setAllToolBtnUnchecked(IncrementWidget->toolBtnList);
        setThisToolBtnchecked(IncrementWidget, IncrementWidget->toolBtnList, joggingPar.increment);
    }
        break;
    default:
        break;
    }

    this->hide();
}

void SettingWidget::okBtnRespond(int id)
{
    QString text(tr("Error..."));   // 如果text设置错误将显示"Error..."

    switch (id) {
    case Jogging::MECHANICAL_UNIT:
    {
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::ABSOLUTE_ACCURACY:
    {
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::MOTION_MODE:
    {
        for(int i=0; i<MotionModeWidget->toolBtnList.size(); i++)
        {
            if(MotionModeWidget->toolBtnList.at(i)->isChecked())
            {
                joggingPar.motionMode = (Jogging::TypeMotionMode)i;
                if(Jogging::PAR_AXIS1_6 == i) {pInputData->mode = ITP_Mode_JointOp_SpeedAndIncMode;}  // 关节模式
                else if(Jogging::PAR_LINEAR == i) {pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;} // 坐标模式
                else if(Jogging::PAR_REORIENT == i) {pInputData->mode = ITP_Mode_CoordinateOp_SpeedAndIncMode;}    // 也是坐标模式
                text = MotionModeWidget->toolBtnList.at(i)->text(); // 获取当前选定的按钮的text
                break;
            }
        }
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::COORDINATE_SYSTEM:
    {
        for(int i=0; i<CoordinateSystemWidget->toolBtnList.size(); i++)
        {
            if(CoordinateSystemWidget->toolBtnList.at(i)->isChecked())
            {
                joggingPar.coordinateSystem = (Jogging::TypeCoordinateSystem)i;
                if(Jogging::PAR_WORLD == i) {pInputData->flagCoordinate = -1;}  // 未定义
                else if(Jogging::PAR_BASE == i) {pInputData->flagCoordinate = 0;}   // 0表示基坐标系
                else if(Jogging::PAR_TOOL == i) {pInputData->flagCoordinate = 1;}   // 1表示工具坐标系
                else if(Jogging::PAR_WORKOBJECT == i) {pInputData->flagCoordinate = 2;} // 2表示用户自定义坐标系(基准坐标系为基坐标系)
                text = CoordinateSystemWidget->toolBtnList.at(i)->text();
                break;
            }
        }
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::TOOL:
    {
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::WORK_OBJECT:
    {
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::PAY_LOAD:
    {
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::JOYSTICK_LOCK:
    {
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::INCREMENT:
    {
        for(int i=0; i<IncrementWidget->toolBtnList.size(); i++)
        {
            if(IncrementWidget->toolBtnList.at(i)->isChecked())
            {
                joggingPar.increment = (Jogging::TypeIncrement)i;   // 记录当前选了哪个
                if(Jogging::PAR_NONE == i) {SW_Increment = SW_OFF;} // 关闭或打开增量开关
                else {SW_Increment = SW_ON;}
                text = IncrementWidget->toolBtnList.at(i)->text();
                break;
            }
        }
        emit propertyChanged(id, text); // 通知父窗体属性框中有更新
    }
        break;
    case Jogging::POSITION_FORMAT:
    {
        positionFmt.coordinateSys = (Jogging::TypePositionCoo)positionShownInComboBox->currentIndex();
        positionFmt.orientationFmt = (Jogging::TypePositionOri)orientationFormatComboBox->currentIndex();
        positionFmt.angleUnit = (Jogging::TypePositionAnU)angleUnitComboBox->currentIndex();
        emit positionChanged(); // 通知父窗体位置框中有更新
    }
        break;
    default:
        break;
    }


    this->hide();   // 关闭子窗口
}


//// 新建
//void SettingWidget::newBtnRespond()
//{
//    NewDataTemplateWidget *newDataUI;

//    if(currSubWidget == Jogging::TOOL)
//    {
//        newDataUI = new NewDataTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tooldata0")), ToolWidget);
//    }
//    else if(currSubWidget == Jogging::WORK_OBJECT)
//    {
//        newDataUI = new NewDataTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobjdata0")), WorkObjectWidget);
//    }
//    else if(currSubWidget == Jogging::PAY_LOAD)
//    {
//        newDataUI = new NewDataTemplateWidget(ProgramData::LOAD_DATA, QString(tr("loaddata0")), PayloadWidget);
//    }

//    newDataUI->setAttribute(Qt::WA_DeleteOnClose);
//    newDataUI->show();
//    connect(newDataUI, SIGNAL(okBtnClicked()), newDataUI, SLOT(close()));
//    connect(newDataUI, SIGNAL(cancelBtnClicked()), newDataUI, SLOT(close()));

//}

//// 更改值
//void SettingWidget::modValActionRespond()
//{
//    DataEditTemplateWidget *modValUI;

//    if(currSubWidget == Jogging::TOOL)
//    {
//        modValUI = new DataEditTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tool_x")), ToolWidget);
//    }
//    else if(currSubWidget == Jogging::WORK_OBJECT)
//    {
//        modValUI = new DataEditTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobj_x")), WorkObjectWidget);
//    }
//    else if(currSubWidget == Jogging::PAY_LOAD)
//    {
//        modValUI = new DataEditTemplateWidget(ProgramData::LOAD_DATA, QString(tr("load_x")), PayloadWidget);
//    }

//    modValUI->setAttribute(Qt::WA_DeleteOnClose);
//    modValUI->show();
//    connect(modValUI, SIGNAL(okBtnClicked()), modValUI, SLOT(close()));
//    connect(modValUI, SIGNAL(cancelBtnClicked()), modValUI, SLOT(close()));
//}

//// 更改声明
//void SettingWidget::modDecActionRespond()
//{
//    NewDataTemplateWidget *newDataUI;

//    if(currSubWidget == Jogging::TOOL)
//    {
//        newDataUI = new NewDataTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tooldata0")), ToolWidget);
//    }
//    else if(currSubWidget == Jogging::WORK_OBJECT)
//    {
//        newDataUI = new NewDataTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobjdata0")), WorkObjectWidget);
//    }
//    else if(currSubWidget == Jogging::PAY_LOAD)
//    {
//        newDataUI = new NewDataTemplateWidget(ProgramData::LOAD_DATA, QString(tr("loaddata0")), PayloadWidget);
//    }

//    newDataUI->setAttribute(Qt::WA_DeleteOnClose);
//    newDataUI->show();
//    connect(newDataUI, SIGNAL(okBtnClicked()), newDataUI, SLOT(close()));
//    connect(newDataUI, SIGNAL(cancelBtnClicked()), newDataUI, SLOT(close()));
//}

//// 复制
//void SettingWidget::copyActionRespond()
//{

//}

//// 删除
//void SettingWidget::deleteActionRespond()
//{
//    WarningDialogTemplateWidget *warningUI;
//    warningUI = new WarningDialogTemplateWidget(QString(tr("确定删除“tool_x”？\n此操作不可撤销。")), ToolWidget);
//    warningUI->setAttribute(Qt::WA_DeleteOnClose);
//    warningUI->setGeometry(geometry().x()+(width()-warningUI->width())/2,
//                           geometry().y()+(height()-warningUI->height())/2,
//                           warningUI->width(), warningUI->height());
//    warningUI->show();

//    connect(warningUI, SIGNAL(yesBtnClicked()), warningUI, SLOT(close()));
//    connect(warningUI, SIGNAL(noBtnClicked()), warningUI, SLOT(close()));
//}

//// 定义
//void SettingWidget::defineActionRespond()
//{
//    DataDefineTemplateWidget *dataDefineUI;

//    if(currSubWidget == Jogging::TOOL)
//    {
//        dataDefineUI = new DataDefineTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tooldata0")), ToolWidget);
//    }
//    else if(currSubWidget == Jogging::WORK_OBJECT)
//    {
//        //dataDefineUI = new DataDefineTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobjdata0")), WorkObjectWidget);
//    }

//    dataDefineUI->setAttribute(Qt::WA_DeleteOnClose);
//    dataDefineUI->show();
//    connect(dataDefineUI, SIGNAL(okBtnClicked()), dataDefineUI, SLOT(close()));
//    connect(dataDefineUI, SIGNAL(cancelBtnClicked()), dataDefineUI, SLOT(close()));
//}
