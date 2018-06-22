#ifndef PROGRAMCHOOSE_H
#define PROGRAMCHOOSE_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QMenu>
//#include "Common/Common.h"

//#include "FileAndDirOperate.h"

namespace Ui {
class ProgramChoose;
}

class ProgramChoose : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramChoose(QWidget *parent = 0);
    ~ProgramChoose();

    void TableWidgetSelectRow(int row);
    void TableWidgetSetRowCount(int Row);
    void TableWidgetClear();
    void TableWidgetSetItem(int row, int column, QTableWidgetItem *item);
    void setItemText(int row, int column, QString str);

    void setMissionAndPro();
    void setChoosePro();

    QMenu *menu;

private slots:
    void do_TableWidgetCellClicked(int row,int column);
    void do_BtnOpenClicked();
    void do_BtnFileClicked();

signals:
    void BtnShowModuleClicked_SIG();
    void BtnOpenClicked_SIG(int,int,QString,QString);
    void MenuActionTriggered(QAction *action);

    void TableWidgetCellClicked_SIG(int row,int column,QString MissionName,//任务名
                                    QString ProgramName);//ProgramName程序名

private:
    Ui::ProgramChoose *ui;

    void Init();
    void BtnInit();
    void TableWidgetInit();
    void ConnectInit();    
};

#endif // PROGRAMCHOOSE_H
