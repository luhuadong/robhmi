#include "header/ropageoption/robmanual/editbtn.h"
#include "header/ropageoption/robmanual/newdatatemplatewidget.h"
#include "header/ropageoption/robmanual/common.h"
#include <QPoint>

EditBtn::EditBtn(QWidget *parent) :
    QPushButton(parent)
{
    editBtnMenu = new QMenu(this);
    editBtnMenu->setFixedSize(100, 220);

    modValAction = new QAction(tr("更改值"), this);
    modDecAction = new QAction(tr("更改声明"), this);
    copyAction = new QAction(tr("复制"), this);
    deleteAction = new QAction(tr("删除"), this);
    defineAction = new QAction(tr("定义"), this);

    editBtnMenu->addAction(modValAction);
    editBtnMenu->addAction(modDecAction);
    editBtnMenu->addAction(copyAction);
    editBtnMenu->addAction(deleteAction);
    editBtnMenu->addSeparator();
    editBtnMenu->addAction(defineAction);

    this->setMenu(editBtnMenu);
    this->setText(tr("编辑"));


    QPoint pos;
    pos.setX(0);
    //pos.setY(-menu->sizeHint().height());
    pos.setY(-editBtnMenu->sizeHint().height());
    //editBtnMenu->exec(this->mapToGlobal(pos));
    //menu->exec(ui->btnOperator->mapToGlobal(pos));


    connect(modDecAction, SIGNAL(triggered()), this, SLOT(showModDec()));

//    std::string s1("Hello World");
//    for(char i : s1)
//    {

//    }
}

void EditBtn::showModDec()
{
    NewDataTemplateWidget *modDecWidget = new NewDataTemplateWidget(ProgramData::ROB_TARGET, "hello", parentWidget());
    //modDecWidget.show();
    modDecWidget->show();
}
