/***************************************************************************
* Module Operation Explanation
* Replace robalarm.cpp with the name of the file
* Fills the include, flaged with +include+
* Fills the definition flaged with =====
*
****************************************************************************/

/***************************************************************************
****************************************************************************
*Copyright(c),2008-2028,广州数控设备有限公司
*File name: robalarm.cpp
*First Author:叶杰盛
*Date:08/27/2015
*文件功能描述：报警接口实现文件
****************************************************************************
****************************************************************************/

#define RobAlarmFIFO_GLOBALS
#define RobAlarmBuffer_GLOBALS
#define RobAlarmFIFO_GLOBALS

#include "robalarm.h"

/***************************************************************************/
/*函数功能：读取报警信息文件*/
/*输入参数：FileName:报警信息文件名*/
/*输出参数: 无*/
/*返回值：1:读取成功,0读取失败*/
/***************************************************************************/
int ReadAlarmFile(char *FileName)
{
    FILE *file = NULL;
    file = fopen(FileName,"r+");

    if(file == NULL){
        perror("fopen fail");
        return 0;
    }

    RobAlarmFIFO.WritePointer=0;
    RobAlarmFIFO.ReadPointer=0;

    while(fgets(RobAlarmFIFO.FileContent[RobAlarmFIFO.WritePointer++],
                sizeof(RobAlarmFIFO.FileContent[RobAlarmFIFO.WritePointer]),file)!=NULL){
        memset(RobAlarmFIFO.FileContent[RobAlarmFIFO.WritePointer],0,
                sizeof(RobAlarmFIFO.FileContent[RobAlarmFIFO.WritePointer]));
    }

    RobAlarmFIFO.Fileline = RobAlarmFIFO.WritePointer;
    //读完,分类
    SplitAlarmInfo();
    return 1;
}

/***************************************************************************/
/*函数功能：将报警信息分类*/
/*输入参数：无*/
/*输出参数: 无*/
/*返回值：空*/
/***************************************************************************/
void SplitAlarmInfo()
{
    int TypeNum=-1,i=0;

    while(RobAlarmFIFO.Fileline != RobAlarmFIFO.ReadPointer){
        RobAlarmFIFO.ReadPointer++;

        if(strcmp(RobAlarmFIFO.FileContent[RobAlarmFIFO.ReadPointer],"\n")==0){
            RobAlarmFIFO.ReadPointer++;
            TypeNum++;
            i=0;
        }

        if(strcmp(RobAlarmFIFO.FileContent[RobAlarmFIFO.ReadPointer],"END")==0)
            break;

        memset(RobAlarmSplitInfo.InfoFIFO[TypeNum][i],
               0,sizeof(RobAlarmSplitInfo.InfoFIFO[TypeNum][i]));
        strcpy(RobAlarmSplitInfo.InfoFIFO[TypeNum][i],
               RobAlarmFIFO.FileContent[RobAlarmFIFO.ReadPointer]);
        i++;
    }
    int var=0;
    for(var=0;var<512;var++){
        strcpy(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[var],RobAlarmSplitInfo.InfoFIFO[OtherType][var]);
        strcpy(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[var],RobAlarmSplitInfo.InfoFIFO[InterpolateType][var]);
        strcpy(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[var],RobAlarmSplitInfo.InfoFIFO[DecodeType][var]);
        strcpy(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[var],RobAlarmSplitInfo.InfoFIFO[IOType][var]);
        strcpy(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[var],RobAlarmSplitInfo.InfoFIFO[DriveType][var]);
    }
}

/***************************************************************************/
/*函数功能：获取报警号所对应的报警内容、说明、处理方法*/
/*输入参数：RobAlarmType:报警类型,RobAlarmNum:报警号*/
/*输出参数: 无*/
/*返回值：1获取成功,0获取失败*/
/***************************************************************************/
int ObtainAlarmContent(int RobAlarmType, int RobAlarmNum)
{
    //1、1)获取RobAlarmType所有的报警号 2)判断RobAlarmType、RobAlarmNum
    ObtainAllAlarmNum(RobAlarmType);
    if(CheckTypeAndNum(RobAlarmType,RobAlarmNum) != 1)
        return 0;

    int i=0;
    int flagNew = 1;
    switch (RobAlarmType){
        case OtherType:
            for(i=0;i<OtherALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmNum == ObtainAlarmNum(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i])){
                    do{
                        if(ObtainContent(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i],flagNew)!=NULL)
                            strcpy(RobAlarmBuffer.RobAlarmContent[flagNew],
                                    ObtainContent(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i],flagNew));
                        i++;
                        flagNew++;
                    }while(-1 == ObtainAlarmNum(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i]));
                }
            }
            break;

        case InterpolateType:
            for(i=0;i<InterpolateALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmNum == ObtainAlarmNum(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i])){
                    do{
                        if(ObtainContent(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i],flagNew)!=NULL)
                            strcpy(RobAlarmBuffer.RobAlarmContent[flagNew],
                                    ObtainContent(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i],flagNew));
                        i++;
                        flagNew++;
                    }while(-1 == ObtainAlarmNum(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i]));
                }
            }
            break;

        case DecodeType:
            for(i=0;i<DecodeALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmNum == ObtainAlarmNum(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i])){
                    do{
                        if(ObtainContent(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i],flagNew)!=NULL)
                            strcpy(RobAlarmBuffer.RobAlarmContent[flagNew],
                                    ObtainContent(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i],flagNew));
                        i++;
                        flagNew++;
                    }while(-1 == ObtainAlarmNum(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i]));
                }
            }
            break;

        case IOType:
            for(i=0;i<IOALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmNum == ObtainAlarmNum(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i])){
                    do{
                        if(ObtainContent(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i],flagNew)!=NULL){
                            strcpy(RobAlarmBuffer.RobAlarmContent[flagNew],
                                ObtainContent(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i],flagNew));
                        }
                        i++;
                        flagNew++;
                    }while(-1 == ObtainAlarmNum(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i]));
                }
            }
            break;

        case DriveType:
            for(i=0;i<DriveALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmNum == ObtainAlarmNum(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i])){
                    do{
                        if(ObtainContent(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i],flagNew)!=NULL)
                            strcpy(RobAlarmBuffer.RobAlarmContent[flagNew],
                                    ObtainContent(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i],flagNew));
                        i++;
                        flagNew++;
                    }while(-1 == ObtainAlarmNum(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i]));
                }
            }
            break;

        default:return 0;break;
    }
    return 1;
}

/***************************************************************************/
/*函数功能：检查是否有这个报警类型及报警号*/
/*输入参数：RobAlarmType:报警类型,RobAlarmNum:报警号*/
/*输出参数: 无*/
/*返回值：1:存在这个报警类型及报警号,0:不存在这个报警类型,-1:不存在这个报警号*/
/***************************************************************************/
int CheckTypeAndNum(int RobAlarmType,int RobAlarmNum)
{
    int i;
    switch (RobAlarmType) {
        case OtherType:
            for(i=0;i<RobAlarmSplitInfo.RobOtherAlarm.Num;i++){
                if(RobAlarmNum==RobAlarmSplitInfo.RobOtherAlarm.AlarmNum[i])
                    break;
                else if(i == RobAlarmSplitInfo.RobOtherAlarm.Num-1)
                    return -1;
            }
            if(RobAlarmSplitInfo.RobOtherAlarm.Num==0)
                return -1;
            break;

        case InterpolateType:
            for(i=0;i<RobAlarmSplitInfo.RobInterpolateAlarm.Num;i++){
                if(RobAlarmNum==RobAlarmSplitInfo.RobInterpolateAlarm.AlarmNum[i])
                    break;
                else if(i == RobAlarmSplitInfo.RobInterpolateAlarm.Num-1)
                    return -1;
            }
            if(RobAlarmSplitInfo.RobInterpolateAlarm.Num==0)
                return -1;
            break;

        case DecodeType:
            for(i=0;i<RobAlarmSplitInfo.RobDecodeAlarm.Num;i++){
                if(RobAlarmNum==RobAlarmSplitInfo.RobDecodeAlarm.AlarmNum[i])
                    break;
                else if(i == RobAlarmSplitInfo.RobDecodeAlarm.Num-1)
                    return -1;
            }
            if(RobAlarmSplitInfo.RobDecodeAlarm.Num==0)
                return -1;
            break;

        case IOType:
            for(i=0;i<RobAlarmSplitInfo.RobIOAlarm.Num;i++){
                if(RobAlarmNum==RobAlarmSplitInfo.RobIOAlarm.AlarmNum[i])
                    break;
                else if(i == RobAlarmSplitInfo.RobIOAlarm.Num-1)
                    return -1;
            }
            if(RobAlarmSplitInfo.RobIOAlarm.Num==0)
                return -1;
            break;

        case DriveType:
            for(i=0;i<RobAlarmSplitInfo.RobDriveAlarm.Num;i++){
                if(RobAlarmNum==RobAlarmSplitInfo.RobDriveAlarm.AlarmNum[i])
                    break;
                else if(i == RobAlarmSplitInfo.RobDriveAlarm.Num-1)
                    return -1;
            }

            if(RobAlarmSplitInfo.RobDriveAlarm.Num==0)
                return -1;
            break;

        default:return 0;break;
    }

    return 1;
}

/***************************************************************************/
/*函数功能：获取RobAlarmType类型的所有的报警号并保存在分类报警信息RobAlarmSplitInfo的相应类型的AlarmNum*/
/*输入参数：RobAlarmType:报警类型*/
/*输出参数: 无*/
/*返回值：1:存在这个报警类型及报警号,0:不存在这个报警类型,-1:不存在这个报警号*/
/***************************************************************************/
void ObtainAllAlarmNum(int RobAlarmType)
{
    int i = 0;
    switch (RobAlarmType) {
        case OtherType:
            RobAlarmSplitInfo.RobOtherAlarm.Num=0;
            for(i=0;i<OtherALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i][0] != '*'&&
                        RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i][0] != '\0'){
                    RobAlarmSplitInfo.RobOtherAlarm.AlarmNum[RobAlarmSplitInfo.RobOtherAlarm.Num] =
                            ObtainAlarmNum(RobAlarmSplitInfo.RobOtherAlarm.AlarmContent[i]);
                    RobAlarmSplitInfo.RobOtherAlarm.Num++;
                }
            }
            break;

        case InterpolateType:
            RobAlarmSplitInfo.RobInterpolateAlarm.Num=0;
            for(i=0;i<InterpolateALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i][0] != '*'&&
                        RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i][0] != '\0'){
                    RobAlarmSplitInfo.RobInterpolateAlarm.AlarmNum[RobAlarmSplitInfo.RobInterpolateAlarm.Num] =
                            ObtainAlarmNum(RobAlarmSplitInfo.RobInterpolateAlarm.AlarmContent[i]);
                    RobAlarmSplitInfo.RobInterpolateAlarm.Num++;
                }
            }
            break;

        case DecodeType:
            RobAlarmSplitInfo.RobDecodeAlarm.Num=0;
            for(i=0;i<DecodeALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i][0] != '*'&&
                        RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i][0] != '\0'){
                    RobAlarmSplitInfo.RobDecodeAlarm.AlarmNum[RobAlarmSplitInfo.RobDecodeAlarm.Num] =
                            ObtainAlarmNum(RobAlarmSplitInfo.RobDecodeAlarm.AlarmContent[i]);
                    RobAlarmSplitInfo.RobDecodeAlarm.Num++;
                }
            }
            break;

        case IOType:
            RobAlarmSplitInfo.RobIOAlarm.Num=0;
            for(i=0;i<IOALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i][0] != '*'&&
                        RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i][0] != '\0'){
                    RobAlarmSplitInfo.RobIOAlarm.AlarmNum[RobAlarmSplitInfo.RobIOAlarm.Num] =
                            ObtainAlarmNum(RobAlarmSplitInfo.RobIOAlarm.AlarmContent[i]);
                    RobAlarmSplitInfo.RobIOAlarm.Num++;
                }
            }
            break;

        case DriveType:
            RobAlarmSplitInfo.RobDriveAlarm.Num=0;
            for(i=0;i<DriveALARM_CONTENT_ROW_SIZE;i++){
                if(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i][0] != '*'&&
                        RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i][0] != '\0'){
                    RobAlarmSplitInfo.RobDriveAlarm.AlarmNum[RobAlarmSplitInfo.RobDriveAlarm.Num] =
                            ObtainAlarmNum(RobAlarmSplitInfo.RobDriveAlarm.AlarmContent[i]);
                    RobAlarmSplitInfo.RobDriveAlarm.Num++;
                }
            }
            break;
        default:break;
    }
}

/***************************************************************************/
/*函数功能：获取报警号*/
/*输入参数：content:报警内容*/
/*输出参数: 无*/
/*返回值：报警号,返回-1表示出错*/
/***************************************************************************/
int ObtainAlarmNum(char *content)
{
    if(content==NULL || *content == '\0')
        return -1;
    int len = strlen(content);
    char input[len];
    strcpy(input,content);

    char *p;
    p = strtok(input," ");

    if(strcmp(p,content)==0)    //输入的字符串没空格,如:*说明J1轴速度超出系统设置值
        return -1;
    if(atoi(p) == 0 && *p != '0')//输入的字符串有空格，但空格前不是字符串,如:*说明 J1轴速度超出系统设置值
        return -1;
    int Num = atoi(p);
    return Num;
}

/***************************************************************************/
/*函数功能：获取报警内容、说明、处理方法*/
/*输入参数：content:报警内容,flagNew=1:获取报警内容、flagNew=2:获取报警说明、flagNew=3:获取报警处理方法*/
/*输出参数: 无*/
/*返回值：返回NULL,获取错误,返回报警内容、说明、处理方法*/
/***************************************************************************/
char *ObtainContent(char *content, int flagNew)
{
    if(content==NULL || *content == '\0')
        return NULL;

    int len = strlen(content);
    char input[len];
    strcpy(input,content);
    char *p = NULL;

    switch (flagNew) {
        case 1:
            p = strtok(input," ");
            p = strtok(NULL," ");
            break;
        case 2:
            p = strtok(input,":");
            p = strtok(NULL,":");
            break;
        case 3:
            p = strtok(input,":");
            p = strtok(NULL,":");
            break;
        default:break;
    }

    char pTmp[strlen(p)];
    strcpy(pTmp,p);
    if(pTmp[strlen(p)-1]=='\n'){
        pTmp[strlen(p)-1]='\0';
        strcpy(p,pTmp);
    }
    return p;
}

/***************************************************/

/***************************************************************************/
/*函数功能：报警接口*/
/*输入参数：RobAlarmType:报警类型,RobAlarmNum:报警号*/
/*输出参数: 无*/
/*返回值：1:报警成功,0:失败*/
/***************************************************************************/
int RobAlarm(int RobAlarmType,int RobAlarmNum)
{

    //1、1)获取RobAlarmType所有的报警号 2)判断RobAlarmType、RobAlarmNum
    ObtainAllAlarmNum(RobAlarmType);
    if(CheckTypeAndNum(RobAlarmType,RobAlarmNum) != 1)
        return 0;

    RobAlarmBuffer.RobAlarmType = RobAlarmType;
    RobAlarmBuffer.RobAlarmNum = RobAlarmNum;

//    RobAlarmBuffer.RobAlarmContent[0][0] = RobAlarmBuffer.RobAlarmNum;

    /*获取报警号所对应的报警内容、说明、处理方法保存在RobAlarmBuffer.RobAlarmContent
     *1获取成功,0获取失败
     *RobAlarmNum;    报警号  RobAlarmType;   报警类型
     */
    ObtainAlarmContent(RobAlarmType, RobAlarmNum);
    //2、写入报警队列
    RobAlarmBuffer.InfoQueue[0] = (char)RobAlarmBuffer.RobAlarmNum;
//    RobAlarmBuffer.InfoQueue = NULL;
//    memset(RobAlarmBuffer.InfoQueue,0,sizeof(RobAlarmBuffer.InfoQueue));//由界面按钮清零

    return 1;
}
