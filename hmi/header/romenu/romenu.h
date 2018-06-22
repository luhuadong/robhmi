#ifndef ROMENU_H
#define ROMENU_H

#include <QWidget>
#include <QDebug>
#include <QMenu>
#include <QLabel>
#include "header/Common/Common.h"

namespace Ui {
class romenu;
}

class romenu : public QWidget
{
    Q_OBJECT

public:
    explicit romenu(QWidget *parent = 0);
    ~romenu();

    QMenu *menu;

private slots:
    void showaction(QAction *Action);

signals:
    void sendmenu(int menu);

private:
    Ui::romenu *ui;
};

#endif // ROMENU_H
