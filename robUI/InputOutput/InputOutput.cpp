#include "InputOutput.h"
#include "ui_InputOutput.h"

InputOutput::InputOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputOutput)
{
    ui->setupUi(this);

    Init();
}

InputOutput::~InputOutput()
{
    delete ui;
}

void InputOutput::setlabel_filterShowText(QString s)
{
    ui->label_filterShow->setText(s);
}

void InputOutput::setlabel_currentIOTypeText(QString s)
{
    ui->label_currentIOType->setText(s);
}

void InputOutput::setlabel_filterShowHide(bool Hideen)
{
    if(Hideen)
        ui->label_filterShow->hide();
    else
        ui->label_filterShow->show();
}

void InputOutput::setlabel_filterHide(bool Hideen)
{
    if(Hideen)
        ui->label_filter->hide();
    else
        ui->label_filter->show();
}

void InputOutput::setlabel_ChooseLayoutHide(bool Hideen)
{
    if(Hideen)
        ui->label_ChooseLayout->hide();
    else
        ui->label_ChooseLayout->show();
}

void InputOutput::setlabel_ChooseIOHide(bool Hideen)
{
    if(Hideen)
        ui->label_ChooseIO->hide();
    else
        ui->label_ChooseIO->show();
}

void InputOutput::setcomboBox_LayoutHide(bool Hideen)
{
    if(Hideen)
        ui->comboBox_Layout->hide();
    else
        ui->comboBox_Layout->show();
}

void InputOutput::setBtn_0Hide(bool Hideen)
{
    if(Hideen)
        ui->Btn_0->hide();
    else
        ui->Btn_0->show();
}

void InputOutput::setBtn_1Hide(bool Hideen)
{
    if(Hideen)
        ui->Btn_1->hide();
    else
        ui->Btn_1->show();
}

void InputOutput::setBtn_refreshHide(bool Hideen)
{
    if(Hideen)
        ui->Btn_refresh->hide();
    else
        ui->Btn_refresh->show();
}

void InputOutput::setBtn_FilterHide(bool Hideen)
{
    if(Hideen)
        ui->Btn_Filter->hide();
    else
        ui->Btn_Filter->show();
}

void InputOutput::BtnInit()
{

}

void InputOutput::on_Btn_1_clicked()
{

}

void InputOutput::on_Btn_0_clicked()
{

}

void InputOutput::on_Btn_Filter_clicked()
{
//    setcomboBox_LayoutHide(true);
}

void InputOutput::on_Btn_View_clicked(bool checked)
{
    if(checked && MenuShow){

        MenuHide = false;
    }else{
//        MenuHide = true;
//        QPoint pos;
//        pos.setX(0);
//        pos.setY(-menu->sizeHint().height());
//        menu->exec(ui->Btn_View->mapToGlobal(pos));;
    }
}

void InputOutput::do_menuHide()
{
//    if(menu->isHidden()&& ui->Btn_View->isChecked())
//        ui->Btn_View->setChecked(false);
    if(/*ui->Btn_View->isChecked() &&*/!MenuHide){
        ui->Btn_View->setChecked(false);
        MenuHide = true
                ;
//        MenuShow = true;
    }

}

void InputOutput::do_menuShow()
{
//    ui->Btn_View->setChecked(true);
//    MenuHide = false;
}

void InputOutput::Init()
{
    MenuHide = true;
    MenuShow = true;
    meltName = new QAction(tr("化名I/O"),ui->widget_Btn);
    industrynetwork = new QAction(tr("工业网络"),ui->widget_Btn);
    IOdevice = new QAction(tr("IO设备"),ui->widget_Btn);
    AllSIGNAL = new QAction(tr("全部信号"),ui->widget_Btn);
    digitInput = new QAction(tr("数字输入"),ui->widget_Btn);
    digitOutput = new QAction(tr("数字输出"),ui->widget_Btn);
    imitateInput = new QAction(tr("模拟输入"),ui->widget_Btn);
    imitateOutput = new QAction(tr("模拟输出"),ui->widget_Btn);
    groupInput = new QAction(tr("组输入"),ui->widget_Btn);
    groupOutput = new QAction(tr("组输出"),ui->widget_Btn);
    incommonuse = new QAction(tr("常用"),ui->widget_Btn);
    safeSIGNAl = new QAction(tr("安全信号"),ui->widget_Btn);
    simulationSIGNAl = new QAction(tr("仿真信号"),ui->widget_Btn);

    menu=new QMenu;
    QMenu *menu1=new QMenu;
    menu1->addAction(meltName);

    menu->setFixedWidth(ui->Btn_View->size().width());
//    menu->setGeometry(0,0,680,500);
    menu->addAction(meltName);
    menu->addAction(industrynetwork);
    menu->addAction(IOdevice);
    menu->addAction(AllSIGNAL);
    menu->addAction(digitInput);
    menu->addAction(digitOutput);
    menu->addAction(imitateInput);
    menu->addAction(imitateOutput);
    menu->addAction(groupInput);
    menu->addAction(groupOutput);
    menu->addAction(incommonuse);
    menu->addAction(safeSIGNAl);
    menu->addAction(simulationSIGNAl);

    connect(menu,SIGNAL(aboutToShow()),this,SLOT(do_menuShow()));
    connect(menu,SIGNAL(aboutToHide()),this,SLOT(do_menuHide()));
    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(do_menutriggered(QAction*)));

//    QPoint pos;
//    pos.setX(0);
//    pos.setY(-menu->sizeHint().height());
//    menu->
//    menu->exec(ui->Btn_View->mapToGlobal(pos));
    ui->Btn_View->setMenu(menu);
//    ui->Btn_View->menu()->exec(ui->Btn_View->mapToGlobal(pos));


}

void InputOutput::do_menutriggered(QAction *Action)
{
    QString action[] = {
        tr("化名I/O"),tr("工业网络"),tr("IO设备"),tr("全部信号"),tr("数字输入"),
        tr("数字输出"),tr("模拟输入"),tr("模拟输出"),tr("组输入"),tr("组输出"),
        tr("常用"),tr("安全信号"),tr("仿真信号")
    };
    for(int i = 0;i<13;i++){
        if(Action->text() == action[i]){
            ChangeView(i);
        }
    }
}
