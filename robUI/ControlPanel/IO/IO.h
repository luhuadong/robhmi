#ifndef IO_H
#define IO_H

#include <QWidget>

namespace Ui {
class IO;
}

class IO : public QWidget
{
    Q_OBJECT

public:
    explicit IO(QWidget *parent = 0);
    ~IO();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::IO *ui;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();
};

#endif // IO_H
