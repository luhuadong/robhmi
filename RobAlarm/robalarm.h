/***************************************************************************
* Module Operation Explanation
* Replace robalarm.h with the name of the file
****************************************************************************/

/***************************************************************************
****************************************************************************
*Copyright(c),2008-2028,广州数控设备有限公司
*File name: robalarm.h
*First Author: 叶杰盛
*Date:08/27/2015
*接口文件功能描述：报警信息处理,实现报警.
****************************************************************************
****************************************************************************/

#ifndef ROBALARM_H
#define ROBALARM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OtherType 0
#define InterpolateType 1
#define DecodeType 2
#define IOType 3
#define DriveType 4

#define READ_FIFO_ROW_SIZE 1024
#define READ_FIFO_COLUMN_SIZE 512

#define ALARM_CONTENT_ROW_SIZE 5
#define ALARM_CONTENT_COLUMN_SIZE 512

#define OtherALARM_CONTENT_ROW_SIZE 512
#define OtherALARM_CONTENT_COLUMN_SIZE  128
#define InterpolateALARM_CONTENT_ROW_SIZE 512
#define InterpolateALARM_CONTENT_COLUMN_SIZE 128
#define DecodeALARM_CONTENT_ROW_SIZE 512
#define DecodeALARM_CONTENT_COLUMN_SIZE 128
#define IOALARM_CONTENT_ROW_SIZE 512
#define IOALARM_CONTENT_COLUMN_SIZE 128
#define DriveALARM_CONTENT_ROW_SIZE 512
#define DriveALARM_CONTENT_COLUMN_SIZE 128

#define OTHER_ALARMNUM 512
#define INTERPOLATE_ALARMNUM 512
#define DECODE_ALARMNUM 512
#define IO_ALARMNUM 512
#define DRIVE_ALARMNUM 512

#define TYPENUM 5 //类型数
#define InfoFIFO_ROW_SIZE 512
#define InfoFIFO_COLUMN_SIZE 128

#define InfoQueue_SIZE 64
//InfoFIFO_ROW_SIZE与DriveALARM_CONTENT_ROW_SIZE等要相同

#define ALARM_FILE_NAME "AlarmInfo.txt"

#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct AlarmFileFifo				// 读报警文件缓冲区
{
    int Fileline;						/// 文件行号
    int ReadPointer;					/// 读文件缓冲队列FIFO读指针
    int WritePointer;					/// 读文件缓冲队列FIFO写指针
    char FileContent[READ_FIFO_ROW_SIZE][READ_FIFO_COLUMN_SIZE] ;	///缓冲队列FIFO内容
}AlarmFileFifo;// 报警文件缓冲区

typedef struct AlarmInfo{
    int RobAlarmNum;    //报警号
    int RobAlarmType;   //报警类型  如,0:其他报警,1:插补报警,2:译码报警,3:IO报警，4:驱动报警

    char RobAlarmContent[ALARM_CONTENT_ROW_SIZE][ALARM_CONTENT_COLUMN_SIZE];
    //RobAlarmContent[1]、RobAlarmContent[2]、RobAlarmContent[3]
    //分别保存索引到的报警内容、说明、处理方法
    char InfoQueue[InfoQueue_SIZE];        //报警消息队列
}AlarmInfo;//报警信息

typedef struct OtherAlarm{
    int Num;//报警信息个数
    int AlarmNum[OTHER_ALARMNUM];   //保存该类型所有报警号
    char AlarmContent[OtherALARM_CONTENT_ROW_SIZE][OtherALARM_CONTENT_COLUMN_SIZE];
}OtherAlarm; //其他报警信息

typedef struct InterpolateAlarm{
    int Num;//报警信息个数
    int AlarmNum[INTERPOLATE_ALARMNUM];   //保存该类型所有报警号
    char AlarmContent[InterpolateALARM_CONTENT_ROW_SIZE][InterpolateALARM_CONTENT_COLUMN_SIZE];
}InterpolateAlarm; //插补报警信息

typedef struct DecodeAlarm{
    int Num;//报警信息个数
    int AlarmNum[DECODE_ALARMNUM];   //保存该类型所有报警号
    char AlarmContent[DecodeALARM_CONTENT_ROW_SIZE][DecodeALARM_CONTENT_COLUMN_SIZE];
}DecodeAlarm; //译码报警信息

typedef struct IOAlarm{
    int Num;//报警信息个数
    int AlarmNum[IO_ALARMNUM];   //保存该类型所有报警号
    char AlarmContent[IOALARM_CONTENT_ROW_SIZE][IOALARM_CONTENT_COLUMN_SIZE];
}IOAlarm; //IO报警信息

typedef struct DriveAlarm{
    int Num;//报警信息个数
    int AlarmNum[DRIVE_ALARMNUM];   //保存该类型所有报警号
    char AlarmContent[DriveALARM_CONTENT_ROW_SIZE][DriveALARM_CONTENT_COLUMN_SIZE];
}DriveAlarm; //驱动报警信息

typedef struct AlarmSplitInfo{
    OtherAlarm RobOtherAlarm;
    InterpolateAlarm RobInterpolateAlarm;
    DecodeAlarm RobDecodeAlarm;
    IOAlarm RobIOAlarm;
    DriveAlarm RobDriveAlarm;
    char InfoFIFO[TYPENUM][InfoFIFO_ROW_SIZE][InfoFIFO_COLUMN_SIZE];
}AlarmSplitInfo;//报警分类信息

#ifdef RobAlarmBuffer_GLOBALS
#define AlarmInfo_GLOBALS_EXT
#else
#define AlarmInfo_GLOBALS_EXT extern
#endif
AlarmInfo_GLOBALS_EXT AlarmInfo RobAlarmBuffer;//报警信息

#ifdef RobAlarmFIFO_GLOBALS
#define AlarmFileFifo_GLOBALS_EXT
#else
#define AlarmFileFifo_GLOBALS_EXT extern
#endif
AlarmFileFifo_GLOBALS_EXT AlarmFileFifo RobAlarmFIFO;// 报警文件缓冲区

#ifdef RobAlarmFIFO_GLOBALS
#define AlarmSplitInfo_GLOBALS_EXT
#else
#define AlarmSplitInfo_GLOBALS_EXT extern
#endif
AlarmSplitInfo_GLOBALS_EXT AlarmSplitInfo RobAlarmSplitInfo;// 报警分类信息

/***************************************************************************/
/*函数功能：报警接口*/
/*输入参数：RobAlarmType:报警类型,RobAlarmNum:报警号*/
/*输出参数: 无*/
/*返回值：1:报警成功,0:失败*/
/***************************************************************************/
int RobAlarm(int RobAlarmType,int RobAlarmNum);

/***************************************************************************/
/*函数功能：读取报警信息文件*/
/*输入参数：FileName:报警信息文件名*/
/*输出参数: 无*/
/*返回值：1:读取成功,0读取失败*/
/***************************************************************************/
int ReadAlarmFile(char *FileName);

/***************************************************************************/
/*函数功能：获取报警号所对应的报警内容、说明、处理方法*/
/*输入参数：RobAlarmType:报警类型,RobAlarmNum:报警号*/
/*输出参数: 无*/
/*返回值：1获取成功,0获取失败*/
/***************************************************************************/
int ObtainAlarmContent(int RobAlarmType,int RobAlarmNum);

/***************************************************************************/
/*函数功能：检查是否有这个报警类型及报警号*/
/*输入参数：RobAlarmType:报警类型,RobAlarmNum:报警号*/
/*输出参数: 无*/
/*返回值：1:存在这个报警类型及报警号,0:不存在这个报警类型,-1:不存在这个报警号*/
/***************************************************************************/
int CheckTypeAndNum(int RobAlarmType,int RobAlarmNum);

/***************************************************************************/
/*函数功能：将报警信息分类*/
/*输入参数：无*/
/*输出参数: 无*/
/*返回值：空*/
/***************************************************************************/
void SplitAlarmInfo();

/***************************************************************************/
/*函数功能：获取RobAlarmType类型的所有的报警号并保存在分类报警信息RobAlarmSplitInfo的相应类型的AlarmNum*/
/*输入参数：RobAlarmType:报警类型*/
/*输出参数: 无*/
/*返回值：1:存在这个报警类型及报警号,0:不存在这个报警类型,-1:不存在这个报警号*/
/***************************************************************************/
void ObtainAllAlarmNum(int RobAlarmType);

/***************************************************************************/
/*函数功能：获取报警号*/
/*输入参数：content:报警内容*/
/*输出参数: 无*/
/*返回值：报警号,返回-1表示出错*/
/***************************************************************************/
int ObtainAlarmNum(char *content);

/***************************************************************************/
/*函数功能：获取报警内容、说明、处理方法*/
/*输入参数：content:报警内容,flagNew=1:获取报警内容、flagNew=2:获取报警说明、flagNew=3:获取报警处理方法*/
/*输出参数: 无*/
/*返回值：返回NULL,获取错误,返回报警内容、说明、处理方法*/
/***************************************************************************/
char *ObtainContent(char *content, int flagNew);

#if defined(__cplusplus)
}
#endif


#endif  // ROBALARM_H
