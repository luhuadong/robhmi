#define robMotSetData_GLOBALS
#define ReadFileFIFO_GLOBALS

#include "ParaSet.h"

int HMI_ParaReadFile()
{
	FILE *file = NULL;
	file = fopen(PARAFILENAME,"a+");

	if(file == NULL)
		return 0;

	ReadFileFIFO.write_pointer = 0;
    memset(ReadFileFIFO.file_content,0,sizeof(ReadFileFIFO.file_content));

	while(fgets(ReadFileFIFO.file_content[ReadFileFIFO.write_pointer],
			sizeof(ReadFileFIFO.file_content[ReadFileFIFO.write_pointer]),file)!=NULL){
		ReadFileFIFO.write_pointer++;
		memset(ReadFileFIFO.file_content[ReadFileFIFO.write_pointer],0,
				sizeof(ReadFileFIFO.file_content[ReadFileFIFO.write_pointer]));
	}
	ReadFileFIFO.read_pointer = 0;
	ReadFileFIFO.lineNum = ReadFileFIFO.write_pointer;

	fclose(file);

	int index=0;

	double *MotSetData[]={
		&robMotSetData.acc_acc,&robMotSetData.dec_acc,&robMotSetData.acc_ramp,
		&robMotSetData.acc_finepramp,&robMotSetData.accMax,&robMotSetData.decMax,

		&robMotSetData.worldAcc_acc,&robMotSetData.worldDec_acc,&robMotSetData.worldAcc_ramp,
		&robMotSetData.worldAcc_finepramp,&robMotSetData.worldAccMax,&robMotSetData.worldDecMax,

		&robMotSetData.permitCornerJointSpeedChange,	//允许的拐角关节速度变化

		&robMotSetData.progdisp.pdisp.trans.x,&robMotSetData.progdisp.pdisp.trans.y,&robMotSetData.progdisp.pdisp.trans.z,

		&robMotSetData.progdisp.pdisp.rot.s,&robMotSetData.progdisp.pdisp.rot.x,&robMotSetData.progdisp.pdisp.rot.y,
		&robMotSetData.progdisp.pdisp.rot.z,

		&robMotSetData.progdisp.eoffs.eax[0],&robMotSetData.progdisp.eoffs.eax[1],&robMotSetData.progdisp.eoffs.eax[2],
		&robMotSetData.progdisp.eoffs.eax[3],&robMotSetData.progdisp.eoffs.eax[4],&robMotSetData.progdisp.eoffs.eax[5]
	};

	char *MotSetData_ch[]={
		&robMotSetData.sing_wrist,&robMotSetData.sing_lockaxis4,&robMotSetData.sing_base,
		&robMotSetData.acc_way
	};

	char *tmp = (char *)malloc(sizeof(char *));
	for(ReadFileFIFO.read_pointer=0;ReadFileFIFO.read_pointer<ReadFileFIFO.lineNum;ReadFileFIFO.read_pointer++){
		strcpy(tmp , ReadFileFIFO.file_content[ReadFileFIFO.read_pointer]);
		if(!validString(tmp))
			continue;
		else{
			ReadFileFIFO.FIFO[index][0] = index;
			ReadFileFIFO.FIFO[index][1] = ReadFileFIFO.read_pointer;
		}

		if(index<12){
			*MotSetData[index++] = getVarToDouble(tmp);
		}else if((index>=12&&index<16)){
			*MotSetData_ch[(index++)-12] = getVarToChar(tmp);
		}else if((index>=16&&index<30)){
			*MotSetData[(index++)-4] = getVarToDouble(tmp);
		}

		memset(tmp,0,sizeof(tmp));
	}

	return 1;
}

double getVarToDouble(char *s)
{
	if(s==NULL)
		return 0;

	double num;

	char *p;

	p = strtok(s, "\t");

	num = atof(p);

	return num;
}

char getVarToChar(char *s)
{
	if(s==NULL)
		return 0;

	char *p;

	p = strtok(s, "\t");

	return *p;
}

bool validString(char *s)//false 无效 true 有效
{
	if(s==NULL)
		return false;

	if(!(*s>='0'&&*s<='9'))
		return false;

	return true;
}

int HMI_ParaAlter(int index, void *pData)
{
	double *MotSetData[]={
		&robMotSetData.acc_acc,&robMotSetData.dec_acc,&robMotSetData.acc_ramp,
		&robMotSetData.acc_finepramp,&robMotSetData.accMax,&robMotSetData.decMax,

		&robMotSetData.worldAcc_acc,&robMotSetData.worldDec_acc,&robMotSetData.worldAcc_ramp,
		&robMotSetData.worldAcc_finepramp,&robMotSetData.worldAccMax,&robMotSetData.worldDecMax,

		&robMotSetData.permitCornerJointSpeedChange,	//允许的拐角关节速度变化

		&robMotSetData.progdisp.pdisp.trans.x,&robMotSetData.progdisp.pdisp.trans.y,&robMotSetData.progdisp.pdisp.trans.z,

		&robMotSetData.progdisp.pdisp.rot.s,&robMotSetData.progdisp.pdisp.rot.x,&robMotSetData.progdisp.pdisp.rot.y,
		&robMotSetData.progdisp.pdisp.rot.z,

		&robMotSetData.progdisp.eoffs.eax[0],&robMotSetData.progdisp.eoffs.eax[1],&robMotSetData.progdisp.eoffs.eax[2],
		&robMotSetData.progdisp.eoffs.eax[3],&robMotSetData.progdisp.eoffs.eax[4],&robMotSetData.progdisp.eoffs.eax[5]
	};

	char *MotSetData_ch[]={
		&robMotSetData.sing_wrist,&robMotSetData.sing_lockaxis4,&robMotSetData.sing_base,
		&robMotSetData.acc_way
	};

	char s[25];
	memset(s,0,sizeof(s));

	char *p;
	p = strtok(ReadFileFIFO.file_content[ReadFileFIFO.FIFO[index][1]], "\t");
	p = strtok(NULL, "\t");

	if(index>=12&&index<16){
		*MotSetData_ch[index-12]=*(char*)pData;

		sprintf(s,"%f\t%s",*MotSetData[index-12],p);
		strcpy(ReadFileFIFO.file_content[ReadFileFIFO.FIFO[index][1]] ,s);
	}else if(index>0&&index<12){
		*MotSetData[index]=*(double*)pData;

		sprintf(s,"%f\t%s",*MotSetData[index],p);
		strcpy(ReadFileFIFO.file_content[ReadFileFIFO.FIFO[index][1]] ,s);
	}else if(index>=16&&index<30){
		*MotSetData[index-4]=*(double*)pData;

		sprintf(s,"%f\t%s",*MotSetData[index-4],p);
		strcpy(ReadFileFIFO.file_content[ReadFileFIFO.FIFO[index][1]] ,s);
	}

	return 1;
}

/***************************************************************************/
/*函数功能：将内存所有数据保存到文件*/
/*输入参数：*/
/*输出参数: 无*/
/*返回值： 0表示失败,1表示成功*/
/***************************************************************************/
int HMI_ParaWriteFile()
{
	FILE *file = NULL;
	file = fopen(PARAFILENAME,"w");
	if(file == NULL)
		return 0;

	ReadFileFIFO.read_pointer = 0;

	for(;ReadFileFIFO.read_pointer<ReadFileFIFO.lineNum;ReadFileFIFO.read_pointer++)
		fputs(ReadFileFIFO.file_content[ReadFileFIFO.read_pointer],file);

	fclose(file);

	return 1;
}
