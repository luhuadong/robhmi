#ifndef ROSTATEBYSYS_H
#define ROSTATEBYSYS_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "header/Common/Common.h"

namespace Ui {
class RoStateBySys;
}

class RoStateBySys : public QWidget
{
    Q_OBJECT

public:
    explicit RoStateBySys(QWidget *parent = 0);
    ~RoStateBySys();

private:
    Ui::RoStateBySys *ui;
};

#endif // ROSTATEBYSYS_H
