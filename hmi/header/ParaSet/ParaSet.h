/***************************************************************************
* Module Operation Explanation
* Replace DataManage.h with the name of the file
****************************************************************************/

/***************************************************************************
****************************************************************************
*Copyright(c),2008-2028,广州数控设备有限公司
*File name: ParaSet.h
*First Author: 叶杰盛
*Date:11/10/2015
*接口文件功能描述：参数设置接口
****************************************************************************
****************************************************************************/

#ifndef PARASET_H_
#define PARASET_H_

#ifdef robMotSetData_GLOBALS
#define ITP_MotSetData_EXT
#else
#define ITP_MotSetData_EXT extern
#endif

#ifdef ReadFileFIFO_GLOBALS
#define ReadFileFifo_EXT
#else
#define ReadFileFifo_EXT extern
#endif

/***************************************************************************/
#include "header/ITP_Interface.h"

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

#if defined(__cplusplus)
extern "C"
{
#endif

#define READFIFOROWSIZE 1024				/// 读文件缓冲队列FIFO行容量
#define READFIFOCOLUMNSIZE 256			/// 读文件缓冲队列FIFO列容量

#define PARAFILENAME "ParaData.txt"

/***************************************************************************/
typedef struct ReadFileFifo				/// 预读缓存
{
    FILE *file ;
    char *fileName;
    int lineNum;						/// 文件行号
    int read_pointer;					/// 读文件缓冲队列FIFO读指针
    int write_pointer;					/// 读文件缓冲队列FIFO写指针
    char file_content[READFIFOROWSIZE][READFIFOCOLUMNSIZE] ;	///缓冲队列FIFO内容
    int FIFO[][2];// 第一列保存内存序号(即在ITP_MotSetData结构体中的位置，如acc_acc:1,dec_acc:2等)
    	//第二列保存该序号在读文件缓冲区的行号
}ReadFileFifo;

/***************************************************************************/
/*函数功能：将文件中的数据加载到内存*/
/*输入参数：*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int HMI_ParaReadFile();

/***************************************************************************/
/*函数功能：将内存所有数据保存到文件*/
/*输入参数： */
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int HMI_ParaWriteFile();

/***************************************************************************/
/*函数功能：内存中修改数据,且对缓冲区相应行修改数据*/
/*输入参数：index:序号,pData:修改数据*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int HMI_ParaAlter(int index, void *pData);

/***************************************************************************/
/*函数功能：获取值并转换成double型*/
/*输入参数：s:缓冲区内容*/
/*输出参数: 无*/
/*返回值：double值*/
/***************************************************************************/
double getVarToDouble(char *s);

/***************************************************************************/
/*函数功能：获取值并转换成char型*/
/*输入参数：s:缓冲区内容*/
/*输出参数: 无*/
/*返回值：char值*/
/***************************************************************************/
char getVarToChar(char *s);

/***************************************************************************/
/*函数功能：判断该语句是否是参数设置的有效语句*/
/*输入参数：s:缓冲区内容*/
/*输出参数: 无*/
/*返回值：false 无效 true 有效*/
/***************************************************************************/
bool validString(char *s);

ITP_MotSetData_EXT ITP_MotSetData robMotSetData;
ReadFileFifo_EXT ReadFileFifo ReadFileFIFO;

#if defined(__cplusplus)
}
#endif

#endif /* PARASET_H_ */
