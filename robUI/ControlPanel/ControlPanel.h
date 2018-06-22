#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "./../Common/Common.h"

#include "Appearance/Appearance.h"
#include "Monitoring/Monitoring.h"
#include "Configuration/Configuration.h"
#include "FlexPendant/FlexPendant.h"
#include "IO/IO.h"
#include "Language/Language.h"
#include "ProgKeys/ProgKeys.h"
#include "DateTime/DateTime.h"
#include "Diagnosis/Diagnosis.h"
#include "TouchScreen/TouchScreen.h"

namespace Ui {
class ControlPanel;
}



class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();


    void setPosText(QString str);

private slots:
    void do_tableWidgetCellClicked(int row, int column);

    void do_btnCancelClicked();//任何界面的取消或关闭按钮都将执行这个槽

private:
    Ui::ControlPanel *ui;
    Appearance *CPAppearance;
    Monitoring *CPMonitoring;
    FlexPendant *CPFlexPendant;
    IO *CPIO;
    Language *CPLanguage;
    ProgKeys *CPProgKeys;
    DateTime *CPDateTime;
    Diagnosis *CPDiagnosis;
    Configuration *CPConfign;
    TouchScreen *CPTouchScreen;

    void Init();
    void ViewInit();
    void TableWidgetInit();
    void ConnectInit();

//    void ShowTableWidget();

    enum CPView{
        CPanelWidget,//控制面板
        AppWidget,//外观
        MonWidget,//监控
        FleWidget,//flexpendant
        IOWidget,//
        LanWidget,//语言
        ProgKeysWidget,//progkeys
        DateTimeWidget,//日期和时间
        DiaWidget,//诊断
        ConfWidget,//配置
        TouchScreenWidget//触摸屏
    };




};

#endif // CONTROLPANEL_H
