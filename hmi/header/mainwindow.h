#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "header/roimagesforsysstate/roimagesforsysstate.h"
#include "header/rostatebysys/rostatebysys.h"
#include "header/ropageoption/ropageoption.h"
#include "header/rostatebar/rostatebar.h"
#include "header/romenu/romenu.h"
#include "header/roclose/roclose.h"

#include "header/UI/rightWidget/rightWidget.h"

#include <QVBoxLayout>
#include <QSettings>
#include <QSplitter>
#include <Qt>

#include "header/Common/Common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void do_RightWidgetBtnCloseClicked();
    void do_RightWidgetBtnMinimizeClicked();

protected :
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    romenu *Menu;
    RoImagesForSysState *ImageForCoord;
    RoImagesForSysState *ImageForOrder;
    RoImagesForSysState *ImageForState;
    RoImagesForSysState *ImageForSpeed;
    RoStateBySys *roStateBySys;
    RoPageOption *ropageoption;
    rostatebar *statebar;
    roClose *rclose;
    rightWidget *rWidget;

    QSplitter *splitterMain;//分割窗口

    QWidget *LeftWidget;
    QWidget *RightWidget;

    void Init();

    void ConnectInit();

    void splitterInit();//分割器初始化

    void ViewInit();

    void loadSettings();

    void saveSettings();
};

#endif // MAINWINDOW_H
