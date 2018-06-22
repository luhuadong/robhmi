#ifndef ROCLOSE_H
#define ROCLOSE_H

#include <QWidget>
#include "header/Common/Common.h"

namespace Ui {
class roClose;
}

class roClose : public QWidget
{
    Q_OBJECT

public:
    explicit roClose(QWidget *parent = 0);
    ~roClose();

signals:
    void closeviewflag();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::roClose *ui;
};

#endif // ROCLOSE_H
