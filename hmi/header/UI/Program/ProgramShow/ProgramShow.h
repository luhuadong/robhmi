#ifndef PROGRAMSHOW_H
#define PROGRAMSHOW_H

#include <QWidget>
#include <QTextCursor>

#include <QStandardItem>
#include <Qt>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextBlock>
#include <QTextCursor>

//#include "./../../Common/Common.h"

#include <QScrollBar>
//#include "FileAndDirOperate.h"

namespace Ui {
class ProgramShow;
}

class ProgramShow : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramShow(QWidget *parent = 0);
    ~ProgramShow();

    void ShowLineNum(int LineNum);
    void ShowProgram(char *str);

    void ShowInsertQstring(QString s);//显示程序插入
    void ShowDelQstring();//显示程序删除

    void ShowProClear();   //显示程序清除
    void LineNumClear();


signals:
    void Btn_MissionAndProClicked_SIG();
    void Btn_ModuleClicked_SIG();
    void Btn_RoutineProClicked_SIG();
    void Btn_AlterPosClicked_SIG();
    void Btn_HideDeclareClicked_SIG();

private slots:
    void do_BtnAddOrderClicked();
    void do_BtnEditClicked();
    void do_BtnDebugClicked();
    void do_BtnAlterPosClicked();
    void do_BtnHideDeclareClicked();

    void do_VerticalValueChanged(int value);
    void do_blockCountChanged(int blockCount );

private:
    Ui::ProgramShow *ui;

    void Init();
    void BtnInit();
    void TextBrowserInit();
    void ConnectInit();

    enum ChangeView{
        vAddOrder,
        vEdit,
        vDebug,
    }vChangeView;

    QList<int> LineList;    //保存行号的列表
};

#endif // PROGRAMSHOW_H
