#ifndef PROGKEYS_H
#define PROGKEYS_H

#include <QWidget>

namespace Ui {
class ProgKeys;
}

class ProgKeys : public QWidget
{
    Q_OBJECT

public:
    explicit ProgKeys(QWidget *parent = 0);
    ~ProgKeys();

signals:
    void btn_CancelClicked_SIG();

private:
    Ui::ProgKeys *ui;

    void Init();
    void BtnInit();
    void TabWidgetInit();
    void ConnectInit();
};

#endif // PROGKEYS_H
