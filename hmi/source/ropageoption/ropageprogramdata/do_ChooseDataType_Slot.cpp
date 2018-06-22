#include "header/ropageoption/ropageprogramdata/ropageprogramdata.h"
#include "ui_ropageprogramdata.h"

void ropageprogramdata::do_ChooseDataType_CancelBtnClicked()
{
}

void ropageprogramdata::do_ChooseDataType_ShowData()
{
    ui->stackedWidget->setCurrentIndex(ChooseAndExitDataTypeView);
    ChooseAndExitDataTypeShow();
}

void ropageprogramdata::do_ChooseDataType_View()
{

}

void ropageprogramdata::do_ChooseDataType_TableWidgetCellDoubleClicked(int row, int column, QString )
{
    CurrentDataType = row*3+column;
    do_ChooseDataType_ShowData();
}

void ropageprogramdata::do_ChooseDataType_TableWidgetCellClicked(int row, int column, QString String)
{
    CurrentDataType = row*3+column;
}

