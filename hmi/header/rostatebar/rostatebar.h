#ifndef ROSTATEBAR_H
#define ROSTATEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include "header/roclose/roclose.h"

#include "header/romenu/romenu.h"
//#include <QListWidget>

#include "header/Common/Common.h"

namespace Ui {
class rostatebar;
}

class rostatebar : public QWidget
{
    Q_OBJECT

public:
    explicit rostatebar(romenu *menu, QStackedWidget* stack,
                        roClose *closeview, QWidget *parent = 0);
    ~rostatebar();

signals:
    void btnchange(int btnNum);

public slots:
    void Showbtn(int Index);
    void ChangeView();
    void closeView();

private:
    Ui::rostatebar *ui;

    QList<QPushButton *> btnShowList;//显示的按钮列表
    QList<QPushButton *> btnlist;//需要显示或隐藏的按钮列表
    QList<QString > ListStr;//菜单界面字符列表
    romenu *menu;
    QStackedWidget *stack;

    void Init();
    QList<QPushButton*> btnInit();
    QList<QString> ListStrInit();
    void ConnectInit();

    void HideAllBtn();//隐藏所有的按钮
    void getBtnStyle(int num);//获取焦点  即按钮变色
};

#endif // ROSTATEBAR_H
