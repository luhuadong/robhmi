#include "ResourceManage.h"
#include "ui_ResourceManage.h"

void ResourceManage::do_btnMenuClicked()
{
    menu->setFixedWidth(ui->btn_menu->size().width());



    QPoint pos;
    pos.setX(0);
    pos.setY(-menu->sizeHint().height());

    menu->exec(ui->btn_menu->mapToGlobal(pos));
}

void ResourceManage::do_triggered(QAction* Action)
{
    for(int i = 0;i<menu->actions().count();i++){
        if(Action->text()==menu->actions().at(i)->text()){
            switch (i) {
            case do_Copy:Copy();
                break;
            case do_Move:Cut();
                break;
            case do_Pase:Paste();//Delete();
                break;
            case do_ReNa:
                ui->stackedWidget->setCurrentIndex(View_vkey);
                vkey->vkeyWorldInput(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
                break;
            case do_Dele:Delete();
                break;
            case do_Attr:
                ui->stackedWidget->setCurrentIndex(View_Attr);
                AttrInfo(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
                break;
            default:break;
            }
        }
    }
    ui->btn_menu->setChecked(false);
}

void ResourceManage::do_btnShowHeaderClicked()
{
    ui->tableWidget->horizontalHeader()->show();//表头显示
}

void ResourceManage::do_btnHideHeaderClicked()
{
    ui->tableWidget->horizontalHeader()->hide();//表头隐藏
}

void ResourceManage::do_TableWidgetNoChooseLine()
{
    menu->setEnabled(false);
}

void ResourceManage::do_TableWidgetCellClicked(int , int )
{
//    ItemType = ui->tableWidget->item(row,1)->text();
//    ItemName = ui->tableWidget->item(row,0)->text();

    menu->setEnabled(true);
}

void ResourceManage::do_btnNewClicked()
{
    currentAction = Action_New;
    ui->stackedWidget->setCurrentIndex(View_vkey);
}

void ResourceManage::do_keyOk(QString str)
{
    switch (currentAction) {
    case Action_Rename:
        this->ReName(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text(),str);
        break;
    case Action_New:NewDirectory(str);
        break;
    default:break;
    }

    do_btnRefreshClicked();
    ui->stackedWidget->setCurrentIndex(View_RB);
}

void ResourceManage::do_btnRefreshClicked()
{
    dir.setPath(dirPath);
    ShowFile(dir);
}

void ResourceManage::do_btnCloseClicked()
{
    ui->stackedWidget->setCurrentIndex(View_RB);
}

void ResourceManage::do_keyCancle()
{
    ui->stackedWidget->setCurrentIndex(View_RB);
}
