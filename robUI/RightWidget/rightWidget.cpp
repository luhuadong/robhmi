#include "rightWidget.h"
#include "ui_rightWidget.h"

rightWidget::rightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rightWidget)
{
    ui->setupUi(this);
    Init();
}

rightWidget::~rightWidget()
{
    delete ui;
}

void rightWidget::Init()
{
    ConnectInit();
    BtnInit();
}

void rightWidget::ConnectInit()
{
    connect(ui->btn_Anticlockwise,SIGNAL(clicked()),this,SIGNAL(btnAnticlockwise_SIG()));
    connect(ui->btn_Clockwise,SIGNAL(clicked()),this,SIGNAL(btnClockwise_SIG()));
    connect(ui->btn_Up,SIGNAL(clicked()),this,SIGNAL(btnUpClicked_SIG()));
    connect(ui->btn_Down,SIGNAL(clicked()),this,SIGNAL(btnDownClicked_SIG()));
    connect(ui->btn_Left,SIGNAL(clicked()),this,SIGNAL(btnLeftClicked_SIG()));
    connect(ui->btn_LeftUp,SIGNAL(clicked()),this,SIGNAL(btnLeftUpClicked_SIG()));
    connect(ui->btn_LeftDown,SIGNAL(clicked()),this,SIGNAL(btnLeftDownClicked_SIG()));
    connect(ui->btn_Right,SIGNAL(clicked()),this,SIGNAL(btnRightClicked_SIG()));
    connect(ui->btn_RightUp,SIGNAL(clicked()),this,SIGNAL(btnRightUpClicked_SIG()));
    connect(ui->btn_RightDown,SIGNAL(clicked()),this,SIGNAL(btnRightDownClicked_SIG()));

    connect(ui->btn_Shortcut_1,SIGNAL(clicked()),this,SIGNAL(btnShortcut_1Clicked_SIG()));
    connect(ui->btn_Shortcut_2,SIGNAL(clicked()),this,SIGNAL(btnShortcut_2Clicked_SIG()));
    connect(ui->btn_Shortcut_3,SIGNAL(clicked()),this,SIGNAL(btnShortcut_3Clicked_SIG()));
    connect(ui->btn_Shortcut_4,SIGNAL(clicked()),this,SIGNAL(btnShortcut_4Clicked_SIG()));

    connect(ui->btn_Change,SIGNAL(clicked()),this,SIGNAL(btnChangeClicked_SIG()));
    connect(ui->btn_ChangeLine,SIGNAL(clicked()),this,SIGNAL(btnChangeLineClicked_SIG()));
    connect(ui->btn_ChangeMoveAxis,SIGNAL(clicked()),this,SIGNAL(btnChangeMoveAxisClicked_SIG()));
    connect(ui->btn_ChangeSpeed,SIGNAL(clicked()),this,SIGNAL(btnChangeSpeedClicked_SIG()));
    connect(ui->btn_ChangeState,SIGNAL(clicked()),this,SIGNAL(btnChangeStateClicked_SIG()));
    connect(ui->btn_ChangeState,SIGNAL(clicked()),this,SLOT(do_btnChangeStateClicked()));

    connect(ui->btn_Run,SIGNAL(clicked()),this,SIGNAL(btnRunClicked_SIG()));
    connect(ui->btn_Next,SIGNAL(clicked()),this,SIGNAL(btnNextClicked_SIG()));
    connect(ui->btn_Prior,SIGNAL(clicked()),this,SIGNAL(btnPriorClicked_SIG()));
    connect(ui->btn_Stop,SIGNAL(clicked()),this,SIGNAL(btnStopClicked_SIG()));

    connect(ui->btn_Close,SIGNAL(clicked()),this,SIGNAL(btnCloseClicked_SIG()));
    connect(ui->btn_Minimize,SIGNAL(clicked()),this,SIGNAL(btnMinimizeClicked_SIG()));
    connect(ui->btn_ChangeLeftView,SIGNAL(clicked()),this,SIGNAL(btnChangeLeftViewClicked_SIG()));
    connect(ui->btn_ShowOrHideLeft,SIGNAL(clicked()),this,SIGNAL(btnShowOrHideLeftClicked_SIG()));

    connect(ui->btn_Enable,SIGNAL(clicked(bool)),this,SIGNAL(btnEnableClicked_SIG(bool)));
    connect(ui->btn_HoldToRun,SIGNAL(clicked(bool)),this,SIGNAL(btnHoldToRunClicked_SIG(bool)));

    connect(ui->radioButton_automatic,SIGNAL(clicked()),this,SIGNAL(radioBtnAutomaticClicked_SIG()));
    connect(ui->radioButton_manual,SIGNAL(clicked()),this,SIGNAL(radioBtnManualClicked_SIG()));
    connect(ui->radioButton_execute,SIGNAL(clicked()),this,SIGNAL(radioBtnExecuteClicked_SIG()));
    connect(ui->btn_MotorEnable,SIGNAL(clicked()),this,SIGNAL(btnMotorEnableClicked_SIG()));
}

void rightWidget::BtnInit()
{
    ui->btn_Enable->setCheckable(true);
    ui->btn_HoldToRun->setCheckable(true);

    ui->radioButton_automatic->setChecked(true);
    ui->widget_ChangeState->close();

    QList <QPushButton*> btnList;
    btnList = this->findChildren<QPushButton*>();

    btnList.removeAt(btnList.indexOf(ui->btn_ChangeState));
    btnList.removeAt(btnList.indexOf(ui->btn_MotorEnable));

    for(int i = 0;i<btnList.count();i++)
        connect(btnList.at(i),SIGNAL(clicked()),this,SLOT(closeWidgetChangeState()));
}

void rightWidget::closeWidgetChangeState()
{
    ui->widget_ChangeState->close();
}

void rightWidget::do_btnChangeStateClicked()
{
    if(ui->widget_ChangeState->isHidden())
        ui->widget_ChangeState->show();
    else
        ui->widget_ChangeState->close();
}

void rightWidget::mousePressEvent(QMouseEvent *event)
{
    if(!(event->type() == QEvent::MouseButtonPress &&event->button()==Qt::LeftButton))
        return;

    if(ui->widget_ChangeState->isHidden())
        ;
    else
        ui->widget_ChangeState->close();

    QWidget::mousePressEvent(event);
}
