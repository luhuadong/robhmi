#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QWidget>

namespace Ui {
class Configuration;
}

class Configuration : public QWidget
{
    Q_OBJECT

public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::Configuration *ui;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();
};

#endif // CONFIGURATION_H
