#ifndef BACKUPRECOVER_H
#define BACKUPRECOVER_H

#include <QWidget>
#include "header/Common/Common.h"
#include "Recover/Recover.h"
#include "Backup/Backup.h"

namespace Ui {
class BackupRecover;
}

class BackupRecover : public QWidget
{
    Q_OBJECT

public:
    explicit BackupRecover(QWidget *parent = 0);
    ~BackupRecover();

    void StackedWidgetAddWidget(QWidget * widget);
    void StackedWidgetSetCurrentIndex(int index);


signals:
    void BtnBackupClicked_SIG();
    void BtnRecoverClicked_SIG();

private slots:
    void do_BtnBackupClicked();
    void do_BtnRecoverClicked();
    void do_BtnCancelClicked();

private:
    Ui::BackupRecover *ui;
    Backup *rBackup;
    Recover *rRecover;

    enum BACKUPRECOVER{
        vBackupRecover,
        vBackup,
        vRecover,
        vKeyworld,
    };

    void Init();
    void ViewInit();
    void ConnectInit();
};

#endif // BACKUPRECOVER_H
