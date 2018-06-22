/***************************************************************************
* Module Operation Explanation
* Replace DataManage.h with the name of the file
****************************************************************************/

/***************************************************************************
****************************************************************************
*Copyright(c),2008-2028,广州数控设备有限公司
*File name: FileAndDirOperate.h
*First Author: 叶杰盛
*Date:022/09/2015
*接口文件功能描述：文件操作
****************************************************************************
****************************************************************************/

#ifndef FILEOPERATE_H
#define FILEOPERATE_H

#ifdef AlarmFileInfo_GLOBALS
#define FileFIFO_EXT
#else
#define FileFIFO_EXT extern
#endif

#ifdef ProgramFileInfo_GLOBALS
#define FileFIFO_EXT
#else
#define FileFIFO_EXT extern
#endif

#ifdef DataManageFileInfo_GLOBALS
#define FileFIFO_EXT
#else
#define FileFIFO_EXT extern
#endif
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
#include <dir.h>
#include <dirent.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#define FILECONTENTROW 1024
#define FILECONTENTCOLUMN 256
#define FILENAMEROW 512
#define FILENAMECOLUMN 32
#define PATHSIZE 64
#define SUFFIXSIZE 8

#define FILEPATH    "./NC/"
#define ALARMFILEPATH	"./Alarm/"
#define PROGRAMFILEPATH "D:/MyStudyForQT/Practice/newhmi/hmi_windows/robhmi/hmi/bin/resource/NC/"
#define DATAMANAGEFILEPATH 	"./Data/"

typedef struct FileFIFO{
    int ReadPointer;//缓存读到文件指针
    int WritePointer;//文件写入缓存指针
    int FileLineNum;    //文件行数
    char FileContent[FILECONTENTROW][FILECONTENTCOLUMN];//文件内容
}FileFIFO;

typedef struct DirSuffixFIFO{
    int FileNum;	//该目录下该后缀的文件个数
    char FileName[FILENAMEROW][FILENAMECOLUMN];//该目录下该后缀的文件名
    char Path[PATHSIZE];	//该目录
    char Suffix[SUFFIXSIZE];	//后缀
}DirSuffixFIFO;	//目录下某后缀信息

/***************************************************************************/
/*函数功能：	初始化*/
/*输入参数：	AlarmFileInfo:报警文件信息,ProgramFileInfo:程序文件信息,DataManageFileInfo:数据管理文件信息*/
/*输出参数:	AlarmFileInfo:报警文件信息,ProgramFileInfo:程序文件信息,DataManageFileInfo:数据管理文件信息*/
/*返回值：	*/
/***************************************************************************/
void HMI_FileAndDirOperateInit(FileFIFO *AlarmFileInfo,FileFIFO *ProgramFileInfo,FileFIFO *DataManageFileInfo);

/***************************************************************************/
/*函数功能：	清除原文件内容,再写如文件*/
/*输入参数：	FileInfo:相应的文件信息结构,path:路径,filename:文件名*/
/*输出参数:	FileInfo:相应的文件信息结构*/
/*返回值：	-1:路径不存在,0:文件打开失败,1成功*/
/***************************************************************************/
int HMI_WriteFileClearContent(FileFIFO *FileInfo,char *path,char* filename);

/***************************************************************************/
/*函数功能：	不清除文件内容,追加到文件尾*/
/*输入参数：	FileInfo:相应的文件信息结构,path:路径,filename:文件名*/
/*输出参数:	FileInfo:相应的文件信息结构*/
/*返回值：	-1:路径不存在,0:文件打开失败,1成功*/
/***************************************************************************/
int HMI_WriteFileWithoutClearContent(FileFIFO *FileInfo,char *path, char *filename);

/***************************************************************************/
/*函数功能：	读文件内容*/
/*输入参数：	FileInfo:相应的文件信息结构,path:路径,filename:文件名*/
/*输出参数:	FileInfo:相应的文件信息结构*/
/*返回值：	-1:路径不存在,0:文件打开失败,1成功*/
/***************************************************************************/
int HMI_ReadFile(FileFIFO *FileInfo,char *path,char* filename);

/***************************************************************************/
/*函数功能：	重命名文件*/
/*输入参数：	path:路径,oldfilename:旧的文件名,newfilename:新的文件名*/
/*输出参数:	无*/
/*返回值：	-2:路径不存在,-1:源文件不存在,0:目标文件已存在,-3:重命名失败,1:成功*/
/***************************************************************************/
int HMI_RenameFile(char *path, char *oldfilename,char *newfilename);

/***************************************************************************/
/*函数功能：	删除文件*/
/*输入参数：	path:路径,filename:文件名*/
/*输出参数:	无*/
/*返回值：	-2:路径不存在,-1:源文件不存在,0:删除失败,1:成功*/
/***************************************************************************/
int HMI_DeleteFile(char *path, char *filename);

/***************************************************************************/
/*函数功能：	判断文件是否存在*/
/*输入参数：	path：路径,filename:文件名*/
/*输出参数:	无*/
/*返回值：	1:存在路径及文件名,0:不存在文件名,-1:不存在路径*/
/***************************************************************************/
int HMI_ExistFile(char *path, char *filename);

/***************************************************************************/
/*函数功能：	删除第几行*/
/*输入参数：	FileInfo:相应的文件信息结构,line:行号*/
/*输出参数:	FileInfo:相应的文件信息结构*/
/*返回值：	1:成功,0:需要删除行数大于文件行数且不能等于0*/
/***************************************************************************/
int HMI_DeleteLine(FileFIFO *FileInfo,int line);

/***************************************************************************/
/*函数功能：	插入第几行*/
/*输入参数：	FileInfo:相应的文件信息结构,line:行号,s:插入内容*/
/*输出参数:	FileInfo:相应的文件信息结构*/
/*返回值：	1:成功,0:需要删除行数大于文件行数且不能等于0*/
/***************************************************************************/
int HMI_InsertLine(FileFIFO *FileInfo,int line,char *s);

/***************************************************************************/
/*函数功能：	修改第几行数据*/
/*输入参数：	FileInfo:相应的文件信息结构,line:行号,s:修改内容*/
/*输出参数:	FileInfo:相应的文件信息结构*/
/*返回值：	1:成功,0:需要删除行数大于文件行数且不能等于0*/
/***************************************************************************/
int HMI_AlterFile(FileFIFO *FileInfo, int line,char *s);

/***************************************************************************/
/*函数功能：	新建路径*/
/*输入参数：	path:路径,DirName:目标目录名*/
/*输出参数:	无*/
/*返回值：	-2:路径不存在,-1:DirName不存在,0:新建失败,1:新建成功*/
/***************************************************************************/
int HMI_NewDir(char *path,char *DirName);

/***************************************************************************/
/*函数功能：	删除路径*/
/*输入参数：	path:路径,DirName:目标目录名*/
/*输出参数:	无*/
/*返回值：	-2:路径不存在,-1:DirName不存在,0:删除失败,1:删除成功*/
/***************************************************************************/
int HMI_DelDir(char *path,char *DirName);

/***************************************************************************/
/*函数功能：	根据后缀找出该目录下所有文件,不包括二级目录*/
/*输入参数：	path:路径,Suffix:后缀名,ok:判断是否获取成功*/
/*输出参数:	ok:true:成功,false:失败*/
/*返回值：	该目录下的后缀信息*/
/***************************************************************************/
DirSuffixFIFO HMI_FindFileBySuffix(char *path, char *Suffix,bool *ok);

FileFIFO_EXT FileFIFO AlarmFileInfo;	//报警文件
FileFIFO_EXT FileFIFO ProgramFileInfo;	//程序文件
FileFIFO_EXT FileFIFO DataManageFileInfo;	//数据管理文件

#if defined(__cplusplus)
}
#endif

#endif
