#include "robResouceManage.h"
#include "ui_robResouceManage.h"

void robResouceManage::do_btnShowHeaderClicked()
{
    ui->tableWidget->horizontalHeader()->show();//表头显示
}

void robResouceManage::do_btnHideHeaderClicked()
{
    ui->tableWidget->horizontalHeader()->hide();//表头隐藏
}

void robResouceManage::do_btnUpClicked()
{
    Up();
}

void robResouceManage::do_btnHomeClicked()
{
    Root();
}

void robResouceManage::do_Init()
{
    Root();
}

void robResouceManage::do_cellClicked(int row,int)
{
    QTableWidgetItem* item = ui->tableWidget->item(row,1);
    if(item==NULL)
        return;

    if(item->text()==tr(" 目录"))
        Go();
    else
        ui->lineEdit_filename->setText(ui->tableWidget->item(row,0)->text());
}
