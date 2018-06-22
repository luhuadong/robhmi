#include "header/ropageoption/robmanual/newdatatemplatewidget.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QTableView>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QAbstractItemView>
#include <QStringList>
#include <QMenu>
#include <QPixmap>

#include "decode_datatype.h"
#include "decode_typestructs.h"
#include "robotdecodepublic.h"
#include "robotprgfilestruct.h"


/* **************************************************** */
/* ************ 【新数据声明】/【数据声明】界面 ************ */
/* *************************************************** */
NewDataTemplateWidget::NewDataTemplateWidget(ProgramData::DataTypes dataType, QString name, QWidget *parent) :
    QWidget(parent)
{
    //this->setAttribute(Qt::WA_DeleteOnClose);   // 关闭窗口的时候释放窗体部件所占内存
    this->setFixedSize(800, 500);
    this->setStyleSheet("background-color: White;");

    scopeTypeStrList<<tr("全局")<<tr("本地")<<tr("任务");
    storageTypeStrList<<tr("变量")<<tr("可变量")<<tr("常量");
    dimensionStrList<<tr("<无>")<<tr("1")<<tr("2")<<tr("3");


    tipsWidget = new QWidget(this);

    dataTypeKeyLabel = new QLabel(tr("数据类型："), tipsWidget);
    dataTypeValLabel = new QLabel(dataTypesStrList.at(dataType), tipsWidget);
    currTaskKeyLabel = new QLabel(tr("当前任务："), tipsWidget);
    currTaskValLabel = new QLabel(tr("T_ROB1"), tipsWidget);
    QHBoxLayout *tipsLayout = new QHBoxLayout;
    tipsLayout->setMargin(10);
    tipsLayout->setSpacing(0);
    tipsLayout->addWidget(dataTypeKeyLabel);
    tipsLayout->addWidget(dataTypeValLabel);
    tipsLayout->addStretch();
    tipsLayout->addWidget(currTaskKeyLabel);
    tipsLayout->addWidget(currTaskValLabel);
    tipsLayout->addStretch();
    tipsWidget->setLayout(tipsLayout);

    contentWidget = new QWidget(this);

    nameLabel = new QLabel(tr("名称：\t"), contentWidget);
    nameLineEdit = new QLineEdit(name, contentWidget);
    nameLineEdit->setSelection(0, name.size());
    nameBtn = new QPushButton(tr("..."), contentWidget);
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->setMargin(0);
    nameLayout->setSpacing(10);
    nameLayout->addWidget(nameLineEdit);
    nameLayout->addWidget(nameBtn);

    scopeLabel = new QLabel(tr("范围：\t"), contentWidget);
    scopeComboBox = new QComboBox(contentWidget);
    scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_GLOBAL));
    scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_LOCAL));
    scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_TASK));
    scopeComboBox->setCurrentIndex(ProgramData::SCOPE_TASK);    // 设置初选项

    storageTypeLabel = new QLabel(tr("存储类型：\t"), contentWidget);
    storageTypeComboBox = new QComboBox(contentWidget);
    storageTypeComboBox->addItem(storageTypeStrList.at(ProgramData::STORAGE_VAR));
    storageTypeComboBox->addItem(storageTypeStrList.at(ProgramData::STORAGE_PERS));
    storageTypeComboBox->addItem(storageTypeStrList.at(ProgramData::STORAGE_CONST));
    storageTypeComboBox->setCurrentIndex(ProgramData::STORAGE_PERS);    // 设置初选项

    taskLabel = new QLabel(tr("任务：\t"), contentWidget);
    taskComboBox = new QComboBox(contentWidget);
    taskComboBox->addItem(tr("T_ROB1"));
    curTaskNameStr = taskComboBox->currentText();


    moduleLabel = new QLabel(tr("模块：\t"), contentWidget);     // 每次应该获取当前系统最新的情况
    moduleComboBox = new QComboBox(contentWidget);
    //moduleComboBox->addItem(tr("MainModule"));
    //moduleComboBox->addItem(tr("user"));

    int moduleNum = getFileModuleCnt(0);
    module_prg_property tmpModule;
    int i = 0;
    for(i=0; i<moduleNum; i++)
    {
        getSelModuleProperty(0, i, &tmpModule); // 获取模块属性信息
        // char * 转QString
        moduleComboBox->addItem(QString(QLatin1String(tmpModule.moduleName)));
    }
    moduleComboBox->setCurrentIndex(0);
    curModuleNameStr = moduleComboBox->currentText();

    routineLabel = new QLabel(tr("例行程序：\t"), contentWidget);  // 每次应该获取当前系统最新的情况
    routineComboBox = new QComboBox(contentWidget);
    routineComboBox->addItem(tr("<无>"));
    routineComboBox->setEnabled(false);
    curRoutineNameStr = routineComboBox->currentText();


    dimensionLabel = new QLabel(tr("维数：\t"), contentWidget);
    dimensionComboBox = new QComboBox(contentWidget);
    dimensionComboBox->addItem(dimensionStrList.at(ProgramData::DIMENSION_NONE));
    dimensionComboBox->addItem(dimensionStrList.at(ProgramData::DIMENSION_1));
    dimensionComboBox->addItem(dimensionStrList.at(ProgramData::DIMENSION_2));
    dimensionComboBox->addItem(dimensionStrList.at(ProgramData::DIMENSION_3));
    dimensionComboBox->setCurrentIndex(ProgramData::DIMENSION_NONE);
    dimensionLineEdit = new QLineEdit(contentWidget);
    dimensionBtn = new QPushButton(tr("..."), contentWidget);
    dimensionLineEdit->setEnabled(false);
    dimensionBtn->setEnabled(false);
    QHBoxLayout *dimensionLayout = new QHBoxLayout;
    dimensionLayout->setMargin(0);
    dimensionLayout->setSpacing(10);
    dimensionLayout->addWidget(dimensionComboBox);
    dimensionLayout->addWidget(dimensionLineEdit);
    dimensionLayout->addWidget(dimensionBtn);

    QGridLayout *contentLayout = new QGridLayout;
    //contentLayout->setMargin(40);
    contentLayout->setContentsMargins(200, 10, 200, 10);
    contentLayout->setSpacing(10);
    contentLayout->addWidget(nameLabel, 0, 0);
    contentLayout->addLayout(nameLayout, 0, 1);
    contentLayout->addWidget(scopeLabel, 1, 0);
    contentLayout->addWidget(scopeComboBox, 1, 1);
    contentLayout->addWidget(storageTypeLabel, 2, 0);
    contentLayout->addWidget(storageTypeComboBox, 2, 1);
    contentLayout->addWidget(taskLabel, 3, 0);
    contentLayout->addWidget(taskComboBox, 3, 1);
    contentLayout->addWidget(moduleLabel, 4, 0);
    contentLayout->addWidget(moduleComboBox, 4, 1);
    contentLayout->addWidget(routineLabel, 5, 0);
    contentLayout->addWidget(routineComboBox, 5, 1);
    contentLayout->addWidget(dimensionLabel, 6, 0);
    contentLayout->addLayout(dimensionLayout, 6, 1);
    contentWidget->setLayout(contentLayout);


    buttonWidget = new QWidget(this);
    initValBtn = new QPushButton(tr("初始值"), buttonWidget);
    okBtn = new QPushButton(tr("确定"), buttonWidget);
    cancelBtn = new QPushButton(tr("取消"), buttonWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(20);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(initValBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: Gray;");

    connect(scopeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(scopeComboBoxResponded(int)));
    connect(storageTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(storageTypeComboBoxResponded(int)));
    connect(taskComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(taskComboBoxResponded(QString)));
    connect(moduleComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(moduleComboBoxResponded(QString)));
    connect(routineComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(routineComboBoxResponded(QString)));
    connect(dimensionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(dimensionComboBoxResponded(int)));

    connect(initValBtn, SIGNAL(clicked()), this, SLOT(initValBtnClicked()));
    connect(okBtn, SIGNAL(clicked()), this, SIGNAL(okBtnClicked()));
    connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(tipsWidget, 1);
    mainLayout->addWidget(contentWidget, 9);
    mainLayout->addWidget(buttonWidget, 1);
    this->setLayout(mainLayout);

    // 程序数据属性默认设置
    //newDataProperty.typeName = name;    // 2015.11.20 修改到这里 ^_^
    // QString转char *：先将QString转换为QByteArray，再将QByteArray转换为char *。
    QByteArray byteArrayName = name.toLatin1();
    strcpy(newDataProperty.typeName, byteArrayName.data());

    newDataProperty.scope = D_DATATYPE_TASK;
    newDataProperty.storeType = D_DATATYPE_PERS;
    newDataProperty.parentTask;
    newDataProperty.parentModule;
    newDataProperty.parentRoutine;
    newDataProperty.dimension;
}

NewDataTemplateWidget::~NewDataTemplateWidget()
{
    //deleteLater();
}

void NewDataTemplateWidget::initValBtnClicked()
{

}

void NewDataTemplateWidget::scopeComboBoxResponded(int scopeType)
{
    switch (scopeType) {
    case ProgramData::SCOPE_GLOBAL:

        break;
    case ProgramData::SCOPE_LOCAL:

        break;
    case ProgramData::SCOPE_TASK:
        //storageTypeComboBox->clear();

        break;
    default:
        break;
    }
}

void NewDataTemplateWidget::storageTypeComboBoxResponded(int storageType)
{
    ProgramData::ScopeTypes tmpScopeType = (ProgramData::ScopeTypes)scopeComboBox->currentIndex();
    scopeComboBox->clear();

    switch (storageType) {
    case ProgramData::STORAGE_VAR:
    {
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_GLOBAL));
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_LOCAL));
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_TASK));
        scopeComboBox->setCurrentIndex(tmpScopeType);
    }
        break;
    case ProgramData::STORAGE_PERS:
    {
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_GLOBAL));
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_LOCAL));
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_TASK));
        //scopeComboBox->removeItem();    // 2015年11月22日，改到这里
        scopeComboBox->setCurrentIndex(tmpScopeType);
    }
        break;
    case ProgramData::STORAGE_CONST:
    {
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_GLOBAL));
        scopeComboBox->addItem(scopeTypeStrList.at(ProgramData::SCOPE_LOCAL));
        if(tmpScopeType == ProgramData::SCOPE_TASK) {tmpScopeType = ProgramData::SCOPE_GLOBAL;}
        scopeComboBox->setCurrentIndex(tmpScopeType);
    }
        break;
    default:
        break;
    }
}

void NewDataTemplateWidget::taskComboBoxResponded(QString curTaskStr)
{

}
void NewDataTemplateWidget::NewDataTemplateWidget::moduleComboBoxResponded(QString curModuleStr)
{

}

void NewDataTemplateWidget::routineComboBoxResponded(QString curRoutineStr)
{

}

void NewDataTemplateWidget::dimensionComboBoxResponded(int dimension)
{

}


/* ************************************* */
/* ************ 【编辑】界面 ************ */
/* *********************************** */
DataEditTemplateWidget::DataEditTemplateWidget(ProgramData::DataTypes dataType, QString name, QWidget *parent) :
    QWidget(parent)
{
    //this->setFixedSize(680, 500);
    this->setFixedSize(800, 500);
    this->setStyleSheet("background-color: White;");

    /* 提示栏 */
    tipsWidget = new QWidget(this);
    currentKeyLabel = new QLabel(tipsWidget);
    currentValLabel = new QLabel(tipsWidget);
    tipsLabel = new QLabel(tipsWidget);

    currentKeyLabel->setText(tr("名称：\t"));
    currentValLabel->setText(name);
    currentKeyLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    currentValLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    tipsLabel->setText(tr("点击一个字段以编辑值。"));
    tipsLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    QHBoxLayout *currentKeyValLayout = new QHBoxLayout;
    currentKeyValLayout->setMargin(0);
    currentKeyValLayout->setSpacing(0);
    currentKeyValLayout->addWidget(currentKeyLabel);
    currentKeyValLayout->addWidget(currentValLabel);
    currentKeyValLayout->addStretch();
    QVBoxLayout *tipsLayout = new QVBoxLayout;
    tipsLayout->setMargin(10);
    tipsLayout->setSpacing(20);
    tipsLayout->addLayout(currentKeyValLayout);
    tipsLayout->addWidget(tipsLabel);
    tipsWidget->setLayout(tipsLayout);

    /* 内容栏 */
    contentWidget = new QWidget(this);

    contentTabView = new QTableView(contentWidget);
    contentModel = new QStandardItemModel;

    contentModel->setColumnCount(3);
    contentModel->setRowCount(3);   // 对应于特定程序数据值的成员个数，这里随便给个3而已

    contentModel->setHeaderData(0, Qt::Horizontal, "名称");
    contentModel->setHeaderData(1, Qt::Horizontal, "值");
    contentModel->setHeaderData(2, Qt::Horizontal, "数据类型");

    contentTabView->setModel(contentModel);
    contentTabView->verticalHeader()->hide();   // 隐藏垂直表头
    contentTabView->horizontalHeader()->setSectionsClickable(false);    // 设置水平表头不可点击
    QFont font = contentTabView->horizontalHeader()->font();    // 设置水平表头字体加粗
    font.setBold(true);
    contentTabView->horizontalHeader()->setFont(font);
    contentTabView->horizontalHeader()->setFixedHeight(30);
    //ToolWidget->contentTabView->horizontalHeader()->setTextElideMode(Qt::ElideLeft);    // 省略号在左边
    contentTabView->setColumnWidth(0, 150); // 设置第一列宽度为150
    contentTabView->setColumnWidth(1, 350); // 设置第二列宽度为350
    contentTabView->horizontalHeader()->setStretchLastSection(true);    // 设置最后一列充满表宽度
    contentTabView->setSelectionBehavior(QAbstractItemView::SelectRows);    // 设置每次点击选中一整行
    contentTabView->setSelectionMode(QAbstractItemView::SingleSelection);   // 设置每次只能选中一行
    contentTabView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置为不可编辑
    contentTabView->setShowGrid(false); // 设置不显示网格线

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(contentTabView);
    contentWidget->setLayout(contentLayout);



    /* 按钮操作栏 */
    buttonWidget = new QWidget(this);
    okBtn = new QPushButton(buttonWidget);
    cancelBtn = new QPushButton(buttonWidget);
    undoBtn = new QPushButton(buttonWidget);
    boolTrueBtn = new QPushButton(buttonWidget);
    boolFalseBtn = new QPushButton(buttonWidget);

    okBtn->setText(tr("确定"));
    cancelBtn->setText(tr("取消"));
    undoBtn->setText(tr("撤销")); // 【撤销】或【刷新】
    boolTrueBtn->setText(tr("TRUE"));
    boolFalseBtn->setText(tr("FALSE"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(20);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(boolTrueBtn);
    buttonLayout->addWidget(boolFalseBtn);
    buttonLayout->addWidget(undoBtn);
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: Gray;");

    /* 主布局 */
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(tipsWidget, 3);
    mainLayout->addWidget(contentWidget, 7);
    mainLayout->addWidget(buttonWidget, 1);
    this->setLayout(mainLayout);

    connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));
    connect(okBtn, SIGNAL(clicked()), this, SIGNAL(okBtnClicked()));
}

DataEditTemplateWidget::~DataEditTemplateWidget()
{
    //deleteLater();
}


/* ************************************* */
/* ************ 【定义】界面 ************ */
/* *********************************** */
DataDefineTemplateWidget::DataDefineTemplateWidget(ProgramData::DataTypes dataType, QString name, QWidget *parent) :
    QWidget(parent)
{
    //this->setFixedSize(680, 500);
    this->setFixedSize(800, 500);
    this->setStyleSheet("background-color: White;");

    /* 提示栏 */
    tipsWidget = new QWidget(this);
    titleLabel = new QLabel(tipsWidget);
    currentKeyLabel = new QLabel(tipsWidget);
    currentValLabel = new QLabel(tipsWidget);
    tipsLabel = new QLabel(tipsWidget);

    methodLabel = new QLabel(tipsWidget);
    methodComboBox = new QComboBox(tipsWidget);
    numOfPointLabel = new QLabel(tipsWidget);
    numOfPointComboBox = new QComboBox(tipsWidget);

    titleLabel->setText(tr("工具坐标定义"));
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    currentKeyLabel->setText(tr("工具坐标：\t"));
    currentValLabel->setText(name);
    currentKeyLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    currentValLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    tipsLabel->setText(tr("选择一种方法，修改位置后点击“确定”。"));
    tipsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    methodLabel->setText(tr("方法："));
    QStringList methodStrList;
    methodStrList << tr("TCP（默认方向）") << tr("TCP和Z") << tr("TCP和Z，X");
    methodComboBox->addItems(methodStrList);
    numOfPointLabel->setText(tr("点数："));
    QStringList numOfPointStrList;
    numOfPointStrList << tr("3") << tr("4") << tr("5") << tr("6") << tr("7") << tr("8") << tr("9");
    numOfPointComboBox->addItems(numOfPointStrList);

    QHBoxLayout *currentKeyValLayout = new QHBoxLayout;
    currentKeyValLayout->setMargin(0);
    currentKeyValLayout->setSpacing(0);
    currentKeyValLayout->addWidget(currentKeyLabel);
    currentKeyValLayout->addWidget(currentValLabel);
    currentKeyValLayout->addStretch();
    QHBoxLayout *methodLayout = new QHBoxLayout;
    //methodLayout->setMargin(40);
    methodLayout->setContentsMargins(20, 0, 60, 0);
    methodLayout->setSpacing(20);
    methodLayout->addWidget(methodLabel);
    methodLayout->addWidget(methodComboBox);
    methodLayout->addStretch();
    methodLayout->addWidget(numOfPointLabel);
    methodLayout->addWidget(numOfPointComboBox);
    QVBoxLayout *tipsLayout = new QVBoxLayout;
    tipsLayout->setMargin(10);
    tipsLayout->setSpacing(20);
    tipsLayout->addWidget(titleLabel);
    tipsLayout->addLayout(currentKeyValLayout);
    tipsLayout->addWidget(tipsLabel);
    tipsLayout->addLayout(methodLayout);
    tipsWidget->setLayout(tipsLayout);

    /* 内容栏 */
    contentWidget = new QWidget(this);

    contentTabView = new QTableView(contentWidget);
    contentModel = new QStandardItemModel;

    contentModel->setColumnCount(2);
    contentModel->setRowCount(3);   // 对应于特定程序数据值的成员个数，这里随便给个3而已

    contentModel->setHeaderData(0, Qt::Horizontal, "点");
    contentModel->setHeaderData(1, Qt::Horizontal, "状态");

    contentTabView->setModel(contentModel);
    contentTabView->verticalHeader()->hide();   // 隐藏垂直表头
    contentTabView->horizontalHeader()->setSectionsClickable(false);    // 设置水平表头不可点击
    QFont font = contentTabView->horizontalHeader()->font();    // 设置水平表头字体加粗
    font.setBold(true);
    contentTabView->horizontalHeader()->setFont(font);
    contentTabView->horizontalHeader()->setFixedHeight(30);
    //ToolWidget->contentTabView->horizontalHeader()->setTextElideMode(Qt::ElideLeft);    // 省略号在左边
    contentTabView->setColumnWidth(0, 250); // 设置第一列宽度为250
    contentTabView->horizontalHeader()->setStretchLastSection(true);    // 设置最后一列充满表宽度
    contentTabView->setSelectionBehavior(QAbstractItemView::SelectRows);    // 设置每次点击选中一整行
    contentTabView->setSelectionMode(QAbstractItemView::SingleSelection);   // 设置每次只能选中一行
    contentTabView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置为不可编辑
    contentTabView->setShowGrid(false); // 设置不显示网格线

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(contentTabView);
    contentWidget->setLayout(contentLayout);



    /* 按钮操作栏 */
    buttonWidget = new QWidget(this);
    okBtn = new QPushButton(buttonWidget);
    okBtn->setText(tr("确定"));
    cancelBtn = new QPushButton(buttonWidget);
    cancelBtn->setText(tr("取消"));
    modPosBtn = new QPushButton(buttonWidget);
    modPosBtn->setText(tr("修改位置"));

    positonsBtn = new QPushButton(buttonWidget);
    positionsBtnMenu = new QMenu(this);
    positionsBtnMenu->setFixedSize(100, 100);
    resetAllAction = new QAction(tr("全部重载"), this);
    loadAction = new QAction(tr("加载"), this);
    saveAction = new QAction(tr("保存"), this);
    positionsBtnMenu->addAction(resetAllAction);
    positionsBtnMenu->addAction(loadAction);
    positionsBtnMenu->addAction(saveAction);
    positonsBtn->setMenu(positionsBtnMenu);
    positonsBtn->setText(tr("位置"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(20);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(positonsBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(modPosBtn);
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: Gray;");

    /* 主布局 */
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(tipsWidget, 4);
    mainLayout->addWidget(contentWidget, 6);
    mainLayout->addWidget(buttonWidget, 1);
    this->setLayout(mainLayout);

    connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));
    connect(okBtn, SIGNAL(clicked()), this, SIGNAL(okBtnClicked()));
}

DataDefineTemplateWidget::~DataDefineTemplateWidget()
{
    //deleteLater();
}



/* ***************************************** */
/* ************ 【警告对话框】界面 ************ */
/* **************************************** */
WarningDialogTemplateWidget::WarningDialogTemplateWidget(QString message, QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(400, 300);
    this->setStyleSheet("background-color: White; border: 1px solid gray;");

    mainWidget = new QWidget(this);

    topWarningLabel = new QLabel(mainWidget);
    topWarningLabel->setText(tr(" 警告"));
    topWarningLabel->setStyleSheet("font: bold 9pt; color: White; background-color: LightBlue; border-style: none;");
    topWarningLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(1, 1, 1, 0);
    topLayout->setSpacing(0);
    topLayout->addWidget(topWarningLabel);

    // ----------------------
    warningIcon = new QLabel(mainWidget);
    warningIcon->setAlignment(Qt::AlignCenter);
    QPixmap pixmap(QString(":/images/bin/resource/images/warning.png"));
    warningIcon->setPixmap(pixmap);
    warningIcon->setStyleSheet("border-style: none;");

    warningMessage = new QLabel(mainWidget);
    warningMessage->setText(message);
    warningMessage->setAlignment(Qt::AlignCenter);
    warningMessage->setStyleSheet("font: bold 12pt; border-style: none;");

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->setMargin(20);
    contentLayout->setSpacing(20);
    contentLayout->addWidget(warningIcon, 1);
    contentLayout->addWidget(warningMessage, 4);

    // ----------------------
    yesBtn = new QPushButton(mainWidget);
    yesBtn->setText(tr("是"));
    yesBtn->setStyleSheet("border:1px solid gray; font: bold 16pt;");
    noBtn = new QPushButton(mainWidget);
    noBtn->setText(tr("否"));
    noBtn->setStyleSheet("border:1px solid gray; font: bold 16pt;");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setContentsMargins(100, 20, 100, 40);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(yesBtn);
    buttonLayout->addWidget(noBtn);

    // ----------------------
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout, 1);
    mainLayout->addLayout(contentLayout, 6);
    mainLayout->addLayout(buttonLayout, 3);
    mainWidget->setLayout(mainLayout);

    QHBoxLayout *thisLayout = new QHBoxLayout;
    thisLayout->setMargin(0);
    thisLayout->setSpacing(0);
    thisLayout->addWidget(mainWidget);
    this->setLayout(thisLayout);

    connect(yesBtn, SIGNAL(clicked()), this, SIGNAL(yesBtnClicked()));
    connect(noBtn, SIGNAL(clicked()), this, SIGNAL(noBtnClicked()));
}

WarningDialogTemplateWidget::~WarningDialogTemplateWidget()
{
    //deleteLater();
}
