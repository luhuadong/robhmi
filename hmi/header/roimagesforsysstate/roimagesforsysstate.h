#ifndef ROIMAGESFORSYSSTATE_H
#define ROIMAGESFORSYSSTATE_H

#include <QWidget>
#include <QImage>
//#include <QGraphicsView>
//#include <QString>
#include "header/Common/Common.h"

namespace Ui {
class RoImagesForSysState;
}

class RoImagesForSysState : public QWidget
{
    Q_OBJECT

public:
    explicit RoImagesForSysState(QWidget *parent = 0);
    ~RoImagesForSysState();

private:
    Ui::RoImagesForSysState *ui;
    QImage *image;
};

#endif // ROIMAGESFORSYSSTATE_H
