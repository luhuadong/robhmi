#ifndef ROPAGEALAM_H
#define ROPAGEALAM_H

#define AlarmSavePath "./"

#include <QWidget>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include "header/ropageoption/ropagealarm/alarmthread/alarmthread.h"
#include "header/UI/robResouceManage/robResouceManage.h"
#include "header/UI/keyworld/vkeyworld/vkeyworld.h"
#include "header/Common/Common.h"

namespace Ui {
class RoPageAlarm;
}

class RoPageAlarm : public QWidget
{
    Q_OBJECT

public:
    explicit RoPageAlarm(QWidget *parent = 0);
    ~RoPageAlarm();

public slots:
    void do_cellClicked(int row, int column);

    void do_Alarm();
    void do_btnSaveClicked();
    void do_btnDelClicked();
    void do_btnRefreshClicked();
    void do_btnOkClicked();
    void do_btnViewClicked();

    void do_robRMbtnNewClicked();
    void do_robRMbtnOpenKeyClicked();
    void do_robRMbtnOkClicked();
    void do_robRMbtnCancelClicked();

    void do_keyOk(QString str);
    void do_keyCancel();
    void do_TimerOut();

signals:
    void isAlarm(int ViewNum);
    void sendAlarm();

private:
    Ui::RoPageAlarm *ui;
    robResouceManage *robRM;
    vkeyworld *vkey;

    QMutex mutex;
    AlarmThread *robAlarmThread;//报警进程

    QString ExpAlarmData[5];
    int currentAction;

    enum Action{
        Action_Rename,
        Action_New,
    };

    void Show_tablewidget_file();

    void Init();

    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();

    enum AlarmView{
        aShowView,//报警显示
        aExpView,//报警说明
        aRMView,//资源管理
        aKeyView,//输入法
    };

    void TableWidgetToFile(QTableWidget *TableWidget, QString filename);
};

#endif // ROPAGEALAM_H
