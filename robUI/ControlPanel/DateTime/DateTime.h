#ifndef DATETIME_H
#define DATETIME_H

#include <QWidget>

namespace Ui {
class DateTime;
}

class DateTime : public QWidget
{
    Q_OBJECT

public:
    explicit DateTime(QWidget *parent = 0);
    ~DateTime();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::DateTime *ui;

    void Init();
    void BtnInit();
    void ConnectInit();
};

#endif // DATETIME_H
