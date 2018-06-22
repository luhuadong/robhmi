#include "header/ropageoption/robmanual/manualsubtemplatewidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QIcon>

#include "decode_datatype.h"
#include "decode_typestructs.h"
#include "robotdecodepublic.h"
#include "robotprgfilestruct.h"

ManualSubTemplateWidget::ManualSubTemplateWidget(QWidget *parent) :
    QWidget(parent)
{
    //this->setFixedSize(680, 500);
    this->setFixedSize(800, 500);
    //this->setStyleSheet("background-color: Lemonchiffon");
    this->setStyleSheet("background-color: White;");
    //this->setStyleSheet("QToolButton{ border: 5px solid LightBlue; background-color: LightGray; }");

    /* 提示栏 */
    tipsWidget = new QWidget(this);
    currentKeyLabel = new QLabel(tipsWidget);
    currentValLabel = new QLabel(tipsWidget);
    tipsLabel = new QLabel(tipsWidget);

    currentKeyLabel->setText(tr("当前选择：\t"));
    currentValLabel->setText(tr("None"));
    currentKeyLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    currentValLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    tipsLabel->setText(tr("tips ..."));
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
    //contentWidget->setStyleSheet("border-top: 1px solid Black; border-bottom: 1px solid Black;");

    /* 按钮操作栏 */
    buttonWidget = new QWidget(this);
    okBtn = new QPushButton(buttonWidget);
    cancelBtn = new QPushButton(buttonWidget);
    newBtn = new QPushButton(buttonWidget);
    //editBtn = new EditBtn(buttonWidget);
    editBtn = new QPushButton(buttonWidget);

    /* ************* */
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

    editBtn->setMenu(editBtnMenu);
    editBtn->setText(tr("编辑"));
    /* ************* */

    okBtn->setText(tr("确定"));
    cancelBtn->setText(tr("取消"));
    newBtn->setText(tr("新建"));
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(20);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(newBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: Gray;");
    newBtn->hide();
    editBtn->hide();


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(tipsWidget, 3);  
    mainLayout->addWidget(contentWidget, 7);
    mainLayout->addWidget(buttonWidget, 1);
    this->setLayout(mainLayout);

    //connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(closeWidget()));
    connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));
    connect(okBtn, SIGNAL(clicked()), this, SIGNAL(okBtnClicked()));
}

void ManualSubTemplateWidget::setContentWidgetLayout(QLayout *contentLayout)
{
    contentWidget->setLayout(contentLayout);
}


void ManualSubTemplateWidget::setCurrentKeyText(QString text)
{
    currentKeyLabel->setText(text);
}

void ManualSubTemplateWidget::setCurrentValText(QString text)
{
    currentValLabel->setText(text);
}

void ManualSubTemplateWidget::setTipsText(QString tips)
{
    tipsLabel->setText(tips);
}

/* **************************************************** */
/* ******************** 【转到】界面 ******************** */
/* *************************************************** */
GoToPosTemplateWidget::GoToPosTemplateWidget(QWidget *parent) :
    QWidget(parent)
{
    //this->setFixedSize(680, 500);
    this->setFixedSize(800, 500);
    this->setStyleSheet("background-color: White;");

    /* 提示栏 */
    tipsWidget = new QWidget(this);

    mechanicalUnitKeyLabel = new QLabel(tipsWidget);  // 机械单元
    mechanicalUnitValLabel = new QLabel(tipsWidget);
    activeToolKeyLabel = new QLabel(tipsWidget);      // 活动工具
    activeToolValLabel = new QLabel(tipsWidget);
    activeWobjKeyLabel = new QLabel(tipsWidget);      // 活动工件
    activeWobjValLabel = new QLabel(tipsWidget);

    mechanicalUnitKeyLabel->setText(tr("机械单元：\t"));
    mechanicalUnitValLabel->setText(tr("ROB_1"));
    activeToolKeyLabel->setText(tr("活动工具：\t"));
    activeToolValLabel->setText(tr("tool0"));
    activeWobjKeyLabel->setText(tr("活动工件：\t"));
    activeWobjValLabel->setText(tr("wobj0"));

    //currentKeyLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    //currentValLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    QGridLayout *tipsLayout = new QGridLayout;
    //tipsLayout->setMargin(20);
    tipsLayout->setContentsMargins(20, 20, 300, 30);
    tipsLayout->setSpacing(20);
    tipsLayout->addWidget(mechanicalUnitKeyLabel, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    tipsLayout->addWidget(mechanicalUnitValLabel, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    tipsLayout->addWidget(activeToolKeyLabel, 1, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    tipsLayout->addWidget(activeToolValLabel, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    tipsLayout->addWidget(activeWobjKeyLabel, 2, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    tipsLayout->addWidget(activeWobjValLabel, 2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
//    tipsLayout->addWidget(mechanicalUnitKeyLabel, 0, 0);
//    tipsLayout->addWidget(mechanicalUnitValLabel, 0, 1);
//    tipsLayout->addWidget(activeToolKeyLabel, 1, 0);
//    tipsLayout->addWidget(activeToolValLabel, 1, 1);
//    tipsLayout->addWidget(activeWobjKeyLabel, 2, 0);
//    tipsLayout->addWidget(activeWobjValLabel, 2, 1);
    tipsWidget->setLayout(tipsLayout);

    /* 内容栏 */
    contentWidget = new QWidget(this);
    //contentWidget->setStyleSheet("border-top: 1px solid Black; border-bottom: 1px solid Black;");

    robtargetListWidget = new QListWidget(contentWidget);   // 显示当前任务中的机器人示教点列表

    activeFilterKeyLabel = new QLabel(contentWidget); // 活动过滤器： XXX
    activeFilterKeyLabel->setText(tr("活动过滤器：\t"));
    activeFilterValLabel = new QLabel(contentWidget);
    activeFilterValLabel->setText(tr("None"));
    // 按住“启动装置”(1.Press and hold Enabling Device.)
    step1Label = new QLabel(contentWidget);
    step1Label->setText(tr("1. 按住“启动装置”"));
    // 按住“转到”按钮，转到位置Px(2.Press and hold Go To button to go to position Px)
    step2Label = new QLabel(contentWidget);
    step2Label->setText(tr("1. 按住“转到”按钮，转到位置。"));
    goToPosBtn = new QPushButton(contentWidget);    // “转到”按钮
    goToPosBtn->setText(tr("转到"));

    QHBoxLayout *contentRightTopLayout = new QHBoxLayout;
    contentRightTopLayout->setMargin(0);
    contentRightTopLayout->setSpacing(0);
    contentRightTopLayout->addWidget(activeFilterKeyLabel);
    contentRightTopLayout->addWidget(activeFilterValLabel);
    contentRightTopLayout->addStretch();

    QVBoxLayout *contentRightLayout = new QVBoxLayout;
    contentRightLayout->setMargin(20);
    contentRightLayout->setSpacing(20);
    contentRightLayout->addLayout(contentRightTopLayout);
    contentRightLayout->addWidget(step1Label);
    contentRightLayout->addWidget(step2Label);
    contentRightLayout->addStretch();
    contentRightLayout->addWidget(goToPosBtn);

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->setMargin(0);
    contentLayout->setSpacing(0);
    contentLayout->addWidget(robtargetListWidget, 6);
    contentLayout->addLayout(contentRightLayout, 4);
    contentWidget->setLayout(contentLayout);

    /* 按钮操作栏 */
    buttonWidget = new QWidget(this);
    filterBtn = new QPushButton(buttonWidget);
    //filterBtn->setText(tr("过滤"));


    closeBtn = new QPushButton(buttonWidget);
    closeBtn->setText(tr("关闭"));
    //okBtn = new QPushButton(buttonWidget);
    //cancelBtn = new QPushButton(buttonWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(20);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(filterBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeBtn);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: Gray;");

    /* ************* */
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(tipsWidget, 3);
    mainLayout->addWidget(contentWidget, 7);
    mainLayout->addWidget(buttonWidget, 1);
    this->setLayout(mainLayout);


    QPixmap pixmap(QString(":/images/bin/resource/images/filter.png"));
    //QIcon &filterIcon(pixmap);
    //filterBtn->setIcon(filterIcon);
    filterBtn->setIcon(pixmap);
    //filterBtn->setIconSize(pixmap.height()>buttonWidget->height()?QSize(buttonWidget->height(),buttonWidget->height()):pixmap.size());

    connect(goToPosBtn, SIGNAL(pressed()), this, SLOT(goToPosBtnPressed()));
    connect(goToPosBtn, SIGNAL(released()), this, SLOT(goToPosBtnReleased()));

    connect(closeBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));
    //connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));
    //connect(okBtn, SIGNAL(clicked()), this, SIGNAL(okBtnClicked()));

    //sysInitRobTarget = pOutputData->curRob; // 定义一个机器人位置点，用于测试【转到】功能
    pInputData->tarRob = sysInitRobTarget;	//直接手动运动到指定位置(基坐标系)
}

GoToPosTemplateWidget::~GoToPosTemplateWidget()
{
    //deleteLater();
}

void GoToPosTemplateWidget::goToPosBtnPressed()
{
    // 是否有一些点被插补算法认为无法到达，所以按键动作失效？——2015.11.13
    // 问题描述：有时候按键失灵，但是一旦按键进入转到模式后就不再失灵。。。
    mode = pInputData->mode;
    pInputData->mode = ITP_Mode_JointOp_PosMode;    // 切换模式的操作应该在为速度和位置赋值之前还是之后？

    //pOutputData->inpos;
    //pOutputData->moving;
    //pOutputData->curRob;

    pInputData->robotPosSpeed.v_ort = (MaxSpeed_Reorient * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;
    pInputData->robotPosSpeed.v_tcp = (MaxSpeed_Linear * interpolatePeriod / 1000) * JoggingSpeedRate * SysSpeedRate;

    //pInputData->mode = ITP_Mode_JointOp_PosMode;    // 切换模式的操作应该在为速度和位置赋值之前还是之后？
    qDebug("<GoToBtn pressed>");
}

void GoToPosTemplateWidget::goToPosBtnReleased()
{
    pOutputData->curJointSpeed;
    pInputData->mode = mode;
    pInputData->robotPosSpeed.v_ort = 0;    // 工具方向速度 radian/插补周期
    pInputData->robotPosSpeed.v_tcp = 0;    // 工具轨迹速度 mm/插补周期

    qDebug("<GoToBtn released>");
}





/* **************************************************** */
/* ******** 【工具坐标】/【工件坐标】/【有效载荷】界面 ******* */
/* *************************************************** */
ManualTableWidget::ManualTableWidget(Jogging::MANUALSUBWIDGET widgetType, QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(800, 500);
    this->setStyleSheet("background-color: White;");
    curWidgetType = widgetType;

    QString tabHeaderName = tr("名称");
    decode_typestruct dataType;
    if(widgetType == Jogging::TOOL)
    {
        tabHeaderName = tr("工具名称");
        dataType = D_DATATYPE_TOOLDATA;
    }
    else if(widgetType == Jogging::WORK_OBJECT)
    {
        tabHeaderName = tr("工件名称");
        dataType = D_DATATYPE_WOBJDATA;
    }
    else if(widgetType == Jogging::PAY_LOAD)
    {
        tabHeaderName = tr("有效载荷名称");
        dataType = D_DATATYPE_LOADDATA;
    }
    else
    {
        //dataType = D_DATATYPE_TOOLDATA;   // 错误
    }
    qDebug("===============\ndataType = %d", dataType);

    /* 提示栏 */
    tipsWidget = new QWidget(this);
    currentKeyLabel = new QLabel(tipsWidget);
    currentValLabel = new QLabel(tipsWidget);
    tipsLabel = new QLabel(tipsWidget);

    currentKeyLabel->setText(tr("当前选择：\t"));
    currentValLabel->setText(tr("None"));
    tipsLabel->setText(tr("从列表中选择一个项目。"));
    tipsLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    QGridLayout *tipsLayout = new QGridLayout;
    tipsLayout->setContentsMargins(20, 20, 300, 30);
    tipsLayout->setSpacing(20);
    tipsLayout->addWidget(currentKeyLabel, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignBottom);
    tipsLayout->addWidget(currentValLabel, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignBottom);
    tipsLayout->addWidget(tipsLabel, 1, 0, 1, 2, Qt::AlignLeft | Qt::AlignBottom);
    tipsWidget->setLayout(tipsLayout);


    /* 内容栏 */
    contentWidget = new QWidget(this);
    //contentWidget->setStyleSheet("border-top: 1px solid Black; border-bottom: 1px solid Black;");

    tabView = new QTableView(contentWidget);
    tabModel = new QStandardItemModel;
    itemCntLabel = new QLabel(contentWidget);
    itemCntLabel->setStyleSheet("background-color: transparent; color: Purple;");
    //itemCntLabel->setText(tr("count:"));
    itemCntLabel->setGeometry(720, 10, 80, 20);  // 位置定义在这里，但是用绝对位置定义真的好吗？


    tabModel->setColumnCount(3);
    //tabModel->setRowCount(3); // 先不设行数
    tabModel->setHeaderData(0, Qt::Horizontal, tabHeaderName);
    tabModel->setHeaderData(1, Qt::Horizontal, "模块");
    tabModel->setHeaderData(2, Qt::Horizontal, "范围");

    tabView->setModel(tabModel);
    tabView->verticalHeader()->hide();   // 隐藏垂直表头
    tabView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 不显示垂直滚动条
    tabView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 不显示水平滚动条
    tabView->horizontalHeader()->setSectionsClickable(false);    // 设置水平表头不可点击
    QFont font = tabView->horizontalHeader()->font();    // 设置水平表头字体加粗
    font.setBold(true);
    tabView->horizontalHeader()->setFont(font);
    tabView->horizontalHeader()->setFixedHeight(30);
    //tabView->horizontalHeader()->setTextElideMode(Qt::ElideLeft);    // 超出显示区域时省略号在左边
    tabView->setColumnWidth(0, 200); // 设置第一列宽度为150
    tabView->setColumnWidth(1, 350); // 设置第二列宽度为350
    tabView->horizontalHeader()->setStretchLastSection(true);    // 设置最后一列充满表宽度
    tabView->setSelectionBehavior(QAbstractItemView::SelectRows);    // 设置每次点击选中一整行
    tabView->setSelectionMode(QAbstractItemView::SingleSelection);   // 设置每次只能选中一行
    tabView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置为不可编辑
    tabView->setShowGrid(false); // 设置不显示网格线

    // ==================== 表格内容显示
    int moduleNum = getFileModuleCnt(0);
    qDebug("moduleNum = %d", moduleNum);
    decode_type_property tmpProperty;
    module_prg_property tmpModule;
    int i = 0, j = 0, rowCnt = 0;

    for(i=0; i<moduleNum; i++)
    {
        j = 0;
        getSelModuleProperty(0, i, &tmpModule);
        while(1 == usePosGetSelVarProperty(0, i, -1, j, dataType, &tmpProperty))
        {
            // 手动操纵可用的TOOLDATA一定是PERS类型的，且不能是LOCAL的
            if(tmpProperty.storeType != D_DATATYPE_PERS || tmpProperty.scope == D_DATATYPE_LOCAL) continue;

            qDebug("typeName = %s", tmpProperty.typeName);
            QStandardItem *itemName = new QStandardItem(tmpProperty.typeName);
            tabModel->setItem(rowCnt, 0, itemName);
            //QStandardItem *itemModule = new QStandardItem(QString::number(tmpProperty.parentModule));
            QStandardItem *itemModule = new QStandardItem(tmpModule.moduleName);
            tabModel->setItem(rowCnt, 1, itemModule);
            QStandardItem *itemScope = new QStandardItem(tmpProperty.scope == D_DATATYPE_TASK ? tr("任务") : tr("全局"));
            tabModel->setItem(rowCnt, 2, itemScope);
            rowCnt++;
            j++;
        }
    }
    // 紫色字体的可选数量提示
    if(rowCnt > 0) {itemCntLabel->setText(tr("1 到 ") + QString::number(rowCnt) + tr(" 共 ") + QString::number(rowCnt));}

    tabView->setCurrentIndex(tabModel->index(0, 0)); // 设置当前选中第一行第一列
    // 被选中的某行的数据显示在提示栏
    currentValLabel->setText(tabView->currentIndex().data().toString());

    connect(tabView, SIGNAL(pressed(QModelIndex)), this, SLOT(tabViewClicked(QModelIndex)));

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(tabView);
    contentWidget->setLayout(contentLayout);



    /* 按钮操作栏 */
    buttonWidget = new QWidget(this);
    okBtn = new QPushButton(buttonWidget);
    cancelBtn = new QPushButton(buttonWidget);
    newBtn = new QPushButton(buttonWidget);
    editBtn = new QPushButton(buttonWidget);

    /* ************* */
    editBtnMenu = new QMenu(this);
    //editBtnMenu->setFixedSize(100, 220);

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

    editBtn->setMenu(editBtnMenu);
    editBtn->setText(tr("编辑"));
    /* ************* */

    okBtn->setText(tr("确定"));
    cancelBtn->setText(tr("取消"));
    newBtn->setText(tr("新建"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(20);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(newBtn);
    buttonLayout->addWidget(editBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background-color: Gray;");


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(tipsWidget, 3);
    mainLayout->addWidget(contentWidget, 7);
    mainLayout->addWidget(buttonWidget, 1);
    this->setLayout(mainLayout);

    connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(cancelBtnClicked()));
    connect(okBtn, SIGNAL(clicked()), this, SIGNAL(okBtnClicked()));

    connect(newBtn, SIGNAL(clicked()), this, SLOT(newBtnRespond()));

    connect(modValAction, SIGNAL(triggered()), this, SLOT(modValActionRespond()));
    connect(modDecAction, SIGNAL(triggered()), this, SLOT(modDecActionRespond()));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyActionRespond()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteActionRespond()));
    connect(defineAction, SIGNAL(triggered()), this, SLOT(defineActionRespond()));
}

ManualTableWidget::~ManualTableWidget()
{
    //deleteLater();
}

void ManualTableWidget::tabViewClicked(QModelIndex modelIndex)
{
    tabView->setCurrentIndex(tabModel->index(modelIndex.row(), 0));
    currentValLabel->setText(tabView->currentIndex().data().toString());
}

// 新建
void ManualTableWidget::newBtnRespond()
{
    NewDataTemplateWidget *newDataUI;

    if(curWidgetType == Jogging::TOOL)
    {
        newDataUI = new NewDataTemplateWidget(ProgramData::TOOL_DATA, QString(tr("NewTool")), this);
    }
    else if(curWidgetType == Jogging::WORK_OBJECT)
    {
        newDataUI = new NewDataTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobjdata0")), this);
    }
    else if(curWidgetType == Jogging::PAY_LOAD) // 未定义
    {
        newDataUI = new NewDataTemplateWidget(ProgramData::LOAD_DATA, QString(tr("loaddata0")), this);
    }

    newDataUI->setAttribute(Qt::WA_DeleteOnClose);
    newDataUI->show();
    connect(newDataUI, SIGNAL(okBtnClicked()), newDataUI, SLOT(close()));
    connect(newDataUI, SIGNAL(cancelBtnClicked()), newDataUI, SLOT(close()));

}

// 更改值
void ManualTableWidget::modValActionRespond()
{
    DataEditTemplateWidget *modValUI;

    if(curWidgetType == Jogging::TOOL)
    {
        modValUI = new DataEditTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tool_x")), this);
    }
    else if(curWidgetType == Jogging::WORK_OBJECT)
    {
        modValUI = new DataEditTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobj_x")), this);
    }
    else if(curWidgetType == Jogging::PAY_LOAD)
    {
        modValUI = new DataEditTemplateWidget(ProgramData::LOAD_DATA, QString(tr("load_x")), this);
    }

    modValUI->setAttribute(Qt::WA_DeleteOnClose);
    modValUI->show();
    connect(modValUI, SIGNAL(okBtnClicked()), modValUI, SLOT(close()));
    connect(modValUI, SIGNAL(cancelBtnClicked()), modValUI, SLOT(close()));
}

// 更改声明
void ManualTableWidget::modDecActionRespond()
{
    NewDataTemplateWidget *newDataUI;

    if(curWidgetType == Jogging::TOOL)
    {
        newDataUI = new NewDataTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tooldata0")), this);
    }
    else if(curWidgetType == Jogging::WORK_OBJECT)
    {
        newDataUI = new NewDataTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobjdata0")), this);
    }
    else if(curWidgetType == Jogging::PAY_LOAD)
    {
        newDataUI = new NewDataTemplateWidget(ProgramData::LOAD_DATA, QString(tr("loaddata0")), this);
    }

    newDataUI->setAttribute(Qt::WA_DeleteOnClose);
    newDataUI->show();
    connect(newDataUI, SIGNAL(okBtnClicked()), newDataUI, SLOT(close()));
    connect(newDataUI, SIGNAL(cancelBtnClicked()), newDataUI, SLOT(close()));
}

// 复制
void ManualTableWidget::copyActionRespond()
{

}

// 删除
void ManualTableWidget::deleteActionRespond()
{
    WarningDialogTemplateWidget *warningUI;
    warningUI = new WarningDialogTemplateWidget(QString(tr("确定删除“tool_x”？\n此操作不可撤销。")), this);
    warningUI->setAttribute(Qt::WA_DeleteOnClose);
    warningUI->setGeometry(geometry().x()+(width()-warningUI->width())/2,
                           geometry().y()+(height()-warningUI->height())/2,
                           warningUI->width(), warningUI->height());
    warningUI->show();

    connect(warningUI, SIGNAL(yesBtnClicked()), warningUI, SLOT(close()));
    connect(warningUI, SIGNAL(noBtnClicked()), warningUI, SLOT(close()));
}

// 定义
void ManualTableWidget::defineActionRespond()
{
    DataDefineTemplateWidget *dataDefineUI;

    if(curWidgetType == Jogging::TOOL)
    {
        dataDefineUI = new DataDefineTemplateWidget(ProgramData::TOOL_DATA, QString(tr("tooldata0")), this);
    }
    else if(curWidgetType == Jogging::WORK_OBJECT)
    {
        dataDefineUI = new DataDefineTemplateWidget(ProgramData::WOBJ_DATA, QString(tr("wobjdata0")), this);
    }

    dataDefineUI->setAttribute(Qt::WA_DeleteOnClose);
    dataDefineUI->show();
    connect(dataDefineUI, SIGNAL(okBtnClicked()), dataDefineUI, SLOT(close()));
    connect(dataDefineUI, SIGNAL(cancelBtnClicked()), dataDefineUI, SLOT(close()));
}
