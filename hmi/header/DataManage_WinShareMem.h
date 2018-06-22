#ifndef DataManage_WinShareMem_H
#define DataManage_WinShareMem_H

#include "header/ITP_Interface.h"
#include <QtGlobal>

#ifdef Q_OS_LINUX
#define Linux 1
#define Windows 0
#include <sys/shm.h>
#elif defined (Q_OS_WIN32)
#define Linux 0
#define Windows 1
#include <Windows.h>
#endif

#define pwstr_size 32

#if defined(__cplusplus)
extern "C"
{
#endif

//flagNew=1表示新建，0表示读取已建共享内存,pShareMem共享内存地址
int DataManage_InitShareMem_InputData(int flagNew,void **pShareMem);//输入共享内存申请
void DataManage_CloseShareMem_InputData(void *pShareMem);			//输入共享内存释放

int DataManage_InitShareMem_OutputData(int flagNew, void **pShareMem);
void DataManage_CloseShareMem_OutputData(void *pShareMem);

int DataManage_InitShareMem_MotSetData(int flagNew,void **pShareMem);
void DataManage_CloseShareMem_MotSetData(void *pShareMem);
#if defined(__cplusplus)
}
#endif

#endif
