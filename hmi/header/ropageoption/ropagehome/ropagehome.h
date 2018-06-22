#ifndef ROPAGEHOME_H
#define ROPAGEHOME_H

#include <QWidget>
#include <QImage>
#include <QString>

#include "header/Common/Common.h"

namespace Ui {
class RoPageHome;
}

class RoPageHome : public QWidget
{
    Q_OBJECT

public:
    explicit RoPageHome(QWidget *parent = 0);
    ~RoPageHome();

private:
    Ui::RoPageHome *ui;
    QImage *image;
};

#endif // ROPAGEHOME_H
