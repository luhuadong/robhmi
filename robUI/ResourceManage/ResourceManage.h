#ifndef RESOURCEMANAGE_H
#define RESOURCEMANAGE_H

#include <QWidget>
#include "./../Common/Common.h"
#include <QDir>
#include <QMenu>
#include "./../../Keyworld/vkeyworld/vkeyworld.h"
#include <QFileInfo>
#include <QDateTime>
#include <QProcess>
#include <QTableWidgetItem>

#define HOMEPATH "D:/MyStudyForQT/Practice/newhmi/hmi_windows/robhmi/hmi/bin"

namespace Ui {
class ResourceManage;
}

class ResourceManage : public QWidget
{
    Q_OBJECT

public:
    explicit ResourceManage(QWidget *parent = 0);
    ~ResourceManage();

    void StackedWidgetAddWidget(QWidget *widget);
    QString dirPath;
    QDir dir;
    QString *UDiskPath;
    struct CopyFile
    {
        CopyFile(QString filePath,QString fileName)
        {
            this->filePath=filePath;
            this->fileName=fileName;
        }
        QString filePath;
        QString fileName;
    }*copyFile;
    bool copyFlag;

    void ShowFile(QDir dir);
    void ChangePath(QString path);
    void Go();
    void GetCopyFile(int function);
    void PasteFile(QString oldFileName,QString newFileName);
    void DeleteFile(QString fileName);
    void NewDirectory(QString DirName);
    void ReName(QString oldName,QString newName);

protected slots:
    void Root();
    void Copy();
    void Cut();
    void Paste();
    void Delete();
    void Up();
    void ItemDoubleClicked(QTableWidgetItem*);

    void do_btnMenuClicked();
    void do_triggered(QAction* Action);
    void do_btnHideHeaderClicked();
    void do_btnShowHeaderClicked();
    void do_TableWidgetNoChooseLine();
    void do_TableWidgetCellClicked(int , int );
    void do_btnRefreshClicked();

    void do_btnNewClicked();
    void do_btnShowSize();
    void do_btnCloseClicked();

    void do_keyOk(QString str);
    void do_keyCancle();


signals:
    void RMInit();
    void TableWidgetNoChooseLine();

private:
    Ui::ResourceManage *ui;

    vkeyworld *vkey;

    QAction *aCopy;
    QAction *aMove ;
    QAction *aPase;
    QAction *aReNa ;
    QAction *aDele;
    QAction *aAttr ;
    QMenu *menu;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();

    void AttrInfo(QString str);
    void AttrFileInit();
    void AttrDirInit();
    void computeSize(QString path);

    enum View{
        View_RB,
        View_Attr,//属性
        View_vkey,
    };

    enum Action{
        Action_Rename,
        Action_New,
    };

    enum do_Action {
        do_Copy,
        do_Move,
        do_Pase,
        do_ReNa,
        do_Dele,
        do_Attr,
    };
    int currentAction;

    float filesize;
};

#endif // RESOURCEMANAGE_H
