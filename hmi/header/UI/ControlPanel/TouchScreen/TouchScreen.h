#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <QWidget>

namespace Ui {
class TouchScreen;
}

class TouchScreen : public QWidget
{
    Q_OBJECT

public:
    explicit TouchScreen(QWidget *parent = 0);
    ~TouchScreen();

signals:
    void btn_CancelClicked_SIG();
    void btn_CorrectClicked_SIG();

private:
    Ui::TouchScreen *ui;
    void Init();
    void BtnInit();
    void ConnectInit();
};

#endif // TOUCHSCREEN_H
