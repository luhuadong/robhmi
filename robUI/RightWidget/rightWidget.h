#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class rightWidget;
}

class rightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit rightWidget(QWidget *parent = 0);
    ~rightWidget();

signals:
    void btnMinimizeClicked_SIG();
    void btnCloseClicked_SIG();
    void btnChangeLeftViewClicked_SIG();
    void btnShowOrHideLeftClicked_SIG();

    void btnShortcut_1Clicked_SIG();
    void btnShortcut_2Clicked_SIG();
    void btnShortcut_3Clicked_SIG();
    void btnShortcut_4Clicked_SIG();

    void btnChangeClicked_SIG();
    void btnChangeLineClicked_SIG();
    void btnChangeMoveAxisClicked_SIG();
    void btnChangeSpeedClicked_SIG();
    void btnChangeStateClicked_SIG();

    void btnUpClicked_SIG();
    void btnRightClicked_SIG();
    void btnLeftClicked_SIG();
    void btnDownClicked_SIG();
    void btnRightUpClicked_SIG();
    void btnRightDownClicked_SIG();
    void btnLeftUpClicked_SIG();
    void btnLeftDownClicked_SIG();
    void btnAnticlockwise_SIG();
    void btnClockwise_SIG();

    void btnEnableClicked_SIG(bool checked);
    void btnHoldToRunClicked_SIG(bool checked);

    void btnRunClicked_SIG();
    void btnNextClicked_SIG();
    void btnPriorClicked_SIG();
    void btnStopClicked_SIG();

    void radioBtnAutomaticClicked_SIG();
    void radioBtnManualClicked_SIG();
    void radioBtnExecuteClicked_SIG();
    void btnMotorEnableClicked_SIG();

private slots:
    void do_btnChangeStateClicked();
    void closeWidgetChangeState();//关闭界面

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::rightWidget *ui;

    void Init();
    void ConnectInit();
    void BtnInit();
};

#endif // RIGHTWIDGET_H
