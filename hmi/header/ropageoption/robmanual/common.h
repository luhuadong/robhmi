#ifndef ROBMANUAL_COMMON_H
#define ROBMANUAL_COMMON_H

#include <QStringList>

// 包含类型ITP_InputData
#include "header/ITP_Interface.h"


#if defined(__cplusplus)
extern "C"
{
#endif

/* ************* 注意命名空间【Jogging】 ************* */
namespace Jogging {

/* 语言 */
typedef enum{
    UI_EN,
    UI_ZH
}LANGUAGE;


typedef enum{
    MECHANICAL_UNIT,
    ABSOLUTE_ACCURACY,
    MOTION_MODE,
    COORDINATE_SYSTEM,
    TOOL,
    WORK_OBJECT,
    PAY_LOAD,
    JOYSTICK_LOCK,
    INCREMENT,
    POSITION_FORMAT,
    ALIGN,
    GO_TO,
    ACTIVATE
}MANUALSUBWIDGET;


/* 机械单元参数标识 */
typedef enum{
    PAR_ROB_1
}TypeMechanicalUnit;

/* 绝对精度参数标识 */
typedef enum{
    PAR_ON,
    PAR_OFF
}TypeAbsoluteAccuracy;

/* 动作模式参数标识 */
typedef enum{
    PAR_AXIS1_6,
    PAR_LINEAR,
    PAR_REORIENT
}TypeMotionMode;

/* 坐标系参数标识 */
typedef enum{
    PAR_WORLD,
    PAR_BASE,
    PAR_TOOL,
    PAR_WORKOBJECT
}TypeCoordinateSystem;

/* 增量参数标识 */
typedef enum{
    PAR_NONE,
    PAR_SMALL,
    PAR_MEDIUM,
    PAR_LARGE,
    PAR_USER
}TypeIncrement;

typedef struct inc_Val{
    double axis;
    double linear;
    double reorient;
}Struct_IncVal;

/* 记录手动操纵中选择的参数的结构体 */
typedef struct joggingPar{
    TypeMechanicalUnit mechanicalUnit;
    TypeAbsoluteAccuracy absoluteAccuracy;
    TypeMotionMode motionMode;
    TypeCoordinateSystem coordinateSystem;
    TypeIncrement increment;
    double maxSpeed;    // 手动操作的最大速度（单位mm/min）
    double curSpeed;    // 手动操作的当前速度（已转换）
}TypeJoggingPar;


/* 位置显示方式（Position shown in） */
typedef enum{
    PAR_SHOW_WORLD,
    PAR_SHOW_BASE,
    PAR_SHOW_WORKOBJECT
}TypePositionCoo;

/* 方向格式（Orientation format） */
typedef enum{
    PAR_SHOW_QUATERNION,
    PAR_SHOW_EULERANGLES
}TypePositionOri;

/* 角度单位（Angle unit） */
typedef enum{
    PAR_SHOW_DEGREES,
    PAR_SHOW_RADIANS
}TypePositionAnU;

/* 位置格式结构体，用于保存【位置格式】界面操作的选项 */
typedef struct positionFmt{
    TypePositionCoo coordinateSys;
    TypePositionOri orientationFmt;
    TypePositionAnU angleUnit;
}TypePositionFmt;

}   // end of namespace Jogging



#define PROPERTY_ROWS 9
#define PROPERTY_COLUMNS 2
#define POSITION_ROWS 7
#define POSITION_COLUMNS 3

#define SW_ON   0   // 开关宏定义：开
#define SW_OFF  1   // 开关宏定义：关



#ifdef JOGGING_GLOBALS
#define JOGGING_EXT
#else
#define JOGGING_EXT extern
#endif

JOGGING_EXT ITP_InputData *pInputData;		//手动操纵的参数输入（共享内存）
JOGGING_EXT ITP_OutputData *pOutputData;	//手动操纵的位置数据输出（共享内存）

JOGGING_EXT Jogging::TypeJoggingPar joggingPar;     // 用于保存【属性表】操作的选项
JOGGING_EXT Jogging::TypePositionFmt positionFmt;   // 用于保存【位置格式】界面操作的选项

/* ************* 以下是手动操纵界面中用到的全局字符串或字符串链表 ************* */
JOGGING_EXT QStringList mechanicalUnitStrList;      // 机械单元选项文字
JOGGING_EXT QStringList absoluteAccuracyStrList;    // 绝对精度选项文字
JOGGING_EXT QStringList motionModeStrList;          // 动作模式选项文字
JOGGING_EXT QStringList coordinateSystemStrList;    // 坐标系选项文字
//JOGGING_EXT QStringList toolStrList;                // 工具坐标选项文字
//JOGGING_EXT QStringList workObjectStrList;          // 工件坐标选项文字
//JOGGING_EXT QStringList payloadStrList;             // 有效载荷选项文字
//JOGGING_EXT QStringList joystickLockStrList;        // 操纵杆锁定选项文字
JOGGING_EXT QStringList incrementStrList;           // 增量选项文字
JOGGING_EXT QStringList propertyTipsStrList;        // 【属性】表中各选项的提示

JOGGING_EXT QStringList jointOpKeyStrList;          // 关节操作时在【位置】中显示的字符串（1、2、3、4、5、6）
JOGGING_EXT QStringList cooOpKeyStrList_Qua;        // 坐标操作（四元数）时在【位置】中显示的字符串（X、Y、Z、q1、q2、q3、q4）
JOGGING_EXT QStringList cooOpKeyStrList_Eul;        // 关节操作（欧拉角）时在【位置】中显示的字符串（X、Y、Z、EZ、EY、EX）
JOGGING_EXT QStringList jointOpUnitStrList_Deg;     // 关节操作（单位度）时在【位置】中显示的单位（°、...、°）
JOGGING_EXT QStringList jointOpUnitStrList_Rad;     // 关节操作（单位弧度）时在【位置】中显示的单位（rad、...、rad）
JOGGING_EXT QStringList cooOpUnitStrList_Qua;       // 坐标操作（四元数）时在【位置】中显示的单位（mm、mm、mm、无、无、无、无）
JOGGING_EXT QStringList cooOpUnitStrList_Eul_Deg;   // 坐标操作（欧拉角、单位度）时在【位置】中显示的单位（mm、mm、mm、°、°、°）
JOGGING_EXT QStringList cooOpUnitStrList_Eul_Rad;   // 坐标操作（欧拉角、单位弧度）时在【位置】中显示的单位（mm、mm、mm、rad、rad、rad）

JOGGING_EXT QStringList jointMoveBtnStrList;        // 关节操作时的按键文字（J1+/J1-/J2+/J2-/J3+/J3-/J4+/J4-/J5+/J5-/J6+/J6-）
JOGGING_EXT QStringList coordMoveBtnStrList;        // 坐标操作时的按键文字（X+/X-/Y+/Y-/Z+/Z-/A+/A-/B+/B-/C+/C-）

JOGGING_EXT int SW_Increment;   // 增量开关（0表示开，1表示关）
JOGGING_EXT Jogging::Struct_IncVal incVal[5];      // 增量选项为5，即无、小、中、大、用户

JOGGING_EXT double MaxSpeed_Joint[ITP_RobotJointNum];   // 六个关节轴的最大速度（单位：度每秒）[156 140 156 270 180 430]
JOGGING_EXT double MaxSpeed_Linear;     // 线性运动最大速度（单位：毫米每秒）1500
JOGGING_EXT double MaxSpeed_Reorient;   // 重定向最大速度（单位：毫米每秒）1200，这里设为180度每秒
JOGGING_EXT double JoggingSpeedRate;    // 手动操纵的最大速度倍率，安全起见，要求手动操纵时不能全速运行，该值一般为0.5或0.8
JOGGING_EXT double SysSpeedRate;        // 机器人系统的速度倍率

JOGGING_EXT ITP_RobTarget sysInitRobTarget; // 定义一个机器人位置点，用于测试【转到】功能




namespace ProgramData {

typedef enum{
    ROB_TARGET,     // robtarget 机器人与外轴的位置数据
    JOINT_TARGET,   // jointtarget 关节位置数据
    TOOL_DATA,      // tooldata 工具数据
    WOBJ_DATA,      // wobjdata 工件数据
    LOAD_DATA,      // loaddata 负荷数据
    ZONE_DATA,      // zonedata TCP转弯半径数据
    SPEED_DATA,     // speeddata 机器人与外轴的速度数据
    BOOL,           // bool 布尔型
    NUM,            // num 数值型
    STRING          // string 字符串型
}DataTypes;     // 当前系统支持的程序数据类型

typedef enum{
    SCOPE_GLOBAL,
    SCOPE_LOCAL,
    SCOPE_TASK
}ScopeTypes;

typedef enum{
    STORAGE_VAR,
    STORAGE_PERS,
    STORAGE_CONST
}StorageTypes;

typedef enum{
    DIMENSION_NONE,
    DIMENSION_1,
    DIMENSION_2,
    DIMENSION_3
}DimensionTypes;


}   // end of namespace ProgramData

#ifdef PROGRAMDATA_GLOBALS
#define PROGRAMDATA_EXT
#else
#define PROGRAMDATA_EXT extern
#endif


//PROGRAMDATA_EXT QString curTask;    // 记录机器人当前任务
PROGRAMDATA_EXT QStringList dataTypesStrList;   // 记录当前系统支持的程序数据类型的字符串列表（robtarget、jointtarget ...）




#if defined(__cplusplus)
}
#endif

#endif // ROBMANUAL_COMMON_H
