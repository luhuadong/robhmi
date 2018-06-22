/*
 * @file	robmanual.h
 * @brief	手动操纵界面
 * @author  LHD
 * @version 1.0
 * @date	2015-8-31
 *
 * # update (更新日志)
 *
 * [2015-08-31] <author> v1.0
 *
 * + v1.0版发布
 *
 */

#ifndef ROBMANUAL_H
#define ROBMANUAL_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QFrame>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QTime>
#include <QTimer>

#include "header/ropageoption/robmanual/settingwidget.h"

// 包含类型ITP_InputData
#include "header/ITP_Interface.h"

// 包含函数DataManage_InitShareMem_InputData
#include "header/DataManage_WinShareMem.h"

// 包含自定义的类OutputThread，用于实时获取机器人的位姿数据
#include "header/ropageoption/robmanual/updateposedatathread.h"


class RobManual : public QWidget
{
    Q_OBJECT
public:
    explicit RobManual(QWidget *parent = 0);
    ~RobManual();

signals:
    //void positionChanged(); // 位置数据的显示格式发生变化

public slots:
    void changeProperties(int row, int column);
    void updatePositionTable(); // 更新位置数据的显示格式

private slots:
    //void closeSubWidget();
    void poseFormatBtnClicked();
    void alignBtnClicked();
    void gotoBtnClicked();
    void activateBtnClicked();

    void propertyChanged(int id, QString text);   // 根据id更新属性框中的数据
    //void changePosition(); // 位置数据的显示格式发生变化
    void updatePoseData(QString *poseData); // 接收线程updatePoseDataThread的信号来更新数据

    void robotJogging(int id);    // 机器人动
    void robotStanding(int id);   // 机器人不动

    void keyLongPressListenerRespond(); // 按钮长按监听
    void incrementTimerRespond();       // 增量模式下连续运动处理函数


private:

    QGroupBox *propertyGroupBox;
    QTableWidget *propertyTabWidget;
    QTableWidgetItem *propertyTabMecKeyItem;    // 机械单元
    QTableWidgetItem *propertyTabMecValItem;
    QTableWidgetItem *propertyTabAbsKeyItem;    // 绝对精度
    QTableWidgetItem *propertyTabAbsValItem;
    QTableWidgetItem *propertyTabMotKeyItem;    // 动作模式
    QTableWidgetItem *propertyTabMotValItem;
    QTableWidgetItem *propertyTabCooKeyItem;    // 坐标系
    QTableWidgetItem *propertyTabCooValItem;
    QTableWidgetItem *propertyTabTooKeyItem;    // 工具坐标
    QTableWidgetItem *propertyTabTooValItem;
    QTableWidgetItem *propertyTabWorKeyItem;    // 工件坐标
    QTableWidgetItem *propertyTabWorValItem;
    QTableWidgetItem *propertyTabPayKeyItem;    // 有效载荷
    QTableWidgetItem *propertyTabPayValItem;
    QTableWidgetItem *propertyTabJoyKeyItem;    // 操纵杆锁定
    QTableWidgetItem *propertyTabJoyValItem;
    QTableWidgetItem *propertyTabIncKeyItem;    // 增量
    QTableWidgetItem *propertyTabIncValItem;

    void initPropertyTable();

    QGroupBox *poseInfoGroupBox;
    QLabel *poseLabel;
    QTableWidget *poseTableWidget;
    QStringList *poseKeyItemStrList;    // 指向当前位置表第一列（key）的字符串链表
    QStringList *poseUnitItemStrList;   // 指向当前位置表第三列（unit）的字符串链表
    QList<QTableWidgetItem *> poseTabKeyItemList;   // 第一列
    QList<QTableWidgetItem *> poseTabValItemList;   // 第二列
    QList<QTableWidgetItem *> poseTabUnitItemList;  // 第三列
    QPushButton *poseFormatBtn;
    UpdatePoseDataThread *updatePoseDataThread; // 实时更新机器人位姿数据的线程

    void initPositionTable();


    QGroupBox *directionGroupBox;
    QStringList *moveBtnTextStrList;
    QList<QPushButton *> moveBtnList;
    //QList<QPushButton *> jointMoveBtnList;
    //QList<QPushButton *> coordMoveBtnList;
    //QList<QPushButton *> wristMoveBtnList;
    enum moveBtnFlag{ Btn_Pos_J1, Btn_Neg_J1,
                      Btn_Pos_J2, Btn_Neg_J2,
                      Btn_Pos_J3, Btn_Neg_J3,
                      Btn_Pos_J4, Btn_Neg_J4,
                      Btn_Pos_J5, Btn_Neg_J5,
                      Btn_Pos_J6, Btn_Neg_J6};

    void initDirectionBtnBox();
    void changeDirectionBtnBox();
    QTimer *keyLongPressListener;   // 用于监听增量模式下相关动作按钮的长按状态
    QTimer *incrementTimer; // 增量模式持续运动时的定时器，如果控制杆偏转持续一秒钟或数秒钟，机器人就会持续移动（速率为每秒10步）。



    QFrame *optionBarFrame;
    QPushButton *alignBtn;
    QPushButton *gotoBtn;
    QPushButton *activateBtn;
    //QPushButton *newBtn;
    //QPushButton *editBtn;
    //QPushButton *okBtn;
    //QPushButton *cancelBtn;
    //QSpacerItem *optionBarSpacer;
    QHBoxLayout *optionBarLayout;

    QVBoxLayout *topRightLayout;
    QHBoxLayout *topLayout;
    QVBoxLayout *mainLayout;

    SettingWidget *settingWidget;   // 手动操纵界面下的所有子界面



};

#endif // ROBMANUAL_H
