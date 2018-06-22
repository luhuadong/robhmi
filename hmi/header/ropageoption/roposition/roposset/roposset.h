#ifndef ROPOSSET_H
#define ROPOSSET_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QLabel>

namespace Ui {
class roposset;
}

class roposset : public QWidget
{
    Q_OBJECT

public:
    explicit roposset(QPushButton *btn, int robtnNum, QWidget *parent = 0);
    ~roposset();

    QString StrEnsure;

    int btnNum;     //保存按钮选择号

    void setbtn(QPushButton *btn, int robtnNum);
    void getBtnFocus(int Num);

    void coord();
    void setaxis();
    void setaxisspeed();
    void lockoper();
    void incr();

public slots:
    void sbtn();

signals:
    void sendbtn(int Num);

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::roposset *ui;
    void btninit();
    void labelinit();
    QList <QPushButton *> btnlist;
    QList <QPushButton *> ::iterator btnlist_i;

    QList <QLabel *> labellist;
    QList <QLabel *> ::iterator labellist_i;
};

#endif // ROPOSSET_H
