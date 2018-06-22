#include "ProgramShow.h"
#include "ui_ProgramShow.h"

ProgramShow::ProgramShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramShow)
{
    ui->setupUi(this);

    Init();
}

ProgramShow::~ProgramShow()
{
    delete ui;
}
/*显示程序的步骤
1、清除表格
2、插入内容
3、回到第一行
4、显示行号
*/
void ProgramShow::ShowProgram(char* str)   //显示程序
{
    QTextCursor cursor = ui->textBrowser_ShowPro->textCursor();

    cursor.insertText(QString(str));

    ui->textBrowser_ShowPro->moveCursor(QTextCursor::End);
}

void ProgramShow::ShowProClear()   //显示程序清除
{
    ui->textBrowser_ShowPro->clear();
}

void ProgramShow::LineNumClear()   //行号清除
{
    ui->textBrowser_line->clear();
}

void ProgramShow::ShowLineNum(int LineNum)//显示行号
{
    ui->textBrowser_line->clear();
    LineList.clear();

    for(int i = 1 ; i<=LineNum;i++){
        QTextCursor cursor = ui->textBrowser_line->textCursor();
        LineList.append(i);
        cursor.insertText(QString::number(i)+"\n");
    }

    ui->textBrowser_line->moveCursor(QTextCursor::Start);
}

void ProgramShow::ShowInsertQstring(QString s)//显示程序插入
{
    QTextCursor cursor = ui->textBrowser_ShowPro->textCursor();
    cursor.insertText(s);

    LineList.insert(cursor.blockNumber(),cursor.blockNumber()+1);
    for(int i = cursor.blockNumber();i <LineList.count();i++){
        LineList.removeAt(cursor.blockNumber());
        LineList.append(i+1);
    }

    ShowLineNum(LineList.count());//显示行号

    if(ui->textBrowser_ShowPro->verticalScrollBar()->value() !=
            ui->textBrowser_line->verticalScrollBar()->value())
        ui->textBrowser_line->verticalScrollBar()->
                setValue(ui->textBrowser_ShowPro->verticalScrollBar()->value());
}

//void ProgramShow::LineInsertQstring(QString s)//行号插入
//{
//    QTextCursor cursor = ui->textBrowser_line->textCursor();
//    cursor.insertText(s);
//}

void ProgramShow::ShowDelQstring()//显示程序删除
{
    QTextCursor cursor = ui->textBrowser_ShowPro->textCursor();

    cursor.select(QTextCursor::LineUnderCursor);

    cursor.removeSelectedText();
    cursor.deleteChar();

    LineList.removeAt(cursor.blockNumber());
    for(int i = cursor.blockNumber();i <LineList.count();i++){
        LineList.removeAt(cursor.blockNumber());
        LineList.append(i+1);
    }

    ShowLineNum(LineList.count());//显示行号

    if(ui->textBrowser_ShowPro->verticalScrollBar()->value() !=
            ui->textBrowser_line->verticalScrollBar()->value())
        ui->textBrowser_line->verticalScrollBar()->
                setValue(ui->textBrowser_ShowPro->verticalScrollBar()->value());
}
