#include "InputOutput.h"
#include "ui_InputOutput.h"

void InputOutput::SetmeltNameView()    //化名界面
{
    setlabel_currentIOTypeText(tr("化名I/O"));
    setlabel_ChooseLayoutHide(true);
    setcomboBox_LayoutHide(true);

    setlabel_filterHide(false);
    setlabel_filterShowHide(false);
    setlabel_ChooseIOHide(false);

    setBtn_0Hide(true);
    setBtn_1Hide(true);
    setBtn_refreshHide(false);
    setBtn_FilterHide(false);

}

void InputOutput::SetindustrynetworkView() //工业网络
{
    setlabel_currentIOTypeText(tr("工业网络"));
    setlabel_ChooseLayoutHide(true);
    setcomboBox_LayoutHide(true);

    setlabel_filterHide(true);
    setlabel_filterShowHide(true);
    setlabel_ChooseIOHide(true);

    setBtn_0Hide(true);
    setBtn_1Hide(true);
    setBtn_refreshHide(true);
    setBtn_FilterHide(true);
}

void InputOutput::SetIOdeviceView() //IO设备
{
    setlabel_currentIOTypeText(tr("IO设备"));
    setlabel_ChooseLayoutHide(true);
    setcomboBox_LayoutHide(true);

    setlabel_filterHide(true);
    setlabel_filterShowHide(true);
    setlabel_ChooseIOHide(false);

    setBtn_0Hide(true);
    setBtn_1Hide(true);
    setBtn_refreshHide(true);
    setBtn_FilterHide(true);
}

void InputOutput::SetAllSIGNALView() //全部信号
{
    AcquiesceView("全部信号");
}

void InputOutput::SetdigitIuputView() //数字输入
{
    AcquiesceView("数字输入");
}

void InputOutput::SetdigitOutputView() //数字输出
{
    AcquiesceView("数字输出");
}

void InputOutput::SetimitateInputView() //模拟输入
{
    AcquiesceView("模拟输入");
}

void InputOutput::SetimitateOutputView() //模拟输出
{
    AcquiesceView(tr("模拟输出"));
}

void InputOutput::SetgroupInputView() //组输入
{
    AcquiesceView(tr("组输入"));
}

void InputOutput::SetgroupOutputView() //组输出
{
    AcquiesceView(tr("组输出"));
}

void InputOutput::SetincommonuseView() //常用
{
    AcquiesceView(tr("常用"));
}

void InputOutput::SetsafeSIGNAlView() //安全信号
{
    AcquiesceView(tr("安全信号"));
}

void InputOutput::SetsimulationSIGNAlView() //仿真信号
{
    AcquiesceView(tr("仿真信号"));
}

void InputOutput::ChangeView(int View)
{
    switch (View) {
        case meltNameView:SetmeltNameView();break;
        case industrynetworkView:SetindustrynetworkView();break;
        case IOdeviceView:SetIOdeviceView();break;
        case AllSIGNALView:SetAllSIGNALView();break;
        case digitIuputView:SetdigitIuputView();break;
        case digitOutputView:SetdigitOutputView();break;
        case imitateInputView:SetimitateInputView();break;
        case imitateOutputView:SetimitateOutputView();break;
        case groupInputView:SetgroupInputView();break;
        case groupOutputView:SetgroupOutputView();break;
        case incommonuseView:SetincommonuseView();break;
        case safeSIGNAlView:SetsafeSIGNAlView();break;
        case simulationSIGNAlView:SetsimulationSIGNAlView();break;
        default:break;
    }
}

void InputOutput::AcquiesceView(QString s)  //默认界面
{
    setlabel_currentIOTypeText(s);
    setlabel_ChooseLayoutHide(false);
    setcomboBox_LayoutHide(false);

    setlabel_filterHide(false);
    setlabel_filterShowHide(false);
    setlabel_ChooseIOHide(false);

    setBtn_0Hide(true);
    setBtn_1Hide(true);
    setBtn_refreshHide(false);
    setBtn_FilterHide(false);
}
