#ifndef HMI_PARASET_H
#define HMI_PARASET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QDebug>

#include "header/ParaSet/ParaSet.h"

static double *MotSetData[]={
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

static char *MotSetData_ch[]={
    &robMotSetData.sing_wrist,&robMotSetData.sing_lockaxis4,&robMotSetData.sing_base,
    &robMotSetData.acc_way
};

namespace Ui {
class HMI_ParaSet;
}

class HMI_ParaSet : public QWidget
{
    Q_OBJECT

public:
    explicit HMI_ParaSet(QWidget *parent = 0);
    ~HMI_ParaSet();

private slots:
    void do_btnAcqClicked();//默认值
    void do_btnOkClicked();
    void TableWidgetCellPressed(int row,int column);
    void TableWidgetItemClicked(QTableWidgetItem* item);
    void do_comboBoxIndexChanged(int index);

private:
    Ui::HMI_ParaSet *ui;

    void Init();
    void TableWidgetInit();
    void ConnectInit();

    void clearTableWidget();

    void ShowAcc();//关节加速度
    void ShowWorldAcc();//笛卡尔加速度
    void ShowSing();//奇异点
    void ShowCornerJointSpeedChange();//允许的拐角关节速度变化
    void ShowAccWay();//机器人配置
    void ShowProgDisp();//偏移参数

    void SetLabelPosText(QString str);
//    void TableWidgetSetItem(int row, int column, QTableWidgetItem *item);


};

#endif // HMI_PARASET_H
