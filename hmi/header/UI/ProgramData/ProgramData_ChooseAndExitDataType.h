#ifndef PROGRAMDATA_CHOOSEANDEXITDATATYPE_H
#define PROGRAMDATA_CHOOSEANDEXITDATATYPE_H

#include <QWidget>
#include <QTableWidgetItem>
#include "header/Common/Common.h"

namespace Ui {
class ProgramData_ChooseAndExitDataType;
}

class ProgramData_ChooseAndExitDataType : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramData_ChooseAndExitDataType(QWidget *parent = 0);
    ~ProgramData_ChooseAndExitDataType();

    void setExplainLabelText(QString String);
    void setScopeLabelText(QString String);
    void setAlterScopeText(QString String);

    void TableWidgetInsertRow(int Row);//插入一行
    void TableWidgetRemoveRow(int Row);//删除一行
    void TableWidgetSetItem(int row, int column, QTableWidgetItem *item);
    void TableWidgetAlterItem(int row,int column,QString str);//更改某行某列表格数据
    void TableWidgetClear();

    void setPosText(QString str);

    int TableWidgetRowCount;//行数

    int TableWidgetCurrentRow;  //当前行
    int TableWidgetCurrentColumn;//当前列

signals:
    void TableWidgetCellPressed_SIG(int row, int column, QString String);
    void TableWidgetCellDoubleClicked_SIG(int row, int column, QString String,QString FirstStr);

    void btnShowDataTypeClicked_SIG();
    void btnRefreshClicked_SIG();
    void btnExitDataClicked_SIG();
    void btnFilterClicked_SIG();
    void btnNewDataClicked_SIG();

public slots:
    void TableWidgetCellPressed(int row, int column);
    void TableWidgetCellDoubleClicked(int row, int column);

private:
    Ui::ProgramData_ChooseAndExitDataType *ui;

    void Init();
    void tableWidgetInit();
    void ConnectInit();
};

#endif // ProgramData_ChooseAndExitDataType_H
