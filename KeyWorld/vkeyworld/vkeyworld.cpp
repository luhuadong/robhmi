#include "vkeyworld.h"
#include "ui_vkeyworld.h"

vkeyworld::vkeyworld(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vkeyworld)
{
    ui->setupUi(this);

    Init();
}

vkeyworld::~vkeyworld()
{
    delete ui;
}

void vkeyworld::globalConfig()
{
    ui->lineEdit->setFocus();
    ui->lineEdit->setText(str);
    ui->lineEdit->setCursorPosition(cursorPos+1);

    if(modal_Shift){
        ui->btn_Shift->setChecked(false);
        modal_Shift = NoShiftModel;
        doChange_ShiftModal(0);
    }
}

void vkeyworld::vkeyWorldInput(QString s)
{
    ui->lineEdit->setText(s);
    Init();
}
