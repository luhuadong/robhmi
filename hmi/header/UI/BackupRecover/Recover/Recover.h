#ifndef RECOVER_H
#define RECOVER_H

#include <QWidget>

namespace Ui {
class Recover;
}

class Recover : public QWidget
{
    Q_OBJECT

public:
    explicit Recover(QWidget *parent = 0);
    ~Recover();

signals:
    void BtnCancelClicked_SIG();
    void BtnRecoverClicked_SIG();

private:
    Ui::Recover *ui;

    void Init();
    void ConnectInit();
};

#endif // RECOVER_H
