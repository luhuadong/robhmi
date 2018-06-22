#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QWidget>
#include "./../Common/Common.h"
#include <QModelIndex>
#include <QTreeWidgetItem>
#include <QTreeWidgetItem>

#include <QDebug>
#include <QHostInfo>
#include <QString>
#include <QNetworkInterface>

namespace Ui {
class SystemInfo;
}

class SystemInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SystemInfo(QWidget *parent = 0);
    ~SystemInfo();

    void setPosText(QString str);


private slots:
    void do_BtnRefreshClicked();
    void do_treeWidgetClicked(QModelIndex index);
//    void do_activated(QModelIndex index);
    void do_collapsed(QModelIndex);
//    void do_entered(QModelIndex index);
    void do_expanded(QModelIndex index);
//    void do_itemClicked(QTreeWidgetItem*item, int column);
    void lookedUp(const QHostInfo &host);

signals:
    void BtnRefreshClicked_SIG();

private:
    Ui::SystemInfo *ui;

    void Init();
    void TreeWidgetInit();
    void ConnectInit();

    void setTextBrowserText(QString str);

    QString obtainItemName(QTreeWidgetItem *Item);//获取Item名称
    QString obtainLocalHostName();
    QString obtainIPAddress();
    QString SystemAttribute();//系统属性
    QString ControlModuleOption();//控制模块选项
    QString DriveModule();//驱动模块
    QString DriveModuleOption();//驱动模块选项
    QString AdditionOption();//附加选项
};

#endif // SYSTEMINFO_H
