
#include "header/DataManage_WinShareMem.h"

#if Windows

HANDLE hRecvMap_InputData;          //存放文件映射对象的句柄，用于后来的释放操作
HANDLE hRecvMap_OutputData;          //存放文件映射对象的句柄，用于后来的释放操作
HANDLE hRecvMap_MotSetData;          //存放文件映射对象的句柄，用于后来的释放操作

int DataManage_InitShareMem_InputData(int flagNew,void **pShareMem)
{
    char *cstr = "ITP_ShareMem_InputData";

    size_t cstr_len = strlen(cstr);
    size_t n = (size_t)MultiByteToWideChar(CP_ACP,0,(const char*)cstr,(int)cstr_len,NULL,0);
    wchar_t pwstr[pwstr_size];
    if(n>=pwstr_size) n = pwstr_size-1;

    MultiByteToWideChar(CP_ACP,0,(const char*)cstr,(int)cstr_len,pwstr,(int)n);
    pwstr[n]=0;

    //以上将char * 转换为wchar_t *

    HANDLE handle;
    if(flagNew == 1)
    {
        //创建一个命名的共享内存对象，指定相应的访问方式与初始化空间大小
        handle = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE | SEC_COMMIT, 0,sizeof(ITP_InputData), pwstr);
    }
    else
    {
        //尝试打开指定命名的共享内存，获取相应对象的句柄
        handle = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, 0, pwstr);
    }

    if(handle != 0)//判断句柄是否指向有效的命名对象，否则初始化失败
    {
        if(flagNew == 1)
        {
            *pShareMem = MapViewOfFile(handle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
            memset(*pShareMem, 0, sizeof(ITP_InputData));//清空共享内存中的数据
        }
        else
        {
            *pShareMem = MapViewOfFile(handle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
        }

        if(pShareMem != 0)
        {
            hRecvMap_InputData=handle;
            return 1;
        }
        else
        {
            CloseHandle(handle);
        }
    }else{
        *pShareMem = 0;
    }
    return 0;
}

void DataManage_CloseShareMem_InputData(void *pShareMem)
{
    if(pShareMem != 0)
    {
        UnmapViewOfFile(pShareMem);
    }
    if(hRecvMap_InputData != 0)
    {
        CloseHandle(hRecvMap_InputData);
        hRecvMap_InputData = 0;
    }
}

int DataManage_InitShareMem_OutputData(int flagNew,void **pShareMem)
{
    char *cstr = "ITP_ShareMem_OutputData";

    size_t cstr_len = strlen(cstr);
    size_t n = (size_t)MultiByteToWideChar(CP_ACP,0,(const char*)cstr,(int)cstr_len,NULL,0);
    wchar_t pwstr[pwstr_size];
    if(n>=pwstr_size) n = pwstr_size-1;

    MultiByteToWideChar(CP_ACP,0,(const char*)cstr,(int)cstr_len,pwstr,(int)n);
    pwstr[n]=0;

    //以上将char * 转换为wchar_t *

    HANDLE handle;
    if(flagNew == 1)
    {
        //创建一个命名的共享内存对象，指定相应的访问方式与初始化空间大小
        handle = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE | SEC_COMMIT, 0,sizeof(ITP_OutputData), pwstr);
    }
    else
    {
        //尝试打开指定命名的共享内存，获取相应对象的句柄
        handle = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, 0,pwstr );
    }

    if(handle != 0)//判断句柄是否指向有效的命名对象，否则初始化失败
    {
        if(flagNew == 1)
        {
            *pShareMem = MapViewOfFile(handle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
            memset(*pShareMem, 0, sizeof(ITP_OutputData));//清空共享内存中的数据
        }
        else
        {
            *pShareMem = MapViewOfFile(handle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
        }

        if(pShareMem != 0)
        {
            hRecvMap_OutputData=handle;
            return 1;
        }
        else
        {
            CloseHandle(handle);
        }
    }else{
        *pShareMem = 0;
    }

    return 0;
}

void DataManage_CloseShareMem_OutputData(void *pShareMem)
{
    if(pShareMem != 0)
    {
        UnmapViewOfFile(pShareMem);
    }
    if(hRecvMap_OutputData != 0)
    {
        CloseHandle(hRecvMap_OutputData);
        hRecvMap_OutputData = 0;
    }
}

int DataManage_InitShareMem_MotSetData(int flagNew,void **pShareMem)
{
    char *cstr = "ITP_ShareMem_MotSetData";

    size_t cstr_len = strlen(cstr);
    size_t n = (size_t)MultiByteToWideChar(CP_ACP,0,(const char*)cstr,(int)cstr_len,NULL,0);
    wchar_t pwstr[pwstr_size];
    if(n>=pwstr_size) n = pwstr_size-1;

    MultiByteToWideChar(CP_ACP,0,(const char*)cstr,(int)cstr_len,pwstr,(int)n);
    pwstr[n]=0;

    HANDLE handle;
    if(flagNew == 1)
    {
        //创建一个命名的共享内存对象，指定相应的访问方式与初始化空间大小
        handle = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE | SEC_COMMIT, 0,sizeof(ITP_MotSetData), pwstr);
    }
    else
    {
        //尝试打开指定命名的共享内存，获取相应对象的句柄
        handle = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, 0, pwstr);
    }

    if(handle != 0)//判断句柄是否指向有效的命名对象，否则初始化失败
    {
        if(flagNew == 1)
        {
            *pShareMem = MapViewOfFile(handle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
            memset(*pShareMem, 0, sizeof(ITP_MotSetData));//清空共享内存中的数据
        }
        else
        {
            *pShareMem = MapViewOfFile(handle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
        }

        if(pShareMem != 0)
        {
            hRecvMap_MotSetData=handle;
            return 1;
        }
        else
        {
            CloseHandle(handle);
        }
    }
    return 0;
}

void DataManage_CloseShareMem_MotSetData(void *pShareMem)
{
    if(pShareMem != 0)
    {
        UnmapViewOfFile(pShareMem);
    }
    if(hRecvMap_MotSetData != 0)
    {
        CloseHandle(hRecvMap_MotSetData);
        hRecvMap_MotSetData = 0;
    }
}

#endif
