#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
//#include <QPushButton>
#include <QStackedLayout>
#include <QSignalMapper>
#include <QComboBox>

#include "header/ropageoption/robmanual/manualsubtemplatewidget.h"
#include "header/ropageoption/robmanual/common.h"
#include "header/ITP_Interface.h"
//#include "header/DataManage.h"

#include "header/ropageoption/robmanual/newdatatemplatewidget.h"
//#include "header/robWidget.h"

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = 0);
    /* 手动操纵下的各个子界面的标识 */


    //Jogging::TypeJoggingPar joggingPar;     // 保存手动操纵中当前选择的参数-->已经改为全局变量了，在common.h中声明！

    Jogging::MANUALSUBWIDGET currSubWidget;     // 记录当前是哪个子界面
    void setCurrentWidget(Jogging::MANUALSUBWIDGET ManualSubWidget); // 提供父窗体设置当前子界面的接口
    QString getPositionShownInWhichCoord();

signals:
    void initPropertyData(int id);  // 初始化属性表中的数据
    void closeSubWidget();  // 通知父窗体现在可以将子界面关闭或隐藏啦
    void propertyChanged(int id, QString text);   // 通知父窗体属性框中有更新
    void positionChanged(); // 位置数据的显示格式发生变化

public slots:

private slots:
    void motionModeToolBtnClicked(int id);
    void coordinateSystemToolBtnClicked(int id);
    void incrementToolBtnClicked(int id);

    //void toolCoordTabViewClicked(QModelIndex modelIndex);

    void cancelBtnRespond(int id);  // id为【MANUALSUBWIDGET】枚举类型
    void okBtnRespond(int id);      // id为【MANUALSUBWIDGET】枚举类型

//    void newBtnRespond();
//    void modValActionRespond();  // 更改值
//    void modDecActionRespond();  // 更改声明
//    void copyActionRespond();    // 复制
//    void deleteActionRespond();  // 删除
//    void defineActionRespond();  // 定义


private:
    QStackedLayout *mainStackedLayout;

    ManualSubTemplateWidget *mechanicalUnitWidget;      // 机械单元
    ManualSubTemplateWidget *absoluteAccuracyWidget;    // 绝对精度
    ManualSubTemplateWidget *MotionModeWidget;          // 动作模式
    ManualSubTemplateWidget *CoordinateSystemWidget;    // 坐标系
    ManualTableWidget *ToolWidget;                // 工具坐标
    ManualTableWidget *WorkObjectWidget;          // 工件坐标
    ManualTableWidget *PayloadWidget;             // 有效载荷
    ManualSubTemplateWidget *JoystickLockWidget;        // 操纵杆锁定
    ManualSubTemplateWidget *IncrementWidget;           // 增量

    ManualSubTemplateWidget *PositionFormatWidget;      // 位置格式
    QComboBox *positionShownInComboBox;
    QComboBox *orientationFormatComboBox;
    QComboBox *angleFormatComboBox;
    QComboBox *angleUnitComboBox;

    ManualSubTemplateWidget *AlignWidget;               // 对准
    //ManualSubTemplateWidget *GoToWidget;                // 转到
    GoToPosTemplateWidget *GoToWidget;
    ManualSubTemplateWidget *ActivateWidget;            // 启动



    QSignalMapper *cancelSignalMapper;      // 取消按钮的信号集合
    QSignalMapper *okSignalMapper;          // 确定按钮的信号集合

    void initMechanicalUnitWidget();
    void initAbsoluteAccuracyWidget();
    void initMotionModeWidget();
    void initCoordinateSystemWidget();
    void initToolWidget();
    void initWorkObjectWidget();
    void initPayloadWidget();
    void initJoystickLockWidget();
    void initIncrementWidget();
    void initPositionFormatWidget();
    void initAlignWidget();
    void initGoToWidget();
    void initActivateWidget();

    void setAllToolBtnUnchecked(QList<QToolButton *> toolBtnList);  // 设置toolBtnList中所有按钮状态为unchecked
    // 设置toolBtnList中对应id的按钮状态为checked
    void setThisToolBtnchecked(ManualSubTemplateWidget *currentPage, QList<QToolButton *> toolBtnList, int id);


};

#endif // SETTINGWIDGET_H
