#include "ProgramData.h"

ProgramData_New::ProgramData_New(QWidget *parent) :
    QWidget(parent)
{
    Init();
}

ProgramData_New::~ProgramData_New()
{
    delete DataType;
    delete DataType_INPUT;
    delete currentTask;
    delete currentTask_INPUT;

    delete nameLabel;//名称
    delete nameLineEdit;
    delete OpenVkeyWorld;

    delete scopeLabel;//范围
    delete scopeComboBox;

    delete saveTypeLabel;//存储类型
    delete saveTypeComboBox;

    delete TaskLabel;//任务
    delete TaskComboBox;

    delete moduleLabel;//模块
    delete moduleComboBox;

    delete MainLabel;//例行程序
    delete MainComboBox;

    delete maintainLabel;//维数
    delete maintainComboBox;
    delete maintainLineEdit;
    delete OpenOtherWidget;

    delete InitDataBtn;
    delete okBtn;
    delete cancelBtn;

    delete Widget;
    delete DataTaskWidget;
    delete buttonWidget;
}

void ProgramData_New::buttonWidgetInit()
{
    buttonWidget = new QWidget;
    InitDataBtn = new QPushButton(tr("初始值"),buttonWidget);
    okBtn = new QPushButton(tr("确定"),buttonWidget);
    cancelBtn = new QPushButton(tr("取消"),buttonWidget);

    InitDataBtn->setFlat(true); //设置按钮为水平状态，默认是突出
    okBtn->setFlat(true); //设置按钮为水平状态，默认是突出
    cancelBtn->setFlat(true); //设置按钮为水平状态，默认是突出

    QGridLayout *buttonLayout = new QGridLayout;

    buttonLayout->setColumnStretch(0,1);
    buttonLayout->addWidget(InitDataBtn,0,0);
    buttonLayout->setColumnStretch(1,1);
    buttonLayout->setColumnStretch(2,1);
    buttonLayout->setColumnStretch(3,1);
    buttonLayout->addWidget(okBtn,0,3);
    buttonLayout->setColumnStretch(4,1);
    buttonLayout->addWidget(cancelBtn,0,4);
    buttonLayout->setSpacing(0);//空隙
    buttonLayout->setMargin(0);//边缘

    InitDataBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    okBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    cancelBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: rgb(145, 145, 145);");

    QFont font;
    font.setBold(true); //加粗
    font.setPointSize(12);//字体大小
    InitDataBtn->setFont(font);
    okBtn->setFont(font);
    cancelBtn->setFont(font);
}

void ProgramData_New::WidgetInit()
{
    Widget = new QWidget;

    QGridLayout *GridLayout = new QGridLayout;

    nameLabel = new QLabel(tr("名称:"));
    nameLineEdit = new QLineEdit;
    OpenVkeyWorld = new QPushButton(tr("..."));

    scopeLabel = new QLabel(tr("范围:"));
    scopeComboBox = new QComboBox;

    saveTypeLabel = new QLabel(tr("存储类型:"));
    saveTypeComboBox = new QComboBox;

    TaskLabel = new QLabel(tr("任务:"));
    TaskComboBox = new QComboBox;

    moduleLabel = new QLabel(tr("模块:"));
    moduleComboBox = new QComboBox;
    MainLabel = new QLabel(tr("例行程序:"));
    MainComboBox = new QComboBox;

    maintainLabel = new QLabel(tr("维数:"));
    maintainComboBox = new QComboBox;
    maintainLineEdit = new QLineEdit;
    OpenOtherWidget = new QPushButton;

    GridLayout->setColumnStretch(0,1);//设置头尾列的比例
    GridLayout->setColumnStretch(6,1);//

    GridLayout->addWidget(nameLabel,0,1);
    GridLayout->addWidget(nameLineEdit,0,3,1,2);
    GridLayout->addWidget(OpenVkeyWorld,0,5);

    GridLayout->addWidget(scopeLabel,1,1);
    GridLayout->addWidget(scopeComboBox,1,3,1,3);
    GridLayout->addWidget(saveTypeLabel,2,1);
    GridLayout->addWidget(saveTypeComboBox,2,3,1,3);
    GridLayout->addWidget(TaskLabel,3,1);
    GridLayout->addWidget(TaskComboBox,3,3,1,3);
    GridLayout->addWidget(moduleLabel,4,1);
    GridLayout->addWidget(moduleComboBox,4,3,1,3);
    GridLayout->addWidget(MainLabel,5,1);
    GridLayout->addWidget(MainComboBox,5,3,1,3);

    GridLayout->addWidget(maintainLabel,6,1);
    GridLayout->addWidget(maintainComboBox,6,3);
    GridLayout->addWidget(maintainLineEdit,6,4);
    GridLayout->addWidget(OpenOtherWidget,6,5);

    GridLayout->setMargin(10);//边缘
    GridLayout->setSpacing(15);//空隙
    Widget->setLayout(GridLayout);

    QFont font;
    font.setBold(true); //加粗
//    font.setPixelSize(12);//像素
//    font.setFamily("幼圆");//字体
//    font.setOverline(true); //上划线
//    font.setUnderline(true);//下划线
    font.setPointSize(12);//字体大小
    this->setFont(font);
}

void ProgramData_New::DataTaskWidgetInit()
{
    DataTaskWidget  = new QWidget;

    QGridLayout *DataTaskLayout = new QGridLayout;

    DataType = new QLabel(tr("数据类型:"));
//    DataType->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    DataType_INPUT = new QLabel(tr("数据类型"));
    currentTask = new QLabel(tr("当前任务:"));
    currentTask_INPUT = new QLabel(tr("当前任务"));

    DataTaskLayout->addWidget(DataType,0,0);
    DataTaskLayout->addWidget(DataType_INPUT,0,1,1,2);
    DataTaskLayout->addWidget(currentTask,0,3);
    DataTaskLayout->addWidget(currentTask_INPUT,0,4,1,2);

    DataTaskWidget->setLayout(DataTaskLayout);
}

void ProgramData_New::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    WidgetInit();
    buttonWidgetInit();
    DataTaskWidgetInit();

    ConnectInit();

    QVBoxLayout *VLayout = new QVBoxLayout;    
    VLayout->setMargin(0);  //边缘
    VLayout->setSpacing(0);
    VLayout->addWidget(DataTaskWidget,1);
    VLayout->addWidget(Widget,8);
    VLayout->addWidget(buttonWidget,1);
    this->setLayout(VLayout);
}

void ProgramData_New::ConnectInit()
{
    connect(InitDataBtn,SIGNAL(clicked()),this,SLOT(InitDataBtnClicked()));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(OkBtnClicked()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(CancelBtnClicked()));
    connect(OpenVkeyWorld,SIGNAL(clicked()),this,SLOT(OpenVkeyWorldBtnClicked()));
    connect(OpenOtherWidget,SIGNAL(clicked()),this,SLOT(OpenOtherWidgetBtnClicked()));
}

void ProgramData_New::InitDataBtnClicked()
{
    emit InitDataBtnClicked_SIG();
}

void ProgramData_New::OkBtnClicked()
{
    emit OkBtnClicked_SIG();
}

void ProgramData_New::CancelBtnClicked()
{
    emit CancelBtnClicked_SIG();
}

void ProgramData_New::OpenVkeyWorldBtnClicked()
{
    emit OpenVkeyWorldBtnClicked_SIG();
}

void ProgramData_New::OpenOtherWidgetBtnClicked()
{
    emit OpenOtherWidgetBtnClicked_SIG();
}

void ProgramData_New::setNameLineEditText(QString string)
{
    nameLineEdit->setText(string);
}

QString ProgramData_New::getnameLineEditText()
{
    return nameLineEdit->text();
}

void ProgramData_New::setMaintainLineEditText(QString string)
{
    maintainLineEdit->setText(string);
}

QString ProgramData_New::getMaintainLineEditText()
{
    return maintainLineEdit->text();
}

