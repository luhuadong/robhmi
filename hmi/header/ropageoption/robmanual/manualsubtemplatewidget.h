/*
 * @file	manualsubtemplatewidget.h
 * @brief	手动操纵界面的子对话框界面模板类
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

#ifndef MANUALSUBTEMPLATEWIDGET_H
#define MANUALSUBTEMPLATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QTableView>
#include <QStandardItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QAbstractItemView>

#include "header/ropageoption/robmanual/editbtn.h"
#include "header/ropageoption/robmanual/common.h"
#include "header/ropageoption/robmanual/newdatatemplatewidget.h"

class ManualSubTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManualSubTemplateWidget(QWidget *parent = 0);
    void setContentWidgetLayout(QLayout *contentLayout);    // 提供设置contentWidget的主布局的接口

    void setCurrentKeyText(QString text);   // 修改提示栏【当前选择】标签本身
    void setCurrentValText(QString text);   // 修改提示栏【当前选择】的值
    void setTipsText(QString tips); // 提供修改提示栏【提示】信息tipsLabel的接口

    QList<QToolButton *> toolBtnList;
    QPushButton *newBtn;

    //EditBtn *editBtn;
    QPushButton *editBtn;
    QMenu *editBtnMenu;
    // 以下action对应的信号与槽需要由使用者根据实际情况来定义
    QAction *modValAction;  // 更改值
    QAction *modDecAction;  // 更改声明
    QAction *copyAction;    // 复制
    QAction *deleteAction;  // 删除
    QAction *defineAction;  // 定义

    QTableView *contentTabView;
    QStandardItemModel *contentModel;


signals:
    //void closeWidget();     // 点击【取消】按钮触发的信号
    void cancelBtnClicked();    // 点击【取消】按钮触发的信号
    void okBtnClicked();        // 点击【确定】按钮触发的信号

public slots:

private:
    QWidget *tipsWidget;
    //QString currentSelectionStr;
    QLabel *currentKeyLabel;
    QLabel *currentValLabel;
    QLabel *tipsLabel;

    QWidget *contentWidget;


    QWidget *buttonWidget;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    //QList<QToolButton *> toolBtnList;
};



/* **************************************************** */
/* ******************** 【转到】界面 ******************** */
/* *************************************************** */
class GoToPosTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoToPosTemplateWidget(QWidget *parent = 0);
    ~GoToPosTemplateWidget();

signals:
    //void closeWidget();     // 点击【取消】按钮触发的信号
    void cancelBtnClicked();    // 点击【取消】按钮触发的信号
    //void okBtnClicked();        // 点击【确定】按钮触发的信号

public slots:

private slots:
    void goToPosBtnPressed();
    void goToPosBtnReleased();

private:
    QWidget *tipsWidget;    // 机械单元，活动工具，活动工件

    QLabel *mechanicalUnitKeyLabel;   // 机械单元
    QLabel *mechanicalUnitValLabel;
    QLabel *activeToolKeyLabel;       // 活动工具
    QLabel *activeToolValLabel;
    QLabel *activeWobjKeyLabel;       // 活动工件
    QLabel *activeWobjValLabel;

    QWidget *contentWidget;

    QListWidget *robtargetListWidget;   // 显示当前任务中的机器人示教点列表
    QLabel *activeFilterKeyLabel; // 活动过滤器： XXX
    QLabel *activeFilterValLabel;
    // 按住“启动装置”(1.Press and hold Enabling Device.)
    QLabel *step1Label;
    // 按住“转到”按钮，转到位置Px(2.Press and hold Go To button to go to position Px)
    QLabel *step2Label;
    QPushButton *goToPosBtn;    // “转到”按钮

    QWidget *buttonWidget;
    //QPushButton *okBtn;
    //QPushButton *cancelBtn;
    QPushButton *filterBtn;
    QPushButton *closeBtn;

    char mode;  // 记录进行“转到”操作前系统的模式

};


/* **************************************************** */
/* ******** 【工具坐标】/【工件坐标】/【有效载荷】界面 ******* */
/* *************************************************** */
class ManualTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManualTableWidget(Jogging::MANUALSUBWIDGET widgetType, QWidget *parent = 0);
    ~ManualTableWidget();

signals:
    void cancelBtnClicked();    // 点击【取消】按钮触发的信号
    void okBtnClicked();        // 点击【确定】按钮触发的信号

public slots:

private slots:
    void tabViewClicked(QModelIndex modelIndex);

    void newBtnRespond();
    void modValActionRespond();  // 更改值
    void modDecActionRespond();  // 更改声明
    void copyActionRespond();    // 复制
    void deleteActionRespond();  // 删除
    void defineActionRespond();  // 定义

private:
    Jogging::MANUALSUBWIDGET curWidgetType;

    QWidget *tipsWidget;
    QLabel *currentKeyLabel;
    QLabel *currentValLabel;
    QLabel *tipsLabel;

    QWidget *contentWidget;
    QTableView *tabView;
    QStandardItemModel *tabModel;
    QLabel *itemCntLabel;

    QWidget *buttonWidget;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QPushButton *newBtn;
    QPushButton *editBtn;
    QMenu *editBtnMenu;
    // 以下action对应的信号与槽需要由使用者根据实际情况来定义
    QAction *modValAction;  // 更改值
    QAction *modDecAction;  // 更改声明
    QAction *copyAction;    // 复制
    QAction *deleteAction;  // 删除
    QAction *defineAction;  // 定义
};

#endif // MANUALSUBTEMPLATEWIDGET_H
