#ifndef BACKUP_H
#define BACKUP_H

#include <QWidget>

namespace Ui {
class Backup;
}

class Backup : public QWidget
{
    Q_OBJECT

public:
    explicit Backup(QWidget *parent = 0);
    ~Backup();

signals:
    void BtnCancelClicked_SIG();
    void BtnBackupClicked_SIG();

private:
    Ui::Backup *ui;

    void Init();
    void ConnectInit();
};

#endif // BACKUP_H
