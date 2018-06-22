#include "ProgramData.h"

ProgramData_Define::ProgramData_Define(QWidget *parent) :
    QWidget(parent)
{
    Init();
}

ProgramData_Define::~ProgramData_Define()
{
    delete CoordDefineLabel;//*坐标定义 可更改
    delete CoordLabel;   //*坐标 可更改
    delete CurrentCoordLabel;   //当前坐标 可更改
    delete activityToolLabel;   //活动工具  可隐藏 可更改
    delete CurrentactivityToolLabel;   //当前活动工具  可隐藏 可更改
    delete ExplainLabel;//选择一种方法,修改位置后点击"确定"
    delete userMethodLabel;//方法||用户方法 可更改
    delete RightCombox;
    delete targetMethodLabel;//点数||目标方法 可更改
    delete LeftCombox;    //
    delete TableWidget;
    delete PosBtn;
    delete SetPosBtn;
    delete OkBtn;
    delete CancelBtn;

    delete buttonWidget;
    delete TipsWidget;
    delete tablewidget;
}

void ProgramData_Define::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    font.setBold(true); //加粗
    font.setPointSize(12);//字体大小

    TipsWidgetInit();
    tablewidgetInit();
    buttonWidgetInit();
    ConnectInit();

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->setMargin(0);  //边缘
    VLayout->setSpacing(0);
    VLayout->addWidget(TipsWidget,4);
    VLayout->addWidget(tablewidget,5);
    VLayout->addWidget(buttonWidget,1);
    this->setLayout(VLayout);
}

void ProgramData_Define::TipsWidgetInit()
{
    TipsWidget = new QWidget;
    QGridLayout *mainLayout = new QGridLayout;

    CoordDefineLabel = new QLabel(tr("*坐标定义"));
    CoordLabel = new QLabel(tr("*坐标"));
    CurrentCoordLabel = new QLabel(tr("当前坐标"));
    activityToolLabel = new QLabel(tr("活动工具"));
    CurrentactivityToolLabel = new QLabel(tr("当前活动工具"));
    ExplainLabel = new QLabel(tr("选择一种方法,修改位置后点击确定."));
    userMethodLabel = new QLabel(tr("点数||用户方法"));
    LeftCombox =  new QComboBox;    //
    targetMethodLabel = new QLabel(tr("方法||目标方法"));
    RightCombox =  new QComboBox;    //

    mainLayout->addWidget(CoordDefineLabel,0,0);
    mainLayout->addWidget(CoordLabel,1,0);
    mainLayout->addWidget(CurrentCoordLabel,1,1);

    mainLayout->addWidget(activityToolLabel,1,2);
    mainLayout->addWidget(CurrentactivityToolLabel,1,3);

    mainLayout->addWidget(ExplainLabel,2,0,1,2);

    mainLayout->addWidget(userMethodLabel,3,0);
    mainLayout->addWidget(LeftCombox,3,1);
    mainLayout->addWidget(targetMethodLabel,3,2);
    mainLayout->addWidget(RightCombox,3,3);

    mainLayout->setSpacing(10);

    TipsWidget->setLayout(mainLayout);

    TipsWidget->setFont(font);
}

void ProgramData_Define::tablewidgetInit()
{
    tablewidget = new QWidget;
    TableWidget = new QTableWidget;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(TableWidget);
    tablewidget->setLayout(mainLayout);
    mainLayout->setMargin(0);  //边缘
    mainLayout->setSpacing(0);
}

void ProgramData_Define::buttonWidgetInit()
{
    buttonWidget = new QWidget;
    PosBtn = new QPushButton(tr("位置"),buttonWidget);
    SetPosBtn = new QPushButton(tr("修改位置"),buttonWidget);
    OkBtn = new QPushButton(tr("确定"),buttonWidget);
    CancelBtn = new QPushButton(tr("取消"),buttonWidget);

    PosBtn->setFlat(true); //设置按钮为水平状态，默认是突出
    SetPosBtn->setFlat(true); //设置按钮为水平状态，默认是突出
    OkBtn->setFlat(true); //设置按钮为水平状态，默认是突出
    CancelBtn->setFlat(true); //设置按钮为水平状态，默认是突出

    QGridLayout *buttonLayout = new QGridLayout;

    buttonLayout->setColumnStretch(0,1);
    buttonLayout->setColumnStretch(1,1);
    buttonLayout->setColumnStretch(2,1);
    buttonLayout->setColumnStretch(3,1);
    buttonLayout->setColumnStretch(4,1);
    buttonLayout->addWidget(PosBtn,0,0);
    buttonLayout->addWidget(SetPosBtn,0,2);
    buttonLayout->addWidget(OkBtn,0,3);
    buttonLayout->addWidget(CancelBtn,0,4);
    buttonLayout->setSpacing(0);//空隙
    buttonLayout->setMargin(0);//边缘

    PosBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    SetPosBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    OkBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    CancelBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: rgb(145, 145, 145);");

    PosBtn->setFont(font);
    SetPosBtn->setFont(font);
    OkBtn->setFont(font);
    CancelBtn->setFont(font);

}

void ProgramData_Define::ConnectInit()
{
    connect(PosBtn,SIGNAL(clicked()),this,SLOT(PosBtnClicked()));
    connect(SetPosBtn,SIGNAL(clicked()),this,SLOT(SetPosBtnClicked()));
    connect(OkBtn,SIGNAL(clicked()),this,SLOT(OkBtnClicked()));
    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(CancelBtnClicked()));
    connect(LeftCombox,SIGNAL(currentIndexChanged(QString)),this,
            SLOT(do_LeftComboxIndexChanged(QString)));
    connect(RightCombox,SIGNAL(currentIndexChanged(QString)),this,
            SLOT(do_RightComboxIndexChanged(QString)));
}

void ProgramData_Define::PosBtnClicked()
{
    QAction *Allreset = new QAction(tr("全部重置"),buttonWidget);
    QAction *Load = new QAction(tr("加载"),buttonWidget);
    QAction *Save = new QAction(tr("保存"),buttonWidget);

    QMenu *menu=new QMenu;
    menu->setFixedWidth(PosBtn->size().width());

    menu->addAction(Allreset);
    menu->addAction(Load);
    menu->addAction(Save);

    menu->setFont(font);
    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(do_triggered(QAction*)));

    QPoint pos;
    pos.setX(0);
    pos.setY(-menu->sizeHint().height());

//    QAction* Action= menu->exec(PosBtn->mapToGlobal(pos));
    menu->exec(PosBtn->mapToGlobal(pos));
}

void ProgramData_Define::OkBtnClicked()
{
    emit OkBtnClicked_SIG();
}

void ProgramData_Define::CancelBtnClicked()
{
    emit CancelBtnClicked_SIG();
}

void ProgramData_Define::SetPosBtnClicked()
{
    emit SetPosBtnClicked_SIG();
}

void ProgramData_Define::setToolDataWidget()
{
    setCoordDefineLabelText(tr("工具坐标定义"));
    setCoordLabelText(tr("工具坐标:"));
    setCurrentactivityToolLabelHide();
    setactivityToolLabelHide();

    setuserMethodLabelText(tr("方法:"));
    settargetMethodLabelText(tr("点数:"));

    addLeftComboxItem(tr("TCP(默认方向)"));
    addLeftComboxItem(tr("TCP 和 Z"));
    addLeftComboxItem(tr("TCP 和 Z,X"));

    addRightComboxItem(tr("3"));
    addRightComboxItem(tr("4"));
    addRightComboxItem(tr("5"));
    addRightComboxItem(tr("6"));
    addRightComboxItem(tr("7"));
    addRightComboxItem(tr("8"));
    addRightComboxItem(tr("9"));
}

void ProgramData_Define::setWobjDataWidget()
{
    setCoordDefineLabelText(tr("工件坐标定义"));
    setCoordLabelText(tr("工件坐标:"));
    setactivityToolLabelText(tr("活动工具:"));

    setuserMethodLabelText(tr("用户方法:"));
    settargetMethodLabelText(tr("目标方法:"));
//    LeftCombox->addItem(QWidget::tr("未更改"));
//    LeftCombox->addItem(QWidget::tr("3点"));
    addLeftComboxItem(tr("未更改"));
    addLeftComboxItem(tr("3点"));
    addRightComboxItem(tr("未更改"));
    addRightComboxItem(tr("3点"));
//    RightCombox->addItem(QWidget::tr("未更改"));
//    RightCombox->addItem(QWidget::tr("3点"));
}

void ProgramData_Define::do_LeftComboxIndexChanged(QString String)
{
    emit LeftComboxIndexChaged_SIG(String);
}

void ProgramData_Define::do_RightComboxIndexChanged(QString String)
{
    emit RightComboxIndexChaged_SIG(String);
}

void ProgramData_Define::do_triggered(QAction* Action)
{
    emit MenuTriggered_SIG(Action);
}
