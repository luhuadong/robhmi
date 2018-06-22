#ifndef PROGRAMROUTINEPRO_H
#define PROGRAMROUTINEPRO_H

#include <QWidget>
#include <QMenu>
#include <QTableWidget>

namespace Ui {
class ProgramRoutinePro;
}

class ProgramRoutinePro : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramRoutinePro(QWidget *parent = 0);
    ~ProgramRoutinePro();

    void TableWidgetSelectRow(int row);
    void TableWidgetSetRowCount(int Row);
    void TableWidgetClear();
    void TableWidgetSetItem(int row, int column, QTableWidgetItem *item);

    QMenu *menu;

private slots:
    void do_btnFileClicked();
    void do_TableWidgetCellClicked(int row,int column);

signals:
    void BtnBackClicked_SIG();
    void BtnShowRoutineProClicked_SIG();
    void BtnFilterClicked();
    void MenuActionTriggered(QAction* action);

    void TableWidgetCellClicked_SIG(int row, int column,QString Name,
                                    QString Module,QString Type);

private:
    Ui::ProgramRoutinePro *ui;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();
};

#endif // PROGRAMROUTINEPRO_H
