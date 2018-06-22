#include "ProgramShow.h"
#include "ui_ProgramShow.h"

void ProgramShow::do_VerticalValueChanged(int value)
{
    if(ui->textBrowser_ShowPro->verticalScrollBar()->value() != value)
        ui->textBrowser_line->verticalScrollBar()->
                setValue(ui->textBrowser_ShowPro->verticalScrollBar()->value());

    ui->textBrowser_line->verticalScrollBar()->setValue(value);
}

void ProgramShow::do_blockCountChanged(int blockCount)
{
    ui->textBrowser_line->verticalScrollBar()->
            setValue(ui->textBrowser_ShowPro->verticalScrollBar()->value());
}

void ProgramShow::do_BtnAddOrderClicked()
{
    if(ui->stackedWidget->isHidden())
        ui->stackedWidget->show();
    else if((!ui->stackedWidget->isHidden())&&ui->stackedWidget->currentIndex()==vAddOrder)
       ui->stackedWidget->hide();

    ui->stackedWidget->setCurrentIndex(vAddOrder);
}

void ProgramShow::do_BtnEditClicked()
{
    if(ui->stackedWidget->isHidden())
        ui->stackedWidget->show();
    else if((!ui->stackedWidget->isHidden())&&ui->stackedWidget->currentIndex()==vEdit)
       ui->stackedWidget->hide();

    ui->stackedWidget->setCurrentIndex(vEdit);
}

void ProgramShow::do_BtnDebugClicked()
{
    if(ui->stackedWidget->isHidden())
        ui->stackedWidget->show();
    else if((!ui->stackedWidget->isHidden())&&ui->stackedWidget->currentIndex()==vDebug)
        ui->stackedWidget->hide();

    ui->stackedWidget->setCurrentIndex(vDebug);
}

void ProgramShow::do_BtnAlterPosClicked()
{
    ShowInsertQstring("hello\n");
}

void ProgramShow::do_BtnHideDeclareClicked()
{
    ShowDelQstring();
}
