#ifndef PROGRAMDATA_ALTER_H
#define PROGRAMDATA_ALTER_H

#include <QWidget>
#include <QTableWidgetItem>
#include "./../Common/Common.h"

namespace Ui {
class ProgramData_Alter;
}

class ProgramData_Alter : public QWidget
{
    Q_OBJECT
public:
    explicit ProgramData_Alter(QWidget *parent = 0);
    ~ProgramData_Alter();

    void setFALSEBtnHide(bool Hideen);
    void setTRUEBtnHide(bool Hideen);
    void setUndoBtnHide(bool Hideen);

    void setCancelBtnEnabled(bool checkable);
    void setUndoBtnEnabled(bool checkable);
    void setOKBtnEnabled(bool checkable);

    void TableWidgetClear();//清楚表格所有行
    void TableWidgetInsertRow(int Row);//插入一行
    void TableWidgetRemoveRow(int Row);//删除一行.
    void TableWidgetSetRowCount(int RowCount);//设置行数
    void TableWidgetSetItem(int row, int column, QTableWidgetItem *item);

    void TableWidgetAlterCurrentItem(QString str);//更改当前表格数据

    void TableWidgetSelectRow(int row);
    QString TableWidgetItemQString(int row,int column);//指定某行某列的内容

    int TableWidgetRowCount;

    int TableWidgetCurrentRow;  //当前行
    int TableWidgetCurrentColumn;//当前列

signals:
    void TRUEBtnClicked_SIG();
    void FALSEBtnClicked_SIG();
    void UndoBtnClicked_SIG();
    void OkBtnClicked_SIG();
    void CancelBtnClicked_SIG();

    void TableWidgetCellPressed_SIG(int row,int column,QString String);
    void TableWidgetItemClicked_SIG(QTableWidgetItem* item);

public slots:
    void TableWidgetCellPressed(int row,int column);

private:
    Ui::ProgramData_Alter *ui;

    void Init();
    void tableWidgetInit();
    void buttonWidgetInit();
    void ConnectInit();
};

#endif // PROGRAMDATA_ALTER_H
