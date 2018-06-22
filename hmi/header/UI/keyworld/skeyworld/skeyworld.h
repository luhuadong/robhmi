#ifndef SKEYWORLD_H
#define SKEYWORLD_H
//纯数字虚拟键盘
#include <QWidget>
#include <QPushButton>

namespace Ui {
class skeyWorld;
}

class skeyWorld : public QWidget
{
    Q_OBJECT

public:
    explicit skeyWorld(QWidget *parent = 0);
    ~skeyWorld();

    void skeyWorldInput(QString str);

private slots:
    void zeroBtnClicked();
    void oneBtnClicked();
    void twoBtnClicked();
    void threeBtnClicked();
    void fourBtnClicked();
    void fiveBtnClicked();
    void sixBtnClicked();
    void sevenBtnClicked();
    void eightBtnClicked();
    void nineBtnClicked();
    void delBtnClicked();
    void okClicked();
    void dotBtnClicked();
    void add_redBtnClicked();

    void vkeyClose();

    void clrBtnClicked();

signals:
    void btnClicked_SIG(QString str);    //数字键盘上每次点击都会发送
    void cancelBtn_SIG();
    void okBtn_SIG();

private:
    Ui::skeyWorld *ui;

    QString vKeyStr;    //保存虚拟键盘的数据

    QString  st;   //保存外面传进来的值

    void Init();
    void btnInit();
    void ConnectInit();

    QList <QPushButton *>btnlist;
};

#endif // SKEYWORLD_H
