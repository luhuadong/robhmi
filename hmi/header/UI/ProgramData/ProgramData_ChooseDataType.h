#ifndef PROGRAMDATA_SHOW_H
#define PROGRAMDATA_SHOW_H

#include <QWidget>
#include <QTableWidgetItem>

#include "header/Common/Common.h"

namespace Ui {
class ProgramData_ChooseDataType;
}

//可用做程序数据显示列表界面等类似界面
class ProgramData_ChooseDataType : public QWidget
{
    Q_OBJECT
public:
    explicit ProgramData_ChooseDataType(QWidget *parent = 0);
    ~ProgramData_ChooseDataType();

    void setExplainLabelText(QString String);
    void setScopeLabelText(QString String);
    void setAlterScopeText(QString String);

    void TableWidgetInsertRow(int Row);//插入一行
    void TableWidgetRemoveRow(int Row);//删除一行
    void TableWidgetSetItem(int row, int column, QTableWidgetItem *item);
    void TableWidgetClear();

    void setPosText(QString str);

    int TableWidgetRowCount;//行数

    int TableWidgetCurrentRow;  //当前行
    int TableWidgetCurrentColumn;//当前列

signals:
    void TableWidgetCellPressed_SIG(int row, int column, QString String);
    void TableWidgetCellDoubleClicked_SIG(int row, int column, QString String);
    void btnViewClicked_SIG();
    void btnShowDataClicked_SIG();

public slots:
    void TableWidgetCellPressed(int row, int column);
    void TableWidgetCellDoubleClicked(int row, int column);

private:
    Ui::ProgramData_ChooseDataType *ui;

    void Init();
    void tableWidgetInit();
    void ConnectInit();
};

#endif // PROGRAMDATA_SHOW_H
