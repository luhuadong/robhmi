#include "ResourceManage.h"
#include "ui_ResourceManage.h"

void ResourceManage::AttrInfo(QString str)
{
    QString Fileinfo = dirPath;
    Fileinfo.append('/').append(str);

    QFileInfo info(Fileinfo);

    QString lastTime = info.lastModified().toString("yyyy/MM/dd HH:mm:ss");

    if(info.isDir()){
        AttrDirInit();
        int FileNum = 0;
        QDir dir(Fileinfo);
        const QFileInfoList list = dir.entryInfoList();
        QFileInfoList::const_iterator iterator = list.begin();
        while(iterator != list.end())
        {
            if((*iterator).isFile())
            {
                FileNum++;
            }

            iterator++;
        }
        QString Comprise = QString::number(FileNum);
        ui->label_Comprise_2->setText(Comprise+tr("个文件"));
    }else{
        AttrFileInit();

        QString unit = "B";
        qint64 infoSize = info.size();

        if(infoSize >= 1024.0) {
            infoSize /= 1024.0;
            unit = "K";
            if(infoSize > 1024.0) {
                infoSize /= 1024.0;
                unit = "M";
                if(infoSize > 1024.0) {
                    infoSize /= 1024.0;
                    unit = "G";
                }
            }
        }

        QString Size = QString::number(infoSize).append(unit);

        QString lastRead = info.lastRead().toString("yyyy/MM/dd HH:mm:ss");
        QString createdTime = info.created().toString("yyyy/MM/dd HH:mm:ss");
        ui->label_visit_2->setText(lastRead);
        ui->label_created_2->setText(createdTime);
        ui->label_Size_2->setText(Size);
    }

    ui->label_Type_2->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text());
    ui->label_Position_2->setText(dirPath);
    ui->label_lastTime_2->setText(lastTime);
}

void ResourceManage::AttrFileInit()
{
    ui->btn_showsize->hide();

    ui->label_Size->show();
    ui->label_Size_2->show();

    ui->label_Comprise->hide();
    ui->label_Comprise_2->hide();

    ui->label_visit->show();
    ui->label_visit_2->show();

    ui->label_created->show();
    ui->label_created_2->show();
}

void ResourceManage::AttrDirInit()
{
    ui->btn_showsize->show();

    ui->label_Size->hide();
    ui->label_Size_2->hide();

    ui->label_visit->hide();
    ui->label_visit_2->hide();

    ui->label_created->hide();
    ui->label_created_2->hide();

    ui->label_Comprise->show();
    ui->label_Comprise_2->show();
}

void ResourceManage::do_btnShowSize()
{
    ui->label_Size->show();
    ui->label_Size_2->show();

    filesize = 0;

    QString Fileinfo = dirPath;
    Fileinfo.append('/').append(
                ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());


    computeSize(Fileinfo);

    QString unit = "B";

    if(filesize >= 1024.0) {
        filesize /= 1024.0;
        unit = "K";
        if(filesize > 1024.0) {
            filesize /= 1024.0;
            unit = "M";
            if(filesize > 1024.0) {
                filesize /= 1024.0;
                unit = "G";
            }
        }
    }
    QString Size ;
    Size.sprintf("%.2f %s",filesize,unit.toLocal8Bit().data());

    ui->label_Size_2->setText(Size);
}

void ResourceManage::computeSize(QString path)
{
    QDir dir(path);

    const QFileInfoList list = dir.entryInfoList();
    QFileInfoList::const_iterator iterator = list.begin();

    iterator++;
    iterator++;

    while(iterator != list.end())
    {
        filesize = (*iterator).size()+filesize;

        if((*iterator).isDir())
            computeSize((*iterator).filePath());
        iterator++;
    }
}
