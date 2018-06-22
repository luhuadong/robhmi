#ifndef robResouceManage_H
#define robResouceManage_H

#include <QWidget>
#include "header/Common/Common.h"
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QProcess>
#include <QTableWidgetItem>

#define HOMEPATH "D:/MyStudyForQT/Practice/newhmi/hmi_windows/robhmi/hmi/bin"

namespace Ui {
class robResouceManage;
}

class robResouceManage : public QWidget
{
    Q_OBJECT

public:
    explicit robResouceManage(QWidget *parent = 0);
    ~robResouceManage();

    void setLineEditText(QString str);
    QString getLineEditText();
    void clearLineEditText();

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
    void Root();
    void Copy();
    void Cut();
    void Paste();
    void Delete();
    void Up();

private slots:

    void do_cellClicked(int row, int);

    void do_btnHideHeaderClicked();
    void do_btnShowHeaderClicked();

    void do_btnUpClicked();
    void do_btnHomeClicked();
    void do_Init();

signals:
    void robRMInit();

    void btnNewClicked_SIG();
    void btnCancelClicked_SIG();
    void btnOkClicked_SIG();
    void btnOpenKeyClicked_SIG();

private:
    Ui::robResouceManage *ui;

    void Init();
    void TableWidgetInit();
    void ConnectInit();
};

#endif // robResouceManage_H
