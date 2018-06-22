
#define robDataBuffer_GLOBALS
#define robDataName_GLOBALS
#define quickToData_GLOBALS
#define quickToName_GLOBALS
#define DataManageFIFO_GLOBALS

#include "DataManage.h"

void DataManage_Init(DataManage_QuickToDataType *pQuickTo,DataManage_BufferType *pBuffer,
        DataManage_QuickToDataName *pQuickToName,DataManage_DataName *pDataName)
{
    pQuickTo->pQuickTo[DataManage_RobTargetType]=(ITP_RobTarget*)(pBuffer->P);
    pQuickTo->pQuickTo[DataManage_JointTargetType]=(void*)pBuffer->J;
    pQuickTo->pQuickTo[DataManage_WobjDataType]=(void*)pBuffer->W;
    pQuickTo->pQuickTo[DataManage_ToolDataType]=(void*)pBuffer->T;
    pQuickTo->pQuickTo[DataManage_ZoneDataType]=(void*)pBuffer->Z;
    pQuickTo->pQuickTo[DataManage_SpeedDataType]=(void*)pBuffer->V;

    pQuickToName->pQuickToName[DataManage_RobTargetType] = (void*)pDataName->PName;
    pQuickToName->pQuickToName[DataManage_JointTargetType] = (void*)pDataName->JName;
    pQuickToName->pQuickToName[DataManage_WobjDataType] = (void*)pDataName->WName;
    pQuickToName->pQuickToName[DataManage_ToolDataType] = (void*)pDataName->TName;
    pQuickToName->pQuickToName[DataManage_ZoneDataType] = (void*)pDataName->ZName;
    pQuickToName->pQuickToName[DataManage_SpeedDataType] = (void*)pDataName->VName;

//	int i ;
//	for(i = 0;i<20;i++){
    memset(pBuffer->P,0,sizeof(pBuffer->P));
    memset(pBuffer->J,0,sizeof(pBuffer->J));
    memset(pBuffer->W,0,sizeof(pBuffer->W));
    memset(pBuffer->T,0,sizeof(pBuffer->T));
    memset(pBuffer->Z,0,sizeof(pBuffer->Z));
    memset(pBuffer->V,0,sizeof(pBuffer->V));

    memset(pBuffer->flagP,0,sizeof(pBuffer->flagP));
    memset(pBuffer->flagJ,0,sizeof(pBuffer->flagJ));
    memset(pBuffer->flagW,0,sizeof(pBuffer->flagW));
    memset(pBuffer->flagT,0,sizeof(pBuffer->flagT));
    memset(pBuffer->flagZ,0,sizeof(pBuffer->flagZ));
    memset(pBuffer->flagV,0,sizeof(pBuffer->flagV));

    memset(pDataName->PName,0,sizeof(pDataName->PName));
    memset(pDataName->JName,0,sizeof(pDataName->JName));
    memset(pDataName->WName,0,sizeof(pDataName->WName));
    memset(pDataName->ZName,0,sizeof(pDataName->ZName));
    memset(pDataName->TName,0,sizeof(pDataName->TName));
    memset(pDataName->VName,0,sizeof(pDataName->VName));
//	}
}

//Finished by YJS

//文件操作	flagType=0表示ITP_RobTarget，1表示ITP_JointTarget，2表示ITP_WobjData…………依此类推
int DataManage_WriteFile_Item(int flagType,int flagNo,void *pData)	//将内存中的某个数据保存到文件
{
    FILE *file = NULL;
    file = fopen("Data","r+");

    if(file == NULL){
        perror("fopen fail");
        return 0;
    }

    char buf[buf_size];

    char keybuf[DataManage_DataNum][2][16]= {
            {"RobTarget\n","ENDRobTarget\n"},	//位姿坐标
            {"JointTarget\n","ENDJointTarget\n"},	//关节坐标
            {"WobjData\n","ENDWobjData\n"},	//用户坐标系
            {"ToolData\n","ENDToolData\n"},	//工具数据
            {"ZoneData\n","ENDZoneData\n"},	//指定平滑开始距离和角度
            {"SpeedData\n","ENDSpeedData\n"},	//速度数据
    };

//	char *key[] = {
//			"P","J","W","T","Z","V"
//	};

    int Lid = 0;
    char tmp[1024][256];

    ITP_RobTarget *roP = (ITP_RobTarget *)pData;
    ITP_JointTarget *roJ = (ITP_JointTarget *)pData;
    ITP_WobjData *roW = (ITP_WobjData *)pData;
    ITP_ToolData *roT = (ITP_ToolData *)pData;
    ITP_ZoneData  *roZ = (ITP_ZoneData  *)pData;
    ITP_SpeedData *roV = (ITP_SpeedData *)pData;

    while(fgets(buf,sizeof(buf),file) != NULL){//	先遍历文件，找到关键字
        Lid++;
        if(strcmp(keybuf[flagType][1],buf) == 0){
        switch(flagType){
            case DataManage_RobTargetType:
                sprintf(tmp[Lid++],"\t%s=%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n",robDataName.PName[flagNo],
                        roP->pose.trans.x,roP->pose.trans.y,roP->pose.trans.z,
                        roP->pose.rot.s,roP->pose.rot.x,roP->pose.rot.y,roP->pose.rot.z,roP->robconf.cf1,roP->robconf.cf4,roP->robconf.cf6,
                        roP->robconf.cfx,roP->extax.eax[0],roP->extax.eax[1],roP->extax.eax[2],roP->extax.eax[3],roP->extax.eax[4],roP->extax.eax[5]);
                break;
            case DataManage_JointTargetType:
                sprintf(tmp[Lid++],"\t%s=%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",robDataName.JName[flagNo],
                        roJ->robax.rax[0],roJ->robax.rax[1],roJ->robax.rax[2],roJ->robax.rax[3],roJ->robax.rax[4],roJ->robax.rax[5],
                        roJ->extax.eax[0],roJ->extax.eax[1],roJ->extax.eax[2],roJ->extax.eax[3],roJ->extax.eax[4],roJ->extax.eax[5]);
                break;
            case DataManage_WobjDataType:
                sprintf(tmp[Lid++],"\t%s=%c,%c,%s,%f,%f,%f,%f,%f,%f,%f\n",robDataName.WName[flagNo],roW->robhold,roW->ufprog,roW->ufmec,
                        roW->uframe.trans.x,roW->uframe.trans.y,roW->uframe.trans.z,
                        roW->uframe.rot.s,roW->uframe.rot.x,roW->uframe.rot.y,roW->uframe.rot.z);
                break;
            case DataManage_ToolDataType:
                sprintf(tmp[Lid++],"\t%s=%c,%f,%f,%f,%f,%f,%f,%f\n",robDataName.TName[flagNo],roT->robhold,
                        roT->tframe.trans.x,roT->tframe.trans.y,roT->tframe.trans.z,
                        roT->tframe.rot.s,roT->tframe.rot.x,roT->tframe.rot.y,roT->tframe.rot.z);
                break;
            case DataManage_ZoneDataType:
                if(roZ->finep == '0'){
                    sprintf(tmp[Lid++],"\t%s=%c,[%f,%f,%f,%f,%f,%f]\n",robDataName.ZName[flagNo],
                            roZ->finep,roZ->bgnzone.pzone_tcp,roZ->bgnzone.pzone_ori,roZ->bgnzone.pzone_eax,roZ->bgnzone.zone_ori,
                            roZ->bgnzone.zone_leax,roZ->bgnzone.zone_reax);
                    }else if(roZ->finep == '1'){
                        sprintf(tmp[Lid++],"\t%s=%c,[%c,%c,%f,%f,%f,%f,%f,%f]\n",robDataName.ZName[flagNo],
                                roZ->finep,roZ->inpos.stoppoint,roZ->inpos.progsynch,roZ->inpos.inpos.position,roZ->inpos.inpos.speed,
                                roZ->inpos.inpos.mintime,roZ->inpos.inpos.maxtime,roZ->inpos.stoptime,roZ->inpos.followtime);
                    }
                break;
            case DataManage_SpeedDataType:
                sprintf(tmp[Lid++],"\t%s=%f,%f,%f,%f,%f\n",robDataName.VName[flagNo],roV->time,roV->v_tcp,roV->v_ort,
                        roV->v_leax,roV->v_reax);
                break;

            }
        }

        strcpy(tmp[Lid],buf);
        memset(buf,0,sizeof(buf));
    }

    int MaxLine=Lid;
    rewind(file);

    for(Lid=1 ;	Lid <= MaxLine;	Lid++)
    {
        fputs(tmp[Lid],file);
    }

    fclose(file);

    return 0;
}

int DataManage_ReadFile(DataManageFile *pFile)	//将文件中的数据加载到内存		0 加载失败	1 加载成功
{
    ReadFile_Fifo FIFO;	///读文件缓冲区

    FILE *file = NULL;
    file = fopen(DataManage_FileName,"a+");

    if(file == NULL){
        perror("fopen fail");
        return 0;
    }

    ReadFile_Fifo FIFO_tmp;
    FIFO.write_pointer = 0;
    FIFO_tmp.write_pointer = 0;
    while(fgets(FIFO.file_content[FIFO.write_pointer++],
                sizeof(FIFO.file_content[FIFO.write_pointer]),file)!=NULL){

        memset(FIFO_tmp.file_content[FIFO_tmp.write_pointer],0,
                sizeof(FIFO_tmp.file_content[FIFO_tmp.write_pointer]));

        read(*pFile,FIFO_tmp.file_content[FIFO_tmp.write_pointer],1+strlen(FIFO.file_content[FIFO.write_pointer-1]));

        FIFO_tmp.write_pointer++;
    }

    FIFO.lineNum = FIFO.write_pointer;

    fclose(file);

    char DataType[DataManage_DataNum][2][16]= {
            {"RobTarget\n","ENDRobTarget\n"},	//位姿坐标
            {"JointTarget\n","ENDJointTarget\n"},	//关节坐标
            {"WobjData\n","ENDWobjData\n"},	//用户坐标系
            {"ToolData\n","ENDToolData\n"},	//工具数据
            {"ZoneData\n","ENDZoneData\n"},	//指定平滑开始距离和角度
            {"SpeedData\n","ENDSpeedData\n"},	//速度数据
    };

    int var =0;
    FIFO.read_pointer = 0;

    char ufmec[DataManage_WobjDataNum][16];
    memset(ufmec,0,sizeof(ufmec));
    char *robufmec;

    for(var = 0 ; var < DataManage_DataNum ; var++){
        FIFO.read_pointer++;
        int index = 0;
        do{
            switch(var){
                case DataManage_RobTargetType://RobTarget拆分split_RobTarget
                    if(index>=DataManage_RobTargetNum)
                        return 0;
                    robDataBuffer.P[index] = split_RobTarget(index,FIFO.file_content[FIFO.read_pointer]);
                    robDataBuffer.flagP[index] = '1';
                break;

                case DataManage_JointTargetType://JointTarget拆分
                    if(index>=DataManage_JointTargetNum)
                        return 0;
                    robDataBuffer.J[index] = split_JointTarget(index,FIFO.file_content[FIFO.read_pointer]);
                    robDataBuffer.flagJ[index] = '1';
                break;

                case DataManage_WobjDataType://WobjData拆分
                    if(index>=DataManage_WobjDataNum)
                        return 0;
                    robDataBuffer.W[index] = split_WobjData(index,&robufmec,FIFO.file_content[FIFO.read_pointer]);
                    strcpy(ufmec[index],robufmec);
                    robDataBuffer.W[index].ufmec = ufmec[index];
                    robDataBuffer.flagW[index] = '1';
                break;

                case DataManage_ToolDataType://ToolData拆分
                    if(index>=DataManage_ToolDataNum)
                        return 0;
                    robDataBuffer.T[index] = split_ToolData(index,FIFO.file_content[FIFO.read_pointer]);
                    robDataBuffer.flagT[index] = '1';
                break;

                case DataManage_ZoneDataType://ZoneData拆分
                    if(index>=DataManage_ZoneDataNum)
                        return 0;
                    robDataBuffer.Z[index] = split_ZoneData(index,FIFO.file_content[FIFO.read_pointer]);
                    robDataBuffer.flagZ[index] = '1';
                break;

                case DataManage_SpeedDataType://SpeedData拆分
                    if(index>=DataManage_SpeedDataNum)
                        return 0;
                    robDataBuffer.V[index] = split_SpeedData(index,FIFO.file_content[FIFO.read_pointer]);
                    robDataBuffer.flagV[index] = '1';
                break;

                default:break;
            }

            index++;
            FIFO.read_pointer++;

        }while(strcmp(FIFO.file_content[FIFO.read_pointer], DataType[var][0]) != 0
                &&strcmp(FIFO.file_content[FIFO.read_pointer], DataType[var][1]) != 0
                &&(strcmp(FIFO.file_content[FIFO.read_pointer], "\n") != 0)
                &&FIFO.read_pointer<FIFO.lineNum);

        FIFO.read_pointer++;
        FIFO.read_pointer++;
    }
    return 1;
}

int DataManage_WriteFile(DataManageFile *pFile)	//将内存所有数据保存到文件	0 保存失败	1 保存成功
{
    int fd = -1;

    fd = open(DataManage_FileName,O_CREAT|O_RDWR|O_TRUNC,0644);

    if(fd == -1){
        perror("open fail:");
        exit(1) ;
    }

    *pFile = fd;

    char buf[DataManage_DataNum][2][16]= {
            {"RobTarget\n","ENDRobTarget\n"},	//位姿坐标
            {"JointTarget\n","ENDJointTarget\n"},	//关节坐标
            {"WobjData\n","ENDWobjData\n"},	//用户坐标系
            {"ToolData\n","ENDToolData\n"},	//工具数据
            {"ZoneData\n","ENDZoneData\n"},	//指定平滑开始距离和角度
            {"SpeedData\n","ENDSpeedData\n"},	//速度数据
    };

    char tmp[tmp_size] ;

    int num = 0;

//    rewind(file);
    lseek(fd,0,SEEK_SET);
    int i = 0;
    for(i=0;i<DataManage_DataNum;i++){
        switch (i) {
            case DataManage_RobTargetType://写位姿坐标到文件
                write(*pFile, buf[0][0],strlen(buf[0][0]));
                for(num = 0; num<DataManage_RobTargetNum;num++){
                    if(robDataBuffer.flagP[num] == '1'){
                        memset(tmp,0,strlen(tmp));
                        sprintf(tmp,"\t%s=%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n",robDataName.PName[num],
                                robDataBuffer.P[num].pose.trans.x,robDataBuffer.P[num].pose.trans.y,robDataBuffer.P[num].pose.trans.z,
                                robDataBuffer.P[num].pose.rot.s,robDataBuffer.P[num].pose.rot.x,robDataBuffer.P[num].pose.rot.y,robDataBuffer.P[num].pose.rot.z,
                                robDataBuffer.P[num].robconf.cf1,robDataBuffer.P[num].robconf.cf4,robDataBuffer.P[num].robconf.cf6,robDataBuffer.P[num].robconf.cfx,
                                robDataBuffer.P[num].extax.eax[0],robDataBuffer.P[num].extax.eax[1],robDataBuffer.P[num].extax.eax[2],
                                robDataBuffer.P[num].extax.eax[3],robDataBuffer.P[num].extax.eax[4],robDataBuffer.P[num].extax.eax[5]);
                        write(*pFile, tmp,strlen(tmp));
                        memset(tmp,0,strlen(tmp));
                    }
                }
                write(*pFile, buf[0][1],strlen(buf[0][1]));//写位姿坐标到文件完成
                write(*pFile,"\n",strlen("\n"));
                break;
            case DataManage_JointTargetType://写关节坐标到文件
                write(*pFile, buf[1][0],strlen(buf[1][0]));
                for(num = 0; num<DataManage_JointTargetNum;num++){
                    memset(tmp,0,sizeof(tmp));
                    if(robDataBuffer.flagJ[num] == '1'){
                        memset(tmp,0,sizeof(tmp));
                        sprintf(tmp,"\t%s=%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",robDataName.JName[num],
                                robDataBuffer.J[num].robax.rax[0],robDataBuffer.J[num].robax.rax[1],robDataBuffer.J[num].robax.rax[2],
                                robDataBuffer.J[num].robax.rax[3],robDataBuffer.J[num].robax.rax[4],robDataBuffer.J[num].robax.rax[5],
                                robDataBuffer.J[num].extax.eax[0],robDataBuffer.J[num].extax.eax[1],robDataBuffer.J[num].extax.eax[2],
                                robDataBuffer.J[num].extax.eax[3],robDataBuffer.J[num].extax.eax[4],robDataBuffer.J[num].extax.eax[5]);
                        write(*pFile, tmp,strlen(tmp));
                        memset(tmp,0,sizeof(tmp));
                    }
                }
                write(*pFile, buf[1][1],strlen(buf[1][1]));//写关节坐标到文件完成
                write(*pFile,"\n",strlen("\n"));
                break;
            case DataManage_WobjDataType://写用户坐标到文件
                write(*pFile, buf[2][0],strlen(buf[2][0]));
                for(num =0; num<DataManage_WobjDataNum;num++){
                    if(robDataBuffer.flagW[num] == '1'){
                        memset(tmp,0,sizeof(tmp));
                        sprintf(tmp,"\t%s=%c,%c,%s,%f,%f,%f,%f,%f,%f,%f\n",robDataName.WName[num],robDataBuffer.W[num].robhold,robDataBuffer.W[num].ufprog,
                                robDataBuffer.W[num].ufmec,robDataBuffer.W[num].uframe.trans.x,robDataBuffer.W[num].uframe.trans.y,
                                robDataBuffer.W[num].uframe.trans.z,robDataBuffer.W[num].uframe.rot.s,robDataBuffer.W[num].uframe.rot.x,
                                robDataBuffer.W[num].uframe.rot.y,robDataBuffer.W[num].uframe.rot.z);
                        write(*pFile, tmp,strlen(tmp));
                    }
                }
                write(*pFile, buf[2][1],strlen(buf[2][1]));//写用户坐标到文件完成
                write(*pFile,"\n",strlen("\n"));
                break;
            case DataManage_ToolDataType://写工具数据到文件
                write(*pFile, buf[3][0],strlen(buf[3][0]));
                for(num =0; num<DataManage_ToolDataNum;num++){
                    if(robDataBuffer.flagT[num] == '1'){
                        memset(tmp,0,sizeof(tmp));
                        sprintf(tmp,"\t%s=%c,%f,%f,%f,%f,%f,%f,%f\n",robDataName.TName[num],robDataBuffer.T[num].robhold,
                                robDataBuffer.T[num].tframe.trans.x,robDataBuffer.T[num].tframe.trans.y,robDataBuffer.T[num].tframe.trans.z,robDataBuffer.T[num].tframe.rot.s,
                                robDataBuffer.T[num].tframe.rot.x,robDataBuffer.T[num].tframe.rot.y,robDataBuffer.T[num].tframe.rot.z);
                        write(*pFile, tmp,strlen(tmp));
                    }
                }
                write(*pFile, buf[3][1],strlen(buf[3][1]));//写工具数据到文件完成
                write(*pFile,"\n",strlen("\n"));
                break;
            case DataManage_ZoneDataType://写指定平滑开始距离和角度到文件
                write(*pFile, buf[4][0],strlen(buf[4][0]));
                for(num=0;num<DataManage_ZoneDataNum;num++){
                    if(robDataBuffer.flagZ[num] == '1'){
                        memset(tmp,0,sizeof(tmp));
                        if(robDataBuffer.Z[num].finep == 1){
                            sprintf(tmp,"\t%s=%d,[%d,%d,%f,%f,%f,%f,%f,%f]\n",robDataName.ZName[num],robDataBuffer.Z[num].finep,
                                    robDataBuffer.Z[num].inpos.stoppoint,robDataBuffer.Z[num].inpos.progsynch,
                                    robDataBuffer.Z[num].inpos.inpos.position,robDataBuffer.Z[num].inpos.inpos.speed,
                                    robDataBuffer.Z[num].inpos.inpos.mintime,robDataBuffer.Z[num].inpos.inpos.maxtime,
                                    robDataBuffer.Z[num].inpos.stoptime,robDataBuffer.Z[num].inpos.followtime);
                        }
                        else if(robDataBuffer.Z[num].finep == 0){
                            sprintf(tmp,"\t%s=%d,[%f,%f,%f,%f,%f,%f]\n",robDataName.ZName[num],robDataBuffer.Z[num].finep,
                                    robDataBuffer.Z[num].bgnzone.pzone_tcp,robDataBuffer.Z[num].bgnzone.pzone_ori,robDataBuffer.Z[num].bgnzone.pzone_eax,
                                    robDataBuffer.Z[num].bgnzone.zone_ori,robDataBuffer.Z[num].bgnzone.zone_leax,robDataBuffer.Z[num].bgnzone.zone_reax);
                        }
                        write(*pFile, tmp,strlen(tmp));
                    }
                }
                write(*pFile, buf[4][1],strlen(buf[4][1]));//写指定平滑开始距离和角度到文件完成
                write(*pFile,"\n",strlen("\n"));
                break;
            case DataManage_SpeedDataType://写速度数据到文件
                write(*pFile, buf[5][0],strlen(buf[5][0]));
                for(num =0; num<DataManage_SpeedDataNum;num++){
                    if(robDataBuffer.flagV[num] == '1'){
                        memset(tmp,0,sizeof(tmp));
                        sprintf(tmp,"\t%s=%f,%f,%f,%f,%f\n",robDataName.VName[num],robDataBuffer.V[num].time,
                                robDataBuffer.V[num].v_tcp,robDataBuffer.V[num].v_ort,robDataBuffer.V[num].v_leax,robDataBuffer.V[num].v_reax);
                        write(*pFile, tmp,strlen(tmp));
                    }
                }
                write(*pFile, buf[5][1],strlen(buf[5][1]));//写速度数据到文件完成
                write(*pFile,"\n",strlen("\n"));
                break;
            default:
                break;
        }
    }
    close(fd);
    return 1;
}

int DataManage_AlterFile(int flagType,int flagNo,void *pData)//文件中修改数据
{
    ITP_RobTarget *roP ;
    ITP_JointTarget *roJ ;
    ITP_WobjData *roW ;
    ITP_ToolData *roT ;
    ITP_ZoneData  *roZ ;
    ITP_SpeedData *roV ;

    ReadFile_Fifo FIFO;

    FILE *file = NULL;
    file = fopen("Data","r+");

    if(file == NULL){
        perror("fopen fail");
        return 0;
    }

    char _Dest[256] ;

    char *key[] = {
            "P","J","W","T","Z","V"
    };

    FIFO.write_pointer = 0 ;

    while(fgets(FIFO.file_content[FIFO.write_pointer],
                sizeof(FIFO.file_content[FIFO.write_pointer]),file) != NULL){//	先遍历文件，找到关键字
        if(Obtain_Snum(FIFO.file_content[FIFO.write_pointer]) == flagNo){
            switch (flagType) {
                case DataManage_RobTargetType:
                    roP = (ITP_RobTarget *)pData;
                    sprintf(_Dest,"\t%s%d=%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n",key[flagType],flagNo,
                            roP->pose.trans.x,roP->pose.trans.y,roP->pose.trans.z,
                            roP->pose.rot.s,roP->pose.rot.x,roP->pose.rot.y,roP->pose.rot.z,roP->robconf.cf1,roP->robconf.cf4,roP->robconf.cf6,
                            roP->robconf.cfx,roP->extax.eax[0],roP->extax.eax[1],roP->extax.eax[2],roP->extax.eax[3],roP->extax.eax[4],roP->extax.eax[5]);
                    strcpy(FIFO.file_content[FIFO.write_pointer],_Dest);
                    break;

                case DataManage_JointTargetType:
                    roJ = (ITP_JointTarget *)pData;
                    sprintf(_Dest,"\t%s%d=%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",key[flagType],flagNo,
                            roJ->robax.rax[0],roJ->robax.rax[1],roJ->robax.rax[2],roJ->robax.rax[3],roJ->robax.rax[4],roJ->robax.rax[5],
                            roJ->extax.eax[0],roJ->extax.eax[1],roJ->extax.eax[2],roJ->extax.eax[3],roJ->extax.eax[4],roJ->extax.eax[5]);
                    strcpy(FIFO.file_content[FIFO.write_pointer],_Dest);
                    break;

                case DataManage_WobjDataType:
                    roW = (ITP_WobjData *)pData;
                    sprintf(_Dest,"\t%s%d=%c,%c,%s,%f,%f,%f,%f,%f,%f,%f\n",key[flagType],flagNo,roW->robhold,roW->ufprog,roW->ufmec,
                            roW->uframe.trans.x,roW->uframe.trans.y,roW->uframe.trans.z,
                            roW->uframe.rot.s,roW->uframe.rot.x,roW->uframe.rot.y,roW->uframe.rot.z);
                    strcpy(FIFO.file_content[FIFO.write_pointer],_Dest);
                    break;

                case DataManage_ToolDataType:
                    roT = (ITP_ToolData *)pData;
                    sprintf(_Dest,"\t%s%d=%c,%f,%f,%f,%f,%f,%f,%f\n",key[flagType],flagNo,roT->robhold,
                            roT->tframe.trans.x,roT->tframe.trans.y,roT->tframe.trans.z,
                            roT->tframe.rot.s,roT->tframe.rot.x,roT->tframe.rot.y,roT->tframe.rot.z);
                    strcpy(FIFO.file_content[FIFO.write_pointer],_Dest);
                    break;

                case DataManage_ZoneDataType:
                    roZ = (ITP_ZoneData *)pData;
                    if(roZ->finep == '0'){
                        sprintf(_Dest,"\t%s%d=%c,[%f,%f,%f,%f,%f,%f]\n",key[flagType],flagNo,
                                roZ->finep,roZ->bgnzone.pzone_tcp,roZ->bgnzone.pzone_ori,roZ->bgnzone.pzone_eax,roZ->bgnzone.zone_ori,
                                roZ->bgnzone.zone_leax,roZ->bgnzone.zone_reax);
                        }else if(roZ->finep == '1'){
                            sprintf(_Dest,"\t%s%d=%c,[%c,%c,%f,%f,%f,%f,%f,%f]\n",key[flagType],flagNo,
                                    roZ->finep,roZ->inpos.stoppoint,roZ->inpos.progsynch,roZ->inpos.inpos.position,roZ->inpos.inpos.speed,
                                    roZ->inpos.inpos.mintime,roZ->inpos.inpos.maxtime,roZ->inpos.stoptime,roZ->inpos.followtime);
                        }
                    strcpy(FIFO.file_content[FIFO.write_pointer],_Dest);
                    break;

                case DataManage_SpeedDataType:
                    roV = (ITP_SpeedData *)pData;
                    sprintf(_Dest,"\t%s%d=%f,%f,%f,%f,%f\n",key[flagType],flagNo,roV->time,roV->v_tcp,roV->v_ort,
                            roV->v_leax,roV->v_reax);
                    strcpy(FIFO.file_content[FIFO.write_pointer],_Dest);
                    break;

                default:
                    break;
            }
        }
        FIFO.write_pointer++;
    }

    FIFO.lineNum = FIFO.write_pointer;
    FIFO.read_pointer = 0;

    rewind(file);
    while(FIFO.read_pointer!= FIFO.lineNum){
        fputs(FIFO.file_content[FIFO.read_pointer++],file);
    }

    fclose(file);

    return 0;
}

//内存操作 //改  名字也要删除  全改吧
int DataManage_Delete(DataManage_BufferType *pBuffer,int flagType,int flagNo)	//内存中删除数据
{
//	ITP_RobTarget P ;	//位姿坐标
//	ITP_JointTarget J ;	//位姿坐标
//	ITP_WobjData W ;	//用户坐标系
//	ITP_ToolData T ;	//用户坐标系
//	ITP_ZoneData Z ;	//指定平滑开始距离和角度
//	ITP_SpeedData V ;	//速度数据
//
//	switch(flagType){
//        case DataManage_RobTargetType:pBuffer->P[flagNo] = P;	pBuffer->flagP[flagNo] = '0';
//			break;
//        case DataManage_JointTargetType:pBuffer->J[flagNo] = J;	pBuffer->flagJ[flagNo] = '0';
//			break;
//        case DataManage_WobjDataType:pBuffer->W[flagNo] = W;	pBuffer->flagW[flagNo] = '0';
//			break;
//        case DataManage_ToolDataType:pBuffer->T[flagNo] = T;	pBuffer->flagT[flagNo] = '0';
//			break;
//        case DataManage_ZoneDataType:pBuffer->Z[flagNo] = Z;	pBuffer->flagZ[flagNo] = '0';
//			break;
//        case DataManage_SpeedDataType:	pBuffer->V[flagNo] = V;	pBuffer->flagV[flagNo] = '0';
//			break;
//	}

    return 0;
}

int DataManage_Add(DataManage_BufferType *pBuffer,DataManage_DataName *pDataName,int flagType,
        void *pData,char *DataName)	//内存中添加数据
{
    ITP_RobTarget *P = (ITP_RobTarget *)pData;
    ITP_JointTarget *J = (ITP_JointTarget *)pData;
    ITP_WobjData *W = (ITP_WobjData *)pData;
    ITP_ToolData *T = (ITP_ToolData *)pData;
    ITP_ZoneData  *Z = (ITP_ZoneData  *)pData;
    ITP_SpeedData *V = (ITP_SpeedData *)pData;

    switch(flagType){
        case DataManage_RobTargetType:pBuffer->P[pDataName->PNum] = *P;	pBuffer->flagP[pDataName->PNum] = '1';
            strcpy(pDataName->PName[pDataName->PNum],DataName); pDataName->PNum++;
            break;
        case DataManage_JointTargetType:pBuffer->J[pDataName->JNum] = *J;	pBuffer->flagJ[pDataName->JNum] = '1';
            strcpy(pDataName->JName[pDataName->JNum],DataName); pDataName->JNum++;
            break;
        case DataManage_WobjDataType:pBuffer->W[pDataName->WNum] = *W;	pBuffer->flagW[pDataName->WNum] = '1';
            strcpy(pDataName->WName[pDataName->WNum],DataName); pDataName->WNum++;
            break;
        case DataManage_ToolDataType:pBuffer->T[pDataName->TNum] = *T;	pBuffer->flagT[pDataName->TNum] = '1';
            strcpy(pDataName->TName[pDataName->TNum],DataName); pDataName->TNum++;
            break;
        case DataManage_ZoneDataType:pBuffer->Z[pDataName->ZNum] = *Z;	pBuffer->flagZ[pDataName->ZNum] = '1';
            strcpy(pDataName->ZName[pDataName->ZNum],DataName); pDataName->ZNum++;
            break;
        case DataManage_SpeedDataType:	pBuffer->V[pDataName->VNum] = *V;	pBuffer->flagV[pDataName->VNum] = '1';
            strcpy(pDataName->VName[pDataName->VNum],DataName); pDataName->VNum++;
            break;
    }

    return 0;
}

int DataManage_Alter(DataManage_BufferType *pBuffer,int flagType,int flagNo,void *pData)	//内存中修改数据
{
    ITP_RobTarget *roP = (ITP_RobTarget *)pData;
    ITP_JointTarget *roJ = (ITP_JointTarget *)pData;
    ITP_WobjData *roW = (ITP_WobjData *)pData;
    ITP_ToolData *roT = (ITP_ToolData *)pData;
    ITP_ZoneData  *roZ = (ITP_ZoneData  *)pData;
    ITP_SpeedData *roV = (ITP_SpeedData *)pData;

    switch(flagType){
        case DataManage_RobTargetType:
            pBuffer->P[flagNo].euler = roP->euler;
            pBuffer->P[flagNo].extax = roP->extax;
            pBuffer->P[flagNo].pose.rot = roP->pose.rot;
            pBuffer->P[flagNo].robconf = roP->robconf;
            pBuffer->P[flagNo].pose.trans = roP->pose.trans;
            break;
        case DataManage_JointTargetType:
            pBuffer->J[flagNo].extax = roJ->extax;
            pBuffer->J[flagNo].robax = roJ->robax;
            break;
        case DataManage_WobjDataType:
            pBuffer->W[flagNo].robhold = roW->robhold;
            pBuffer->W[flagNo].ufprog = roW->ufprog ;
            pBuffer->W[flagNo].uframe = roW->uframe;
            pBuffer->W[flagNo].ufmec = roW->ufmec;
            break;
        case DataManage_ToolDataType:
            pBuffer->T[flagNo].robhold = roT->robhold ;
            pBuffer->T[flagNo].tframe = roT->tframe ;
            pBuffer->T[flagNo].tload = roT->tload ;
            break;
        case DataManage_ZoneDataType:
            pBuffer->Z[flagNo].bgnzone = roZ->bgnzone ;
            pBuffer->Z[flagNo].finep = roZ->finep ;
            pBuffer->Z[flagNo].inpos = roZ->inpos ;
            break;
        case DataManage_SpeedDataType:
            pBuffer->V[flagNo].time = roV->time ;
            pBuffer->V[flagNo].v_leax = roV->v_leax ;
            pBuffer->V[flagNo].v_ort = roV->v_ort ;
            pBuffer->V[flagNo].v_reax = roV->v_reax ;
            pBuffer->V[flagNo].v_tcp = roV->v_tcp ;
            break;
    }

    return 0;
}

int DataManage_Clear(DataManage_BufferType *pBuffer)	//清理内存数据
{
//	int i ;
//	for(i = 0;i<20;i++){
    memset(pBuffer->P,0,sizeof(pBuffer->P));
    memset(pBuffer->J,0,sizeof(pBuffer->J));
    memset(pBuffer->W,0,sizeof(pBuffer->W));
    memset(pBuffer->T,0,sizeof(pBuffer->T));
    memset(pBuffer->Z,0,sizeof(pBuffer->Z));
    memset(pBuffer->V,0,sizeof(pBuffer->V));

    memset(pBuffer->flagP,0,sizeof(pBuffer->flagP));
    memset(pBuffer->flagJ,0,sizeof(pBuffer->flagJ));
    memset(pBuffer->flagW,0,sizeof(pBuffer->flagW));
    memset(pBuffer->flagT,0,sizeof(pBuffer->flagT));
    memset(pBuffer->flagZ,0,sizeof(pBuffer->flagZ));
    memset(pBuffer->flagV,0,sizeof(pBuffer->flagV));
//	}

    return 0;
}

//返回-1表示错误
int Obtain_Snum(char *s)		//获取序号
{
    if(s==NULL)
        return -1;
    char s_tmp[16],tmp[16] ;//256改

    memset(s_tmp,0,sizeof(s_tmp));
    memset(tmp,0,sizeof(tmp));

    strcpy(s_tmp,s);	//保存s
    int i=0,index=0;

    int len = strlen(s_tmp);
    for(i =0;i<len;i++){
        if(!(('Z'-s_tmp[0]>=0&&s_tmp[0]-'A'>=0)||('z'-s_tmp[0]>=0&&s_tmp[0]-'a'>=0)))
                //名字开头必须是字母
            return -1;

        if(!(('Z'-s_tmp[i]>=0&&s_tmp[i]-'A'>=0)||('z'-s_tmp[i]>0&&s_tmp[i]-'a'>=0)||
                ('9'-s_tmp[i]>=0&&s_tmp[i]-'0'>=0)))//只能是字母或数字
            return -1;

        if(s_tmp[i]-'0'>=0&&'9'-s_tmp[i]>=0)//获取数字
            tmp[index++] = s_tmp[i];
    }
//
//	int tmplen = strlen(tmp);
//	if(tmp[tmplen] == '\n')	//去掉\n
//		tmp[tmplen] = '\0';

    index = atoi(tmp);

    return index;
}

char *Obtain_DataName(char *s)//获取变量名
{
    if(s == NULL)
        return NULL;

    char s_tmp[256] ;
    memset(s_tmp,0,sizeof(s_tmp));
    strcat(s_tmp,s);	//保存s

    char *DataName = NULL;

    int i = 0;
    for(i=0;i<strlen(s_tmp);i++){
        s_tmp[i] = s_tmp[i+1];//去掉\t
    }

    DataName = strtok(s_tmp,"=");

    return DataName;
}

ITP_RobTarget split_RobTarget(int index,char *s)
{
    ITP_RobTarget roP;//位姿坐标

    strcpy(robDataName.PName[index] , Obtain_DataName(s));//得到变量名
    robDataName.PNum = index+1;

    //等号左边去掉
    char *p; 		//保存等号右边
    p = strtok(s, "=");
    p = strtok(NULL, "=");

    int i ;
    int len = strlen(p);

    char tmp[tmp_size];		//保存逗号之间的数据
    memset(tmp,0,sizeof(tmp));

    double tmp_double[32];
    memset(tmp_double,0,sizeof(tmp_double));

    int tmp_var=0,tmp_double_var = 0;
    char *endptr;

    for(i=0;i<len;i++){

        tmp[tmp_var++] = *(p++);

        if(*p==','||*p=='\n'){
            tmp_double[tmp_double_var++] = strtod(tmp,&endptr);

            p++;
            memset(tmp,0,sizeof(tmp));
            tmp_var=0;
        }
    }

    roP.pose.trans.x = tmp_double[0];
    roP.pose.trans.y = tmp_double[1];
    roP.pose.trans.z = tmp_double[2];

    roP.pose.rot.s = tmp_double[3];
    roP.pose.rot.x = tmp_double[4];
    roP.pose.rot.y = tmp_double[5];
    roP.pose.rot.z = tmp_double[6];

    roP.robconf.cf1 = tmp_double[7];
    roP.robconf.cf4 = tmp_double[8];
    roP.robconf.cf6 = tmp_double[9];
    roP.robconf.cfx = tmp_double[10];

    roP.extax.eax[0] = tmp_double[11];
    roP.extax.eax[1] = tmp_double[12];
    roP.extax.eax[2] = tmp_double[13];
    roP.extax.eax[3] = tmp_double[14];
    roP.extax.eax[4] = tmp_double[15];
    roP.extax.eax[5] = tmp_double[16];

    return roP;
}

ITP_JointTarget split_JointTarget(int index,char *s)
{
    ITP_JointTarget roJ;

    strcpy(robDataName.JName[index] , Obtain_DataName(s));//得到变量名
    robDataName.JNum = index+1;

    //等号左边去掉
    char *p; 		//保存等号右边
    p = strtok(s, "=");
    p = strtok(NULL, "=");

    int i ;
    int len = strlen(p);

    char tmp[32];
    memset(tmp,0,sizeof(tmp));

    double tmp_double[16];
    memset(tmp_double,0,sizeof(tmp_double));

    int tmp_var=0,tmp_double_var = 0;
    char *endptr;

    for(i=0;i<len;i++){

        tmp[tmp_var++] = *(p++);

        if(*p==','||*p=='\n'){
            tmp_double[tmp_double_var++] = strtod(tmp,&endptr);

            p++;
            memset(tmp,0,sizeof(tmp));
            tmp_var=0;
        }
    }

    roJ.robax.rax[0] = tmp_double[0];
    roJ.robax.rax[1] = tmp_double[1];
    roJ.robax.rax[2] = tmp_double[2];
    roJ.robax.rax[3] = tmp_double[3];
    roJ.robax.rax[4] = tmp_double[4];
    roJ.robax.rax[5] = tmp_double[5];

    roJ.extax.eax[0] = tmp_double[6];
    roJ.extax.eax[1] = tmp_double[7];
    roJ.extax.eax[2] = tmp_double[8];
    roJ.extax.eax[3] = tmp_double[9];
    roJ.extax.eax[4] = tmp_double[10];
    roJ.extax.eax[5] = tmp_double[11];

    return roJ;
}

ITP_WobjData split_WobjData(int index,char **ch,char *s)
{
    ITP_WobjData roW;
    roW.ufmec = NULL; //(char*)malloc(sizeof(char*));

    strcpy(robDataName.WName[index] , Obtain_DataName(s));//得到变量名
    robDataName.WNum = index+1;

    //等号左边去掉
    char *WobjData_r = NULL; 		//保存等号右边
    WobjData_r = strtok(s, "=");
    WobjData_r = strtok(NULL, "=");

    char Backup[32];
    memset(Backup,0,sizeof(Backup));

    double WobjData_double[16];
    memset(WobjData_double,0,sizeof(WobjData_double));

    int tmp_var=0,tmp_double_var = 0;
    char *WobjData_endptr = NULL;
    int var =0;

    char ufmec[32];
    memset(ufmec,0,sizeof(ufmec));

    while(*WobjData_r!='\0'){
        if(*WobjData_r==','||*WobjData_r=='\n'){
            if(tmp_double_var == 0){
                roW.robhold = *Backup;
            }
            else if(tmp_double_var == 1){
                roW.ufprog = *Backup;
            }
            else if(tmp_double_var == 2){
                strcpy(ufmec,Backup);
                roW.ufmec= ufmec;
            }else
                WobjData_double[var++] = strtod(Backup,&WobjData_endptr);

            tmp_double_var++;
            WobjData_r++;
            memset(Backup,0,sizeof(Backup));
            tmp_var=0;
        }else
            Backup[tmp_var++] = *(WobjData_r++);
    }

    roW.uframe.trans.x= WobjData_double[0];
    roW.uframe.trans.y = WobjData_double[1];
    roW.uframe.trans.z = WobjData_double[2];

    roW.uframe.rot.s = WobjData_double[3];
    roW.uframe.rot.x = WobjData_double[4];
    roW.uframe.rot.y = WobjData_double[5];
    roW.uframe.rot.z = WobjData_double[6];

    *ch = roW.ufmec;

    return roW;
}

ITP_ToolData split_ToolData(int index,char *s)
{
    ITP_ToolData roT;

    strcpy(robDataName.TName[index] , Obtain_DataName(s));//得到变量名
    robDataName.TNum = index+1;

    //等号左边去掉
    char *p; 		//保存等号右边
    p = strtok(s, "=");
    p = strtok(NULL, "=");

    int i ;
    int len = strlen(p);

    char tmp[32];
    memset(tmp,0,sizeof(tmp));

    double tmp_double[16];
    memset(tmp_double,0,sizeof(tmp_double));

    int tmp_var=0,tmp_double_var = 0;
    char *endptr;

    int var = 0;

    for(i=0;i<len;i++){

        tmp[tmp_var++] = *(p++);

        if(*p==','||*p=='\n'){
            if(var==0)
                roT.robhold = *tmp;
            else
                tmp_double[tmp_double_var++] = strtod(tmp,&endptr);

            p++;
            var++;
            memset(tmp,0,sizeof(tmp));
            tmp_var=0;
        }

    }
    roT.tframe.trans.x = tmp_double[0];
    roT.tframe.trans.y = tmp_double[1];
    roT.tframe.trans.z = tmp_double[2];

    roT.tframe.rot.s = tmp_double[3];
    roT.tframe.rot.x = tmp_double[4];
    roT.tframe.rot.y = tmp_double[5];
    roT.tframe.rot.z = tmp_double[6];

    return roT;
}

ITP_ZoneData split_ZoneData(int index,char *s)
{
    ITP_ZoneData roZ;

    strcpy(robDataName.ZName[index] , Obtain_DataName(s));//得到变量名
    robDataName.ZNum = index+1;

    char *p; 		//保存等号右边
    p = strtok(s, "=");
    p = strtok(NULL, "=");

    int i ;
    int len = strlen(p);

    char tmp[32];
    memset(tmp,0,sizeof(tmp));

    double tmp_double[16];
    memset(tmp_double,0,sizeof(tmp_double));

    int tmp_var=0,tmp_double_var = 0;
    char *endptr;

    int tmplen;
    for(i=0;i<len;i++){
        tmp[tmp_var++] = *(p++);
        if(*p==','||*p=='\n'){
            if(tmp[0] == '['){
                for(tmplen = 0;tmplen < strlen(tmp);tmplen++){
                    tmp[tmplen] = tmp[tmplen+1];
                }
            }

            if(tmp[strlen(tmp)-1] == ']'){
                tmp[strlen(tmp)-1] = '\0';
            }

            tmp_double[tmp_double_var++] = strtod(tmp,&endptr);

            p++;
            memset(tmp,0,sizeof(tmp));
            tmp_var=0;
        }
    }

    roZ.finep = (int)tmp_double[0];
    if(roZ.finep == 0){
        roZ.bgnzone.pzone_tcp = tmp_double[1];
        roZ.bgnzone.pzone_ori = tmp_double[2];
        roZ.bgnzone.pzone_eax = tmp_double[3];
        roZ.bgnzone.zone_ori = tmp_double[4];
        roZ.bgnzone.zone_leax = tmp_double[5];
        roZ.bgnzone.zone_reax = tmp_double[6];
    }else if(roZ.finep == 1){
        roZ.inpos.stoppoint = tmp_double[1];
        roZ.inpos.progsynch = tmp_double[2];
        roZ.inpos.inpos.position = tmp_double[3];
        roZ.inpos.inpos.speed = tmp_double[4];
        roZ.inpos.inpos.mintime = tmp_double[5];
        roZ.inpos.inpos.maxtime = tmp_double[6];
        roZ.inpos.stoptime = tmp_double[7];
        roZ.inpos.followtime = tmp_double[8];
    }

    return roZ;
}

ITP_SpeedData split_SpeedData(int index,char *s)
{
    ITP_SpeedData roV;

    strcpy(robDataName.VName[index] , Obtain_DataName(s));//得到变量名
    robDataName.VNum = index+1;

    //等号左边去掉
    char *p; 		//保存等号右边
    p = strtok(s, "=");
    p = strtok(NULL, "=");

    int i ;
    int len = strlen(p);

    char tmp[32];
    memset(tmp,0,sizeof(tmp));

    double tmp_double[16];
    memset(tmp_double,0,sizeof(tmp_double));

    int tmp_var=0,tmp_double_var = 0;
    char *endptr;

    for(i=0;i<len;i++){

        tmp[tmp_var++] = *(p++);

        if(*p==','||*p=='\n'){
            tmp_double[tmp_double_var++] = strtod(tmp,&endptr);

            p++;
            memset(tmp,0,sizeof(tmp));
            tmp_var=0;
        }
    }

    roV.time = tmp_double[0];
    roV.v_tcp = tmp_double[1];
    roV.v_ort = tmp_double[2];
    roV.v_leax = tmp_double[3];
    roV.v_reax = tmp_double[4];

    return roV;
}

void *getData(int flagType,char *DataName)	//在robDataBuffer获取数据
{
    void *typeData = NULL;
    char DataName_BACKUP[16];

    //先将数据名保存;
    strcpy(DataName_BACKUP,DataName);
    int i =0 ;
    for(i =0;i<strlen(DataName_BACKUP);i++){
        if(!(('Z'-DataName_BACKUP[0]>=0&&DataName_BACKUP[0]-'A'>=0)||('z'-DataName_BACKUP[0]>=0&&DataName_BACKUP[0]-'a'>=0)))
                //名字开头必须是字母
            return typeData;

        if(!(('Z'-DataName_BACKUP[i]>=0&&DataName_BACKUP[i]-'A'>=0)||('z'-DataName_BACKUP[i]>=0&&DataName_BACKUP[i]-'a'>=0)||
                ('9'-DataName_BACKUP[i]>=0&&DataName_BACKUP[i]-'0'>=0)))//只能是字母或数字
            return typeData;
    }

    //先判断是否有flagType这个类型,后判断是否有这个名字
    switch(flagType){
            case DataManage_RobTargetType:
                for(i=0;i<DataManage_RobTargetNum;i++){
                    if(robDataBuffer.flagP[i]=='1'&&strcmp(robDataName.PName[i],DataName) == 0)
                        typeData = &robDataBuffer.P[i];
                }
                break;
            case DataManage_JointTargetType:
                for(i=0;i<DataManage_JointTargetNum;i++){
                    if(robDataBuffer.flagJ[i]=='1'&&strcmp(robDataName.JName[i],DataName) == 0)
                        typeData = &robDataBuffer.J[i];
                }
                break;
            case DataManage_WobjDataType:
                for(i=0;i<DataManage_WobjDataNum;i++){
                    if(robDataBuffer.flagW[i]=='1'&&strcmp(robDataName.WName[i],DataName) == 0)
                        typeData = &robDataBuffer.W[i];
                }
                break;
            case DataManage_ToolDataType:
                for(i=0;i<DataManage_ToolDataNum;i++){
                    if(robDataBuffer.flagT[i]=='1'&&strcmp(robDataName.TName[i],DataName) == 0)
                        typeData = &robDataBuffer.T[i];
                }
                break;
            case DataManage_ZoneDataType:
                for(i=0;i<DataManage_ZoneDataNum;i++){
                    if(robDataBuffer.flagZ[i]=='1'&&strcmp(robDataName.ZName[i],DataName) == 0)
                        typeData = &robDataBuffer.Z[i];
                }
                break;
            case DataManage_SpeedDataType:
                for(i=0;i<DataManage_SpeedDataNum;i++){
                    if(robDataBuffer.flagV[i]=='1'&&strcmp(robDataName.VName[i],DataName) == 0)
                        typeData = &robDataBuffer.V[i];
                }
                break;
            default:return typeData;break;
        }

    return typeData;
}
