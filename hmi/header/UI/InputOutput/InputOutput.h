#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <QWidget>
#include <QMenu>
#include <QDebug>

namespace Ui {
class InputOutput;
}

class InputOutput : public QWidget
{
    Q_OBJECT

public:
    explicit InputOutput(QWidget *parent = 0);
    ~InputOutput();

private slots:
    void on_Btn_1_clicked();
    void on_Btn_0_clicked();
    void on_Btn_Filter_clicked();
    void on_Btn_View_clicked(bool checked);

    void do_menuHide();
    void do_menuShow();

    void do_menutriggered(QAction *Action);

private:
    Ui::InputOutput *ui;

    void Init();

    QAction *meltName ;
    QAction *industrynetwork ;
    QAction *IOdevice ;
    QAction *AllSIGNAL ;
    QAction *digitInput ;
    QAction *digitOutput ;
    QAction *imitateInput ;
    QAction *imitateOutput ;
    QAction *groupInput ;
    QAction *groupOutput ;
    QAction *incommonuse ;
    QAction *safeSIGNAl ;
    QAction *simulationSIGNAl ;
    QMenu *menu ;

    void BtnInit();

    int TableWidgetCurrentRow;
    int TableWidgetCurrentColumn;

    bool MenuShow;
    bool MenuHide;

    void setlabel_currentIOTypeText(QString s);
    void setlabel_filterShowText(QString s);

    void setlabel_filterHide(bool Hideen);
    void setlabel_filterShowHide(bool Hideen);
    void setlabel_ChooseIOHide(bool Hideen);
    void setlabel_ChooseLayoutHide(bool Hideen);
    void setcomboBox_LayoutHide(bool Hideen);

    void setBtn_0Hide(bool Hideen);
    void setBtn_1Hide(bool Hideen);
    void setBtn_refreshHide(bool Hideen);
    void setBtn_FilterHide(bool Hideen);

    void SetmeltNameView() ;   //化名界面
    void SetindustrynetworkView(); //工业网络
    void SetIOdeviceView() ;//IO设备
    void SetAllSIGNALView(); //全部信号
    void SetdigitIuputView(); //数字输入
    void SetdigitOutputView(); //数字输出
    void SetimitateInputView(); //模拟输入
    void SetimitateOutputView(); //模拟输出
    void SetgroupInputView(); //组输入
    void SetgroupOutputView(); //组输出
    void SetincommonuseView(); //常用
    void SetsafeSIGNAlView(); //安全信号
    void SetsimulationSIGNAlView(); //仿真信号

    enum IOView{
        meltNameView,
        industrynetworkView,
        IOdeviceView,
        AllSIGNALView,
        digitIuputView,
        digitOutputView,
        imitateInputView,
        imitateOutputView,
        groupInputView,
        groupOutputView,
        incommonuseView,
        safeSIGNAlView,
        simulationSIGNAlView,
    };

    void AcquiesceView(QString s) ;//默认界面
    void ChangeView(int View);
};

#endif // ROBWIDGET_IO_H
