#ifndef ROPOSITION_H
#define ROPOSITION_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QMenu>
#include "header/ropageoption/roposition/roposset/roposset.h"
#include "header/ropageoption/roposition/outputthread.h"

#include "header/ITP_Interface.h"

#include "header/ropageoption/ropagealarm/robalarm.h"

namespace Ui {
class roposition;
}

class roposition : public QWidget
{
    Q_OBJECT

public:
    explicit roposition(QWidget *parent = 0);
    ~roposition();

    QPushButton *btnflat;//标记按下的按钮

    void changedire();

    //Init
    void btninit();
    void labelinit();
    void shareMemInit();
    void datainit();

    //tablewidget
    void tableWidgetInit();
    void tableWidgetconfig_4_view();
    void tableWidgetconfig_2_view();
    void tableWidgetconfig_3_view();


private slots:
    void roMoving();
    void rostopMoving();
    void setbtn();
    void change(int btnnum);

    //Data
    void showData(ITP_OutputData *OutputData);

private:
    Ui::roposition *ui;
    roposset *posset;

    void init();

    ITP_InputData *pInputData;		//share mem

    outputThread *read_ITP_Thread; //read share mem thread
    void *shared_Inputmemory;

    QImage *image;

    QList <QPushButton *> thisallbtn;
    QList <QPushButton *> dirbtnlist;
    QList <QLabel *> labellist;

    void changeCoord(int num);
    void changeAxis(int num);
    void changeAxisSpeed(int num);
    void changeModel(int num);

    void do_JointOp_SpeedMode(int num);
    void do_CoordinateOp_SpeedMode();

    int axis[2][3] ;
    int selectaxis;       //选中轴
    int currentaxis;      //当前轴
    int currentmodel;

    //data

};

#endif // ROPOSITION_H
