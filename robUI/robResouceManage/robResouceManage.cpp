#include "robResouceManage.h"
#include "ui_robResouceManage.h"

robResouceManage::robResouceManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::robResouceManage)
{
    ui->setupUi(this);

    Init();
}

robResouceManage::~robResouceManage()
{
    delete ui;
}

void robResouceManage::ShowFile(QDir dir)
{
    while(ui->tableWidget->rowCount()!=0)
        ui->tableWidget->removeRow(0);

    QFileInfoList fileList=dir.entryInfoList();

    for (int i=0;i<fileList.count();i++)
    {
        if(fileList.at(i).fileName()!="."&&fileList.at(i).fileName()!=".."){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());//插入一行
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,
                                     new QTableWidgetItem(fileList.at(i).fileName()));
            if(fileList.at(i).isDir()){
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,
                                         new QTableWidgetItem(tr(" 目录")));
            }else {
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,
                                         new QTableWidgetItem(fileList.at(i).suffix()+tr(" 文件")));
            }
        }
    }
}

void robResouceManage::ChangePath(QString path)
{
    dir.setPath(path);
    dirPath=dir.absolutePath();
    ui->label_Path->setText(dir.absolutePath());
}

void robResouceManage::Go()
{
    QFileInfo file;
    if (ui->label_Path->text()==dirPath){
        if (ui->tableWidget->selectedItems().count()>0)
            file.setFile(dir,ui->tableWidget->selectedItems().first()->text());
        else file.setFile(dir.dirName());
    }else{
        file.setFile(ui->label_Path->text());
        if(!file.isDir())
            if (ui->tableWidget->selectedItems().count()>0)
                file.setFile(dir,ui->tableWidget->selectedItems().first()->text());
            else file.setFile(dir.dirName());
    }
    if (file.isDir())
    {
        ChangePath(file.filePath());
        ShowFile(dir);
    }else{
        ChangePath(file.path());
        ShowFile(dir);
        QProcess *pro=new QProcess();
        pro->start(file.filePath());
    }
}

void robResouceManage::PasteFile(QString oldFileName, QString newFileName)
{
    QFileInfo file(oldFileName);
    if (file.isDir()){
        QDir oldMenu,newMenu;
        oldMenu.setPath(oldFileName);
        newMenu.mkdir(newFileName);
        QFileInfoList fileList=oldMenu.entryInfoList();
        for (int i=2;i<fileList.count();i++)
            PasteFile(oldFileName+"/"+fileList.at(i).fileName(),newFileName+"/"+fileList.at(i).fileName());
    }else
        QFile::copy(oldFileName,newFileName);
}

void robResouceManage::DeleteFile(QString fileName)
{
   QFileInfo file(fileName);
   if (file.isDir()){
       QDir fileDir;
       fileDir.setPath(fileName);
       QFileInfoList fileList=fileDir.entryInfoList();
       for (int i=2;i<fileList.count();i++)
           DeleteFile(fileName+"/"+fileList.at(i).fileName());
       fileDir.rmdir(fileName);
   }else
       QFile::remove(fileName);
}

void robResouceManage::Root()
{
    ChangePath(HOMEPATH);
    ShowFile(dir);
}

void robResouceManage::Copy()
{
    GetCopyFile(0);
}

void robResouceManage::Cut()
{
    GetCopyFile(1);
}

void robResouceManage::Paste()
{
    if (copyFile->filePath=="/")
        copyFile->filePath="";
    if (dirPath=="/")
        dirPath="";
    PasteFile(copyFile->filePath+"/"+copyFile->fileName,dirPath+"/"+copyFile->fileName);
    if (copyFile->filePath=="")
        copyFile->filePath="/";
    if (dirPath=="")
        dirPath="/";
    dir.setPath(dirPath);
    ShowFile(dir);
}

void robResouceManage::Delete()
{
    if (ui->tableWidget->selectedItems().count()<=0)
        return;
    if (dirPath=="/")
        dirPath="";
    DeleteFile(dirPath+"/"+ui->tableWidget->selectedItems().first()->text());

    if (dirPath=="")
        dirPath="/";
    dir.setPath(dirPath);
    ShowFile(dir);
}

void robResouceManage::Up()
{
    dir.cd("..");
    ChangePath(dir.path());
    ShowFile(dir);
}

void robResouceManage::GetCopyFile(int function)
{
    if (ui->tableWidget->selectedItems().count()<=0)
        return;
    copyFlag=function;
    copyFile=new CopyFile(dirPath,ui->tableWidget->selectedItems().first()->text());
}

void robResouceManage::NewDirectory(QString DirName)
{
    dir.mkdir(DirName);
}

void robResouceManage::ReName(QString oldName,QString newName)
{
    QString oldPath = dirPath;
    oldPath.append("/").append(oldName);
    QString newPath = dirPath;
    newPath.append("/").append(newName);

    QFileInfo info(oldPath);
    if(info.isFile()){
        QFile file;
        file.rename(oldPath,newPath);
    }else{
        QDir dir(oldName);
        dir.rename(oldPath,newPath);
    }
}

void robResouceManage::setLineEditText(QString str)
{
    ui->lineEdit_filename->setText(str);
}

QString robResouceManage::getLineEditText()
{
    return ui->lineEdit_filename->text();
}

void robResouceManage::clearLineEditText()
{
    ui->lineEdit_filename->clear();
}
