#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QWidget>

namespace Ui {
class Language;
}

class Language : public QWidget
{
    Q_OBJECT

public:
    explicit Language(QWidget *parent = 0);
    ~Language();

signals:
    void btn_CancelClicked_SIG();
    void btn_OKClicked_SIG();

private:
    Ui::Language *ui;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();
};

#endif // LANGUAGE_H
