#ifndef ROBWIDGET_H
#define ROBWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QcomboBox>
#include <QTableWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QAction>
#include <QMenu>
#include <QHeaderView>

#include "header/Common/Common.h"

//新建数据界面类
class ProgramData_New : public QWidget
{
    Q_OBJECT
public:
    explicit ProgramData_New(QWidget *parent = 0);
    ~ProgramData_New();

    void setNameLineEditText(QString string);
    QString getnameLineEditText();
    void setMaintainLineEditText(QString string);
    QString getMaintainLineEditText();

signals:
    void InitDataBtnClicked_SIG();
    void OkBtnClicked_SIG();
    void CancelBtnClicked_SIG();
    void OpenVkeyWorldBtnClicked_SIG();
    void OpenOtherWidgetBtnClicked_SIG();

public slots:
    void InitDataBtnClicked();
    void OkBtnClicked();
    void CancelBtnClicked();
    void OpenVkeyWorldBtnClicked();
    void OpenOtherWidgetBtnClicked();

private:
    QWidget *DataTaskWidget;
    QLabel *DataType;
    QLabel *DataType_INPUT;
    QLabel *currentTask;
    QLabel *currentTask_INPUT;

    /***************************************/
    QWidget *Widget;

    QLabel *nameLabel;//名称
    QLineEdit *nameLineEdit;
    QPushButton *OpenVkeyWorld;

    QLabel *scopeLabel;//范围
    QComboBox *scopeComboBox;

    QLabel *saveTypeLabel;//存储类型
    QComboBox *saveTypeComboBox;

    QLabel *TaskLabel;//任务
    QComboBox *TaskComboBox;

    QLabel *moduleLabel;//模块
    QComboBox *moduleComboBox;

    QLabel *MainLabel;//例行程序
    QComboBox *MainComboBox;

    QLabel *maintainLabel;//维数
    QComboBox *maintainComboBox;
    QLineEdit *maintainLineEdit;
    QPushButton *OpenOtherWidget;    //改

    /***************************************/
    QWidget *buttonWidget;
    QPushButton *InitDataBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void Init();

    void DataTaskWidgetInit();
    void buttonWidgetInit();
    void WidgetInit();
    void ConnectInit();
};

//数据定义界面
class ProgramData_Define : public QWidget
{
    Q_OBJECT
public:
    explicit ProgramData_Define(QWidget *parent = 0);
    ~ProgramData_Define();

    void setCoordDefineLabelText(QString String){
        CoordDefineLabel->setText(String);
    }
    void setCoordLabelText(QString String){
        CoordLabel->setText(String);
    }
    void setCurrentCoordLabelText(QString String){
        CurrentCoordLabel->setText(String);
    }
    void setactivityToolLabelText(QString String){
        activityToolLabel->setText(String);
    }
    void setCurrentactivityToolLabelText(QString String){
        CurrentactivityToolLabel->setText(String);
    }
    void setExplainLabelText(QString String){
        ExplainLabel->setText(String);
    }
    void setuserMethodLabelText(QString String){
        userMethodLabel->setText(String);
    }
    void settargetMethodLabelText(QString String){
        targetMethodLabel->setText(String);
    }
    void setactivityToolLabelHide(){
        activityToolLabel->hide();
    }
    void setCurrentactivityToolLabelHide(){
        CurrentactivityToolLabel->hide();
    }
    void addLeftComboxItem(QString String){
        LeftCombox->addItem(String);
    }
    void addRightComboxItem(QString String){
        RightCombox->addItem(String);
    }

    void setToolDataWidget();
    void setWobjDataWidget();
    QFont font;//字体设置

signals:
    void PosBtnClicked_SIG();
    void OkBtnClicked_SIG();
    void CancelBtnClicked_SIG();
    void SetPosBtnClicked_SIG();
    void LeftComboxIndexChaged_SIG(QString String);
    void RightComboxIndexChaged_SIG(QString String);
    void MenuTriggered_SIG(QAction*);

public slots:
    void PosBtnClicked();
    void OkBtnClicked();
    void CancelBtnClicked();
    void SetPosBtnClicked();
    void do_LeftComboxIndexChanged(QString String);
    void do_RightComboxIndexChanged(QString String);
    void do_triggered(QAction* Action);

private:
    QWidget *TipsWidget;

    QLabel *CoordDefineLabel;//*坐标定义 可更改
    QLabel *CoordLabel;   //*坐标 可更改
    QLabel *CurrentCoordLabel;   //当前坐标 可更改
    QLabel *activityToolLabel;   //活动工具  可隐藏 可更改
    QLabel *CurrentactivityToolLabel;   //当前活动工具  可隐藏 可更改

    QLabel *ExplainLabel;//选择一种方法,修改位置后点击"确定"

    QLabel *userMethodLabel;//方法||用户方法 可更改
    QComboBox *LeftCombox;
    QLabel *targetMethodLabel;//点数||目标方法 可更改
    QComboBox *RightCombox;    //

    QWidget *tablewidget;
    QTableWidget *TableWidget;


    QWidget *buttonWidget;
    QPushButton *PosBtn;
    QPushButton *SetPosBtn;
    QPushButton *OkBtn;
    QPushButton *CancelBtn;

    void Init();
    void TipsWidgetInit();
    void tablewidgetInit();
    void buttonWidgetInit();
    void ConnectInit();
};


#endif // ROBWIDGET_H
