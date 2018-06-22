#ifndef VKEYWORLD_H
#define VKEYWORLD_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include <Qt>


#define Capital_High_case 1 //大写
#define Capital_Lower_case 0    //小写

#define ShiftModel 1 //Shift模式
#define NoShiftModel 0  //非Shift模式

namespace Ui {
class vkeyworld;
}

class vkeyworld : public QWidget
{
    Q_OBJECT

public:
    explicit vkeyworld( QWidget *parent = 0);
    ~vkeyworld();

     void vkeyWorldInput(QString s);

private slots:
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();

    void digitClicked();
    void character_qpClicked();
    void character_alClicked();
    void character_zmClicked();
    void symbolClicked();

    void CAPClicked(bool enabled);
    void ShiftClicked(bool enabled);

    void BackspaceClicked();
    void spaceClicked();

    void upClicked();
    void downClicked();
    void leftClicked();
    void rightClicked();

    void HomeClicked();
    void EndClicked();

    void doChange_CAPModal(int CapModal);
    void doChange_ShiftModal(int ShiftModal);

signals:
    void sig_ok(QString str);
    void sig_cancel();

    void sig_Change_CAPModal(int CapModal);//改变CAP模式的信号
    void sig_Change_ShiftModal(int ShiftModal);//改变Shift模式的信号

private:
    Ui::vkeyworld *ui;

    int cursorPos;     //光标位置

    void Init();
    void btnInit();
    void globalConfig();

    int modal_CAP;      //模式 :1大写模式 ,0 小写
    int modal_Shift;      //模式 :1Shift模式 ,0 非Shift

    QString str;

    QList <QPushButton *> btnList_digit;        //数组按键
    QList <QPushButton *> btnList_character_qp; //字母键q-p
    QList <QPushButton *> btnList_character_al; //字母键a-l
    QList <QPushButton *> btnList_character_zm; //字母键z-m
    QList <QPushButton *> btnList_symbol; //符号键
};

#endif // VKEYWORLD_H
