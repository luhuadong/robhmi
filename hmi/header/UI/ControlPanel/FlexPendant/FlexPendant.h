#ifndef FLEXPENDANT_H
#define FLEXPENDANT_H

#include <QWidget>

namespace Ui {
class FlexPendant;
}

class FlexPendant : public QWidget
{
    Q_OBJECT

public:
    explicit FlexPendant(QWidget *parent = 0);
    ~FlexPendant();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::FlexPendant *ui;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();
};

#endif // FLEXPENDANT_H
