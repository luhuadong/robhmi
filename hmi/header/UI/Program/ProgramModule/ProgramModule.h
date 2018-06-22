#ifndef PROGRAMMODULE_H
#define PROGRAMMODULE_H

#include <QWidget>
#include <QMenu>
#include <QTableWidget>

namespace Ui {
class ProgramModule;
}

class ProgramModule : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramModule(QWidget *parent = 0);
    ~ProgramModule();

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
    void BtnShowModuleClicked_SIG();
    void BtnRefrashClicked();
    void MenuActionTriggered(QAction* action);

    void TableWidgetCellClicked_SIG(int row, int column,
                                    QString ModuleName,QString ModuleType);

private:
    Ui::ProgramModule *ui;

    void Init();
    void TableWidgetInit();
    void BtnInit();
    void ConnectInit();
};

#endif // PROGRAMMODULE_H
