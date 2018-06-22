#include "SystemInfo.h"
#include "ui_SystemInfo.h"


SystemInfo::SystemInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInfo)
{
    ui->setupUi(this);

    Init();
}

SystemInfo::~SystemInfo()
{
    delete ui;
}

void SystemInfo::Init()
{
    this->resize(PAGEOPTIONWIDTH,PAGEOPTIONHEIGHT);

    TreeWidgetInit();
    ConnectInit();
}

void SystemInfo::ConnectInit()
{
    connect(ui->btn_refresh,SIGNAL(clicked()),
            this,SLOT(do_BtnRefreshClicked()));
    connect(ui->treeWidget,SIGNAL(collapsed(QModelIndex)),
            this,SLOT(do_collapsed(QModelIndex)));//收
    connect(ui->treeWidget,SIGNAL(expanded(QModelIndex)),
            this,SLOT(do_expanded(QModelIndex)));//展开
    connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),
            this,SLOT(do_treeWidgetClicked(QModelIndex)));
}

void SystemInfo::TreeWidgetInit()
{
    //只能选择一行
    ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //选择一行
    ui->treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不要垂直滚动条
    ui->treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //不要水平滚动条
    ui->treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void SystemInfo::setPosText(QString str)
{
    ui->label_Pos->setText(ui->label_Pos->text().append("/").append(str));
}

void SystemInfo::setTextBrowserText(QString str)
{
    ui->textBrowser->setText(str);
}

void SystemInfo::do_BtnRefreshClicked()
{
    emit BtnRefreshClicked_SIG();
}

void SystemInfo::do_treeWidgetClicked(QModelIndex index)
{
    QTreeWidgetItem *Item = ui->treeWidget->currentItem();
    if(Item==NULL)
        return;

    if(Item->isExpanded()){
        ui->treeWidget->setExpanded(index,false);
    }else{
        ui->treeWidget->setExpanded(index,true);
    }
}

void SystemInfo::do_collapsed(QModelIndex)//收
{
    ui->textBrowser->clear();
}

void SystemInfo::do_expanded(QModelIndex index)
{
    QString ItemText[] = {
        "控制器属性","网络连接","服务端口","WAN","已安装系统",
        "系统属性","控制模块","选项","驱动模块","Robot1","选项","Robot2","选项","附加选项"
    };

    QTreeWidgetItem *Item = ui->treeWidget->currentItem();
    if(Item==NULL)
        return;

    if(Item->text(ui->treeWidget->currentColumn())==tr("控制器属性"))
        setTextBrowserText(tr("-名称\n\t").append(obtainLocalHostName()));
    else if(Item->text(ui->treeWidget->currentColumn())==tr("服务端口"))
        setTextBrowserText(tr("-IP地址\n\t").append(obtainIPAddress()));
    else
        setTextBrowserText(tr("-名称\n\t").append(obtainItemName(Item)));
}

QString SystemInfo::obtainLocalHostName()
{
    QString localHostName = QHostInfo::localHostName() ;
    return localHostName;
}

QString SystemInfo::obtainIPAddress()
{
    QHostInfo info = QHostInfo::fromName(obtainLocalHostName()) ;

    QString IPAddress ;//= info.addresses();
//    qDebug()<<info.addresses().first().toIPv4Address();

    QHostInfo::lookupHost(info.addresses().first().toString()
                    ,this,SLOT(lookedUp(QHostInfo)));


//    foreach(QHostAddress address,info.addresses())
//    {
//        if(address.protocol() == QAbstractSocket::IPv4Protocol)
//            qDebug() << "IPv4 Address: " << address.toString();
//    }

//    foreach (QHostAddress address, QNetworkInterface::allAddresses() )
//    {
//        qDebug() << "Address: " << address;
//    }
    return IPAddress;
}

void SystemInfo::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses())
        qDebug() << "Found address:" << address.toString();
}


QString SystemInfo::SystemAttribute()//系统属性
{

}

QString SystemInfo::ControlModuleOption()//控制模块选项
{

}

QString SystemInfo::DriveModule()//驱动模块
{

}

QString SystemInfo::DriveModuleOption()//驱动模块选项
{

}

QString SystemInfo::AdditionOption()//附加选项
{

}

QString SystemInfo::obtainItemName(QTreeWidgetItem *Item)//获取Item名称
{
    return Item->text(ui->treeWidget->currentColumn());
}
