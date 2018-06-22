#ifndef EDITBTN_H
#define EDITBTN_H

#include <QPushButton>
#include <QMenu>
#include <QAction>


// 构造函数要加一个参数，用来说明当前操作的程序数据的类型和值。
class EditBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit EditBtn(QWidget *parent = 0);

signals:

public slots:
    void showModDec();

private:
    QMenu *editBtnMenu;

    QAction *modValAction;  // 更改值
    QAction *modDecAction;  // 更改声明
    QAction *copyAction;    // 复制
    QAction *deleteAction;  // 删除
    QAction *defineAction;  // 定义

};

#endif // EDITBTN_H
