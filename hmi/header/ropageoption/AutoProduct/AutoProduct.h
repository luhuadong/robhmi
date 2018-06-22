#ifndef AUTOPRODUCT_H
#define AUTOPRODUCT_H

#include <QWidget>
#include <QScrollBar>

namespace Ui {
class AutoProduct;
}

class AutoProduct : public QWidget
{
    Q_OBJECT

public:
    explicit AutoProduct(QWidget *parent = 0);
    ~AutoProduct();

private slots:
    void do_blockCountChanged(int );
    void do_VerticalValueChanged(int value);

signals:
    void btn_loadClicked_SIG();
    void btn_DebugClicked_SIG();
    void btn_PPtoMainClicked_SIG();

private:
    Ui::AutoProduct *ui;

    void Init();
    void TextBrowserInit();
    void ConnectInit();
};

#endif // AUTOPRODUCT_H
