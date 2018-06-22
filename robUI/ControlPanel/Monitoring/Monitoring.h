#ifndef MONITORING_H
#define MONITORING_H

#include <QWidget>

namespace Ui {
class Monitoring;
}

class Monitoring : public QWidget
{
    Q_OBJECT

public:
    explicit Monitoring(QWidget *parent = 0);
    ~Monitoring();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::Monitoring *ui;

    void Init();
    void BtnInit();
    void ConnectInit();
};

#endif // MONITORING_H
