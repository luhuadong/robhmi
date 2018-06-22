/***************************************************************************
* Module Operation Explanation
* Replace DataManage.h with the name of the file
****************************************************************************/

/***************************************************************************
****************************************************************************
*Copyright(c),2008-2028,广州数控设备有限公司
*File name: DataManage.h
*First Author: 叶杰盛
*Date:06/09/2015
*接口文件功能描述：数据管理及处理
****************************************************************************
****************************************************************************/

#ifndef DataManage_H
#define DataManage_H

#ifdef quickToName_GLOBALS
#define DataManage_QuickToDataName_EXT
#else
#define DataManage_QuickToDataName_EXT extern
#endif

#ifdef quickToData_GLOBALS
#define DataManage_QuickToDataType_EXT
#else
#define DataManage_QuickToDataType_EXT extern
#endif

#ifdef robDataBuffer_GLOBALS
#define DataManage_BufferType_EXT
#else
#define DataManage_BufferType_EXT extern
#endif

#ifdef robDataName_GLOBALS
#define DataManage_DataName_EXT
#else
#define DataManage_DataName_EXT extern
#endif

#ifdef DataManageFIFO_GLOBALS
#define ReadFile_Fifo_EXT
#else
#define ReadFile_Fifo_EXT extern
#endif

/***************************************************************************/
#include "ITP_Interface.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/***************************************************************************/

//数据管理，主要用来管理:
//ITP_RobTarget(示教点数据)，ITP_JointTarget(关节坐标数据)
//ITP_WobjData(用户坐标系数据)，ITP_ToolData(工具坐标系数据)，ITP_LoadData(负载数据)
//ITP_ZoneData（拐角或结束处理数据），ITP_SpeedData(速度数据)

//处理方法：将以上数据以字符的形式放在一个文件中，格式定义：
/*
RobTarget
    P1=x,y,z,q1,q2,q3,q4,cf1,cf4,cf6,cfx,eax1,eax2,eax3,eax4,eax5,eax6

ENDRobTarget

JointTarget
    J1=robax1,robax2,robax3,robax4,robax5,robax6,extax1,extax2,extax3,extax4,extax5,extax6

ENDJointTarget

WobjData
    W1=robhold,ufprog,"name",x,y,z,q1,q2,q3,q4

ENDWobjData

ToolData
    T1=robhold,x,y,z,q1,q2,q3,q4

ENDToolData

ZoneData		//根据finep的值来判断数据类型
    Z1=finep,[pzone_tcp,pzone_ori,pzone_eax,zone_ori,zone_leax,zone_reax]
        或[stoppoint,progsynch,position,speed,mintime,maxtime,stoptime,followtime]

ENDZoneData

SpeedData
    V1=time,v_tcp,v_ort,v_leax,v_reax

ENDSpeedData
*/

#if defined(__cplusplus)
extern "C"
{
#endif

/***************************************************************************/
/*Add all #includes here*/

typedef int DataManageFile;	//文件类型

#define DataManage_RobTargetNum	20
#define DataManage_JointTargetNum	20
#define DataManage_WobjDataNum	20
#define DataManage_ToolDataNum	20
#define DataManage_ZoneDataNum	20
#define DataManage_SpeedDataNum	20

#define DataManage_DataNum	6

#define DataManage_RobTargetType	0
#define DataManage_JointTargetType	1
#define DataManage_WobjDataType		2
#define DataManage_ToolDataType		3
#define DataManage_ZoneDataType		4
#define DataManage_SpeedDataType	5

#define RobTargetType_NameLen 16	//变量名长度
#define JointTargetType_NameLen 16	//变量名长度
#define WobjDataType_NameLen 16	//变量名长度
#define ToolDataType_NameLen 16	//变量名长度
#define ZoneDataType_NameLen 16	//变量名长度
#define SpeedDataType_NameLen 16	//变量名长度

#define READ_FIFO_ROW_SIZE 1024				/// 读文件缓冲队列FIFO行容量
#define READ_FIFO_COLUMN_SIZE 256					/// 读文件缓冲队列FIFO列容量
#define AxisNum	6	///轴数

#define buf_size 256
#define buff_size 256
#define tmp_size 256

#define DataManage_FileName "Data"
/***************************************************************************/

typedef struct DataManage_BufferType
{
    char flagP[DataManage_RobTargetNum];	//0表示未使用，1表示已有数据
    ITP_RobTarget P[DataManage_RobTargetNum];	//位姿坐标

    char flagJ[DataManage_JointTargetNum];
    ITP_JointTarget J[DataManage_JointTargetNum];	//关节坐标

    char flagW[DataManage_WobjDataNum];
    ITP_WobjData W[DataManage_WobjDataNum];	//用户坐标系

    char flagT[DataManage_ToolDataNum];
    ITP_ToolData T[DataManage_ToolDataNum];	//工具数据

    char flagZ[DataManage_ZoneDataNum];
    ITP_ZoneData Z[DataManage_ZoneDataNum];	//指定平滑开始距离和角度

    char flagV[DataManage_SpeedDataNum];
    ITP_SpeedData V[DataManage_SpeedDataNum];	//速度数据
}DataManage_BufferType;

typedef struct DataManage_QuickToDataType	//用于快速定位数据
{
    void *pQuickTo[DataManage_DataNum];
}DataManage_QuickToDataType;

typedef struct ReadFile_Fifo				/// 预读缓存
{
    FILE *file ;
    char *fileName;
    DataManageFile pFile;	//文件类型
    int lineNum;						/// 文件行号
    int read_pointer;					/// 读文件缓冲队列FIFO读指针
    int write_pointer;					/// 读文件缓冲队列FIFO写指针
    char file_content[READ_FIFO_ROW_SIZE][READ_FIFO_COLUMN_SIZE] ;	///缓冲队列FIFO内容
}ReadFile_Fifo;

typedef struct DataManage_DataName
{
    int PNum;//ITP_RobTarget数据的个数	不能超过DataManage_RobTargetNum PNum-1:记录数据结构保存到第几个数组下标了
    char PName[DataManage_RobTargetNum][RobTargetType_NameLen];//位姿坐标

    int JNum;//ITP_JointTarget数据的个数 不能超过DataManage_WobjDataNum
    char JName[DataManage_JointTargetNum][JointTargetType_NameLen];	//关节坐标

    int WNum;//ITP_WobjData数据的个数 不能超过DataManage_RobTargetNum
    char WName[DataManage_WobjDataNum][WobjDataType_NameLen];	//用户坐标系

    int TNum;//ITP_ToolData数据的个数 不能超过DataManage_ToolDataNum
    char TName[DataManage_ToolDataNum][ToolDataType_NameLen];	//工具数据

    int ZNum;//ITP_ZoneData数据的个数 不能超过DataManage_ZoneDataNum
    char ZName[DataManage_ZoneDataNum][ZoneDataType_NameLen];	//指定平滑开始距离和角度

    int VNum;//ITP_SpeedData数据的个数 不能超过DataManage_SpeedDataNum
    char VName[DataManage_SpeedDataNum][SpeedDataType_NameLen];	//速度数据
}DataManage_DataName;

typedef struct DataManage_QuickToDataName	//用于变量名快速定位数据
{
    void *pQuickToName[DataManage_DataNum];
}DataManage_QuickToDataName;

/***************************************************************************/
/*函数功能：拆分数据ITP_RobTarget*/
/*输入参数： index：下标,s:FIFO缓存区字符串*/
/*输出参数: 	  无*/
/*返回值：	  ITP_RobTarget类型的数据*/
/***************************************************************************/
ITP_RobTarget split_RobTarget(int index,char *s);

/***************************************************************************/
/*函数功能：拆分数据ITP_JointTarget*/
/*输入参数： index：下标,s:FIFO缓存区字符串*/
/*输出参数: 	  无*/
/*返回值：	  ITP_JointTarget类型的数据*/
/***************************************************************************/
ITP_JointTarget split_JointTarget(int index,char *s);

/***************************************************************************/
/*函数功能：拆分数据ITP_WobjData*/
/*输入参数： index：下标,s:FIFO缓存区字符串*/
/*输出参数: 	  无*/
/*返回值：	  ITP_WobjData类型的数据*/
/***************************************************************************/
ITP_WobjData split_WobjData(int index,char **ch,char *s);

/***************************************************************************/
/*函数功能：拆分数据ITP_ToolData*/
/*输入参数： index：下标,s:FIFO缓存区字符串*/
/*输出参数: 	  无*/
/*返回值：	  ITP_ToolData类型的数据*/
/***************************************************************************/
ITP_ToolData split_ToolData(int index,char *s);

/***************************************************************************/
/*函数功能：拆分数据ITP_ZoneData*/
/*输入参数： index：下标,s:FIFO缓存区字符串*/
/*输出参数: 	  无*/
/*返回值：	 ITP_ZoneData类型的数据*/
/***************************************************************************/
ITP_ZoneData split_ZoneData(int index,char *s);

/***************************************************************************/
/*函数功能：拆分数据SpeedData*/
/*输入参数： index：下标,s:FIFO缓存区字符串*/
/*输出参数: 	  无*/
/*返回值：	 ITP_SpeedData类型的数据*/
/***************************************************************************/
ITP_SpeedData split_SpeedData(int index,char *s);

/***************************************************************************/
/*函数功能：获取序号*/
/*输入参数： s:变量名*/
/*输出参数: 无*/
/*返回值： 序号,返回-1表示错误*/
/***************************************************************************/
int Obtain_Snum(char *s);

/***************************************************************************/
/*函数功能：获取变量名*/
/*输入参数： s:FIFO缓存区字符串*/
/*输出参数: 无*/
/*返回值： 变量名,返回NULL获取失败*/
/***************************************************************************/
char *Obtain_DataName(char *s);

/***************************************************************************/
/*函数功能：获取在robDataBuffer相应数据*/
/*输入参数： flagType:数据类型,DataName:变量名*/
/*输出参数: 无*/
/*返回值： robDataBuffer相应的数据,获取失败返回NULL*/
/***************************************************************************/
void *getData(int flagType,char *DataName);	//在robDataBuffer获取数据

/***************************************************************************/
/*函数功能：数据初始化*/
/*输入参数： pQuickTo:,pBuffer:,pQuickToName:,pDataName:*/
/*输出参数: 无*/
/*返回值： 无*/
/***************************************************************************/
void DataManage_Init(DataManage_QuickToDataType *pQuickTo,DataManage_BufferType *pBuffer,
        DataManage_QuickToDataName *pQuickToName,DataManage_DataName *pDataName);

/***************************************************************************/
/*函数功能：将文件中的数据加载到内存*/
/*输入参数： pFile:文件类型*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_ReadFile(DataManageFile *pFile);

/***************************************************************************/
/*函数功能：将内存中的某个数据保存到文件*/
/*输入参数： flagType=0表示ITP_RobTarget，1表示ITP_JointTarget，2表示ITP_WobjData…………依此类推，flagNo:下标,pData:需要保存的数据*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_WriteFile_Item(int flagType, int flagNo, void *pData);

/***************************************************************************/
/*函数功能：将内存所有数据保存到文件*/
/*输入参数： pFile:文件类型*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_WriteFile(DataManageFile *pFile);

/***************************************************************************/
/*函数功能：文件中修改数据*/
/*输入参数： flagType=0表示ITP_RobTarget，1表示ITP_JointTarget，2表示ITP_WobjData…………依此类推，flagNo:下标,pData:需要保存的数据*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_AlterFile(int flagType, int flagNo, void *pData);

/***************************************************************************/
/*函数功能：内存中删除数据*/
/*输入参数： pBuffer:数据内存,flagType=0表示ITP_RobTarget，1表示ITP_JointTarget，2表示ITP_WobjData…………依此类推，flagNo:下标*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_Delete(DataManage_BufferType *pBuffer,int flagType,int flagNo);

/***************************************************************************/
/*函数功能：内存中添加数据*/
/*输入参数： pBuffer:数据内存,pDataName:名字内存,flagType:数据类型,flagNo:下标,pData:需要添加的数据,DataName:新加数据名*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_Add(DataManage_BufferType *pBuffer,DataManage_DataName *pDataName,int flagType,
        void *pData,char *DataName);

/***************************************************************************/
/*函数功能：内存中修改数据*/
/*输入参数： pBuffer:数据内存,flagType=0表示ITP_RobTarget，1表示ITP_JointTarget，2表示ITP_WobjData…………依此类推，flagNo:下标,pData:需要修改的数据*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_Alter(DataManage_BufferType *pBuffer,int flagType,int flagNo,void *pData);

/***************************************************************************/
/*函数功能：清理内存数据*/
/*输入参数： pBuffer:数据内存*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int DataManage_Clear(DataManage_BufferType *pBuffer);

DataManage_BufferType_EXT DataManage_BufferType robDataBuffer;
DataManage_DataName_EXT DataManage_DataName robDataName;
DataManage_QuickToDataType_EXT DataManage_QuickToDataType quickToData;
DataManage_QuickToDataName_EXT DataManage_QuickToDataName quickToName;
ReadFile_Fifo_EXT ReadFile_Fifo DataManageFIFO;


#if defined(__cplusplus)
}
#endif

#endif
