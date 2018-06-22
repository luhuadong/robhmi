#define AlarmFileInfo_GLOBALS
#define ProgramFileInfo_GLOBALS
#define DataManageFileInfo_GLOBALS

#define PATHANDNAME	128

#include "FileAndDirOperate.h"

void HMI_FileAndDirOperateInit(FileFIFO *AlarmFileInfo,FileFIFO *ProgramFileInfo,FileFIFO *DataManageFileInfo)
{
	AlarmFileInfo->WritePointer = 1;
	AlarmFileInfo->ReadPointer = 1;

	ProgramFileInfo->WritePointer = 1;
	ProgramFileInfo->ReadPointer = 1;

	DataManageFileInfo->WritePointer = 1;
	DataManageFileInfo->ReadPointer = 1;

    int i = 0 ;
    for(i = 0 ;i<FILECONTENTROW;i++){
        memset(ProgramFileInfo->FileContent[i],0,sizeof(ProgramFileInfo->FileContent[i]));
        memset(AlarmFileInfo->FileContent[i],0,sizeof(AlarmFileInfo->FileContent[i]));
        memset(DataManageFileInfo->FileContent[i],0,sizeof(DataManageFileInfo->FileContent[i]));
    }
}

int HMI_ReadFile(FileFIFO *FileInfo,char *path, char *filename)
{
    if(HMI_ExistFile(path,filename) == -1)
		return -1;	//路径不存在

	char PathAndName[PATHANDNAME];
	memset(PathAndName,0,sizeof(PathAndName));

	strcpy(PathAndName,path);
	strcat(PathAndName,filename);

    FILE *file = NULL;

    file = fopen(PathAndName,"a+");

    if(file == NULL){
        return 0;
    }

    FileInfo->WritePointer=1;
	while(fgets(FileInfo->FileContent[FileInfo->WritePointer],
				sizeof(FileInfo->FileContent[FileInfo->WritePointer]),file)!=NULL){
		FileInfo->WritePointer++;	//读到最后一行后,仍然+1
	}

    FileInfo->FileLineNum = FileInfo->WritePointer-1;//所有-1

    fclose(file);

    return 1;
}

int HMI_WriteFileClearContent(FileFIFO *FileInfo,char *path, char *filename)	//清除文件内容再写
{
    if(HMI_ExistFile(path,filename) == -1)
		return -1;	//路径不存在

	char PathAndName[PATHANDNAME];
	memset(PathAndName,0,sizeof(PathAndName));

	strcpy(PathAndName,path);
	strcat(PathAndName,filename);

	FILE *file = NULL;
    file = fopen(PathAndName,"w+");//w+:文件不存在则新建,存在则清除文件内容	a+:文件不存在则新建,存在则添加到文件尾

    if(file == NULL){
        return 0;
    }

    FileInfo->ReadPointer=1;
    while(FileInfo->ReadPointer <= FileInfo->FileLineNum){
    	fputs(FileInfo->FileContent[FileInfo->ReadPointer],file);
    	FileInfo->ReadPointer++;
    }

	fclose(file);

    return 1;
}

int HMI_WriteFileWithoutClearContent(FileFIFO *FileInfo,char *path, char *filename)	//不清除文件内容,追加到文件尾
{
    if(HMI_ExistFile(path,filename) == -1)
		return -1;	//路径不存在

	char PathAndName[PATHANDNAME];
	memset(PathAndName,0,sizeof(PathAndName));

	strcpy(PathAndName,path);
	strcat(PathAndName,filename);

	FILE *file = NULL;
    file = fopen(PathAndName,"a+");//w+:文件不存在则新建,存在则清除文件内容	a+:文件不存在则新建,存在则添加到文件尾

    if(file == NULL){
        return 0;
    }

    FileInfo->ReadPointer=1;
    while(FileInfo->ReadPointer <= FileInfo->FileLineNum){
    	fputs(FileInfo->FileContent[FileInfo->ReadPointer],file);
    	FileInfo->ReadPointer++;
    }

	fclose(file);

    return 1;
}

int HMI_DeleteFile(char *path, char *filename)
{
    if(HMI_ExistFile(path,filename) == -1)
		return -2;	//路径不存在

    if(HMI_ExistFile(path,filename) == 0)
		return -1;//	filename不存在

	char PathAndName[PATHANDNAME];
	memset(PathAndName,0,sizeof(PathAndName));

	strcpy(PathAndName,path);
	strcat(PathAndName,filename);

	if(remove(PathAndName) == 0)
		return 1;
	else
		return 0;	//删除失败
}

int HMI_ExistFile(char *path, char *filename)
{
	DIR *ptr_dir = NULL;
	struct dirent *dir_entry;

	ptr_dir = opendir(path);
	if(ptr_dir==NULL)
		return -1;//不存在路径

	while((dir_entry = readdir(ptr_dir)) != NULL){
		if(strcmp(dir_entry->d_name,filename) == 0 )
			return 1;
	}

    return 0;	//默认返回0,即文件不存在
}

int HMI_RenameFile(char *path, char *oldfilename, char *newfilename)
{
    if(HMI_ExistFile(path,oldfilename) == -1&&HMI_ExistFile(path,newfilename) == -1)
		return -2;	//路径不存在

    if(HMI_ExistFile(path,oldfilename) == 0)
		return -1;//	oldfilename不存在

    if(HMI_ExistFile(path,newfilename) == 1)
		return 0;//	newfilename已经存在

//    if(strcmp(oldfilename , newfilename)==0)
//        return -3;//新旧名字重名	貌似不用那个判断

    char newname[PATHANDNAME];
	char oldname[PATHANDNAME];
	memset(oldname,0,sizeof(oldname));
	memset(newname,0,sizeof(newname));

	strcpy(oldname,path);
	strcat(oldname,oldfilename);

	strcpy(newname,path);
	strcat(newname,newfilename);

	if(rename(oldname, newname) == 0)
		return 1;
	else
		return -3;//其他出错
}

int HMI_DeleteLine(FileFIFO *FileInfo,int line)
{
	if(line>FileInfo->FileLineNum || line==0)
		return 0;	//需要删除行数大于文件行数	不能等于0

	int i = line;

	for(;i<FileInfo->FileLineNum;i++){
		strcpy(FileInfo->FileContent[i] ,FileInfo->FileContent[i+1]);
	}
	memset(FileInfo->FileContent[FileInfo->FileLineNum],0,sizeof(FileInfo->FileContent[FileInfo->FileLineNum]));
	FileInfo->FileLineNum--;

    return 1;
}

int HMI_InsertLine(FileFIFO *FileInfo,int line,char *s)
{
	if(line>FileInfo->FileLineNum || line==0)
		return 0;	//需要删除行数大于文件行数	不能等于0

	int i = FileInfo->FileLineNum;
	for(;i>=line;i--){
		strcpy(FileInfo->FileContent[i+1] ,FileInfo->FileContent[i]);
	}

	strcpy(FileInfo->FileContent[line] ,s);
	FileInfo->FileLineNum++;

    return 1;
}

int HMI_AlterFile(FileFIFO *FileInfo,int line,char *s)
{
	if(line>FileInfo->FileLineNum || line==0)
		return 0;	//需要删除行数大于文件行数	不能等于0

	strcpy(FileInfo->FileContent[line] ,s);

	return 1;
}

//Dir
int HMI_NewDir(char *path,char *DirName)
{
    if(HMI_ExistFile(path,DirName) == -1)
		return -2;	//路径不存在

    if(HMI_ExistFile(path,DirName) == 1)
		return -1;//	DirName已存在

	char PathAndName[PATHANDNAME];
	memset(PathAndName,0,sizeof(PathAndName));

	strcpy(PathAndName,path);
	strcat(PathAndName,DirName);

	if(!mkdir(PathAndName))//0表示成功
		return 1;

	return 0;	//创建失败
}

int HMI_DelDir(char *path,char *DirName)
{
    if(HMI_ExistFile(path,DirName) == -1)
		return -2;	//路径不存在

    if(HMI_ExistFile(path,DirName) == 0)
		return -1;//	DirName不存在

	char PathAndName[PATHANDNAME];
	memset(PathAndName,0,sizeof(PathAndName));

	strcpy(PathAndName,path);
	strcat(PathAndName,DirName);

	if (!rmdir(PathAndName))
		return 1;

	return 0;
}

DirSuffixFIFO HMI_FindFileBySuffix(char *path, char *Suffix,bool *ok)	//根据后缀找出该目录下所有文件,不包括二级目录
{
    DIR *ptr_dir = NULL;
    struct dirent *dir_entry;

    DirSuffixFIFO DirSuffixInfo;

    *ok = true;
    ptr_dir = opendir(path);
    if(ptr_dir==NULL){
        *ok = false;
        return DirSuffixInfo;
    }

    DirSuffixInfo.FileNum=0;//Init
    strcpy(DirSuffixInfo.Suffix,Suffix);
    strcpy(DirSuffixInfo.Path,path);

    char SuffixTmp[8];	//保存文件后缀
    memset(SuffixTmp,0,sizeof(SuffixTmp));

    int dotPos = 0 ,index = 0,i;
    char *ptr;

    while((dir_entry = readdir(ptr_dir)) != NULL){
        ptr = strrchr(dir_entry->d_name, '.');
        if(ptr){	//有点
            dotPos = ptr-dir_entry->d_name;
            for(i = dotPos+1;i<strlen(dir_entry->d_name);i++)
                SuffixTmp[index++] = dir_entry->d_name[i];
        }else{//没点

        }

        if(strcmp(SuffixTmp,Suffix) == 0){
            strcpy(DirSuffixInfo.FileName[DirSuffixInfo.FileNum],dir_entry->d_name);
            DirSuffixInfo.FileNum++;
        }

        index = 0;
        memset(SuffixTmp,0,sizeof(SuffixTmp));
    }

    return DirSuffixInfo;
}
