#include "vkeyworld.h"
#include "ui_vkeyworld.h"

void vkeyworld::digitClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();

    for(int i =0;i<btnList_digit.count();i++){
        if(btnList_digit.at(i)->hasFocus())
            str.insert(cursorPos,btnList_digit.at(i)->text());
    }

    globalConfig();
}

void vkeyworld::character_qpClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    for(int i =0;i<btnList_character_qp.count();i++){
        if(btnList_character_qp.at(i)->hasFocus())
            str.insert(cursorPos,btnList_character_qp.at(i)->text());
    }

    globalConfig();
}

void vkeyworld::character_alClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    for(int i =0;i<btnList_character_al.count();i++){
        if(btnList_character_al.at(i)->hasFocus())
            str.insert(cursorPos,btnList_character_al.at(i)->text());
    }

    globalConfig();
}

void vkeyworld::character_zmClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    for(int i =0;i<btnList_character_zm.count();i++){
        if(btnList_character_zm.at(i)->hasFocus())
            str.insert(cursorPos,btnList_character_zm.at(i)->text());
    }

    globalConfig();
}

void vkeyworld::symbolClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    for(int i =0;i<btnList_symbol.count();i++){
        if(btnList_symbol.at(i)->hasFocus())
            str.insert(cursorPos,btnList_symbol.at(i)->text());
    }

    globalConfig();
}

void vkeyworld::CAPClicked(bool enabled)
{
    globalConfig();
    if(enabled)
        modal_CAP = Capital_High_case;
    else
        modal_CAP = Capital_Lower_case;

    emit sig_Change_CAPModal(modal_CAP);
}

void vkeyworld::ShiftClicked(bool enabled)
{
    if(enabled)
        modal_Shift = ShiftModel;
    else
        modal_Shift = NoShiftModel;

    emit sig_Change_ShiftModal(modal_Shift);
}

void vkeyworld::doChange_CAPModal(int CapModal)
{
    QString HighCase[3][10] = {
        {"Q","W","E","R","T","Y","U","I","O","P"},
        {"A","S","D","F","G","H","J","K","L"},
        {"Z","X","C","V","B","N","M"}
    };

    QString LowerCase[3][10] = {
        {"q","w","e","r","t","y","u","i","o","p"},
        {"a","s","d","f","g","h","j","k","l"},
        {"z","x","c","v","b","n","m"}
    };

    QList <QPushButton *> btnList[3];

    btnList[0] = btnList_character_qp;
    btnList[1] = btnList_character_al;
    btnList[2] = btnList_character_zm;

    if(CapModal){//大写
        for(int j = 0 ;j<3;j++)
            for(int i = 0 ;i < btnList[j].count();i++)
                btnList[j].at(i)->setText(HighCase[j][i]);
    }else{//小写
        for(int j = 0 ;j<3;j++)
            for(int i = 0 ;i < btnList[j].count();i++)
                btnList[j].at(i)->setText(LowerCase[j][i]);
    }
    ui->lineEdit->setFocus();
}

void vkeyworld::doChange_ShiftModal(int ShiftModal)
{
    if(ShiftModal){//Shift模式
        ui->btn_sub->setText("_");
        ui->btn_equ->setText("?");
        ui->btn_sem->setText("|");
        ui->btn_meal->setText("*");
        ui->btn_add->setText("@");
        ui->btn_comma->setText("<");
        ui->btn_dot->setText(">");
        ui->btn_div->setText(":");
        ui->btn_cse->setText("`");
        ui->btn_slant->setText("~");

        doChange_CAPModal(Capital_High_case);//大写
    }else{
        ui->btn_sub->setText("-");
        ui->btn_equ->setText("=");
        ui->btn_sem->setText(";");
        ui->btn_meal->setText("'");
        ui->btn_add->setText("+");
        ui->btn_comma->setText(",");
        ui->btn_dot->setText(".");
        ui->btn_div->setText("/");
        ui->btn_cse->setText("`");
        ui->btn_slant->setText("\\");

        doChange_CAPModal(Capital_Lower_case);//小写
    }
    ui->lineEdit->setFocus();
}

void vkeyworld::BackspaceClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();

    if(cursorPos==0)
        return;

    str.remove(cursorPos-1,1);
    ui->btn_Backspace->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocus();
    ui->lineEdit->setText(str);

    ui->lineEdit->setCursorPosition(cursorPos-1);
}

void vkeyworld::leftClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    ui->lineEdit->setCursorPosition(--cursorPos);
    ui->btn_left->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocus();
}

void vkeyworld::rightClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    ui->lineEdit->setCursorPosition(++cursorPos);
    ui->btn_right->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocus();
}
void vkeyworld::upClicked()
{
    leftClicked();
}

void vkeyworld::downClicked()
{
    rightClicked();
}

void vkeyworld::HomeClicked()
{
    ui->lineEdit->setCursorPosition(0);
    ui->btn_Home->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocus();
}

void vkeyworld::EndClicked()
{
    ui->lineEdit->setCursorPosition(str.count());
    ui->btn_End->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocus();
}

void vkeyworld::spaceClicked()
{
    cursorPos = ui->lineEdit->cursorPosition();
    str.insert(cursorPos,' ');

    ui->btn_space->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocus();

    ui->lineEdit->setText(str);
    ui->lineEdit->setCursorPosition(cursorPos+1);
}

void vkeyworld::on_btn_cancel_clicked()
{
    emit sig_cancel();
    str.clear();
    this->close();
}

void vkeyworld::on_btn_ok_clicked()
{
    str = ui->lineEdit->text();
    emit sig_ok(str);
    str.clear();
    this->close();
}
