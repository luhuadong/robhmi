#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include <QWidget>

namespace Ui {
class Diagnosis;
}

class Diagnosis : public QWidget
{
    Q_OBJECT

public:
    explicit Diagnosis(QWidget *parent = 0);
    ~Diagnosis();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::Diagnosis *ui;

    void Init();
    void BtnInit();
    void ConnectInit();
};

#endif // DIAGNOSIS_H
