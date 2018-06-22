#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <QWidget>

namespace Ui {
class Appearance;
}

class Appearance : public QWidget
{
    Q_OBJECT

public:
    explicit Appearance(QWidget *parent = 0);
    ~Appearance();

signals:
    void btn_CancelClicked_SIG();
    void btn_OKClicked_SIG();
    void btn_TurnRightClicked_SIG();
    void btn_AcquiesceClicked_SIG();

private:
    Ui::Appearance *ui;

    void Init();
    void BtnInit();
    void ConnectInit();
};

#endif // APPEARANCE_H
