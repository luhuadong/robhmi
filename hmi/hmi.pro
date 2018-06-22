#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T10:51:16
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hmi
TEMPLATE = app

TRANSLATIONS += \
    bin/resource/language/EN.ts \
    bin/resource/language/ZH_CN.ts

#库文文件
LIBS += -L ./../../robhmi/hmi/lib -lRobAlarm -lDataManage -lDataProcess -lProgramData \
    -lskeyworld -lvkeyworld -lFileAndDirOperate -lResourceManage -lParaSet \
    -lrightWidget -lControlPanel -lInputOutput -lSystemInfo -lBackupRecover \
    -lProgramShow -lProgramChoose -lProgramModule -lProgramRoutinePro -lrobResourceManage \
    -lrobDecodePrg


#DEPENDPATH = ./../../robhmi/hmi/header#添加依赖的路

NETCNC_ROOT = $${PWD}/../

INCLUDEPATH += \#$(ROBOT_QT_PRJ_PATH)/hmi/header \
    $(ROBOT_QT_PRJ_PATH)/robDecodePrg/header/decode_core \
    $(ROBOT_QT_PRJ_PATH)/robDecodePrg/header/decode_prg \

#INCLUDEPATH += $${NETCNC_ROOT}/robDecodePrg/header/decode_core \
#    $${NETCNC_ROOT}/robDecodePrg/header/decode_prg \
#    $${NETCNC_ROOT}/robUI/Program/ProgramChoose \

SOURCES +=\#源文文件
    source/main.cpp \
    source/mainwindow.cpp \
    source/romenu/romenu.cpp \
    source/roimagesforsysstate/roimagesforsysstate.cpp \    
    source/rostatebysys/rostatebysys.cpp \    
    source/roclose/roclose.cpp \
    source/rostatebar/rostatebar.cpp \
    source/DataManage_WinShareMem.c \
    source/ropageoption/ropageoption.cpp \
    source/ropageoption/ropagehome/ropagehome.cpp \
    source/ropageoption/roposition/roposition.cpp \
    source/ropageoption/roposition/roposset/roposset.cpp \
    source/ropageoption/roposition/outputthread.cpp \    
    source/ropageoption/ropagealarm/alarmthread/alarmthread.cpp \
    source/ropageoption/ropagealarm/ropagealarm.cpp \
    source/ropageoption/roposition/roposition_init.cpp \
    source/ropageoption/roposition/roposition_slot.cpp \
    source/ropageoption/ropageprogramdata/ropageprogramdata.cpp \
    source/ropageoption/ropageprogramdata/do_AlterDataType_Slot.cpp \
    source/ropageoption/ropageprogramdata/do_ChooseAndExitDataType_Slot.cpp \
    source/ropageoption/ropageprogramdata/do_ChooseDataType_Slot.cpp \
    source/ropageoption/ropageprogramdata/do_NewDataView_Slot.cpp \
    source/ropageoption/ropageprogramdata/do_Show.cpp \
    source/ropageoption/ropageprogramdata/do_Skey_Slot.cpp \
    source/ropageoption/ropageprogramdata/do_Slot.cpp \
    source/ropageoption/roprogram/RoProgram.cpp \
    source/ropageoption/AutoProduct/AutoProduct.cpp \
    source/ropageoption/ropagealarm/ropagealarmInit.cpp \
    source/ropageoption/ropagealarm/ropagealarmSlot.cpp \
    source/ropageoption/HMI_ParaSet/HMI_ParaSet.cpp \
    source/ropageoption/roprogram/RoProgramSlot.cpp \
    source/ropageoption/robmanual/editbtn.cpp \
    source/ropageoption/robmanual/manualsubtemplatewidget.cpp \
    source/ropageoption/robmanual/newdatatemplatewidget.cpp \
    source/ropageoption/robmanual/robmanual.cpp \
    source/ropageoption/robmanual/settingwidget.cpp \
    source/ropageoption/robmanual/updateposedatathread.cpp

HEADERS  += \#头文文件
    header/mainwindow.h \
    header/romenu/romenu.h \
    header/rostatebysys/rostatebysys.h \
    header/roimagesforsysstate/roimagesforsysstate.h \
    header/ropageoption/ropageoption.h \
    header/ropageoption/ropagehome/ropagehome.h \
    header/roclose/roclose.h \
    header/rostatebar/rostatebar.h \
    header/ropageoption/roposition/roposition.h \
    header/ropageoption/roposition/roposset/roposset.h \
    header/ropageoption/roposition/outputthread.h \
    header/ITP_Interface.h \
    header/DataManage_WinShareMem.h \
    header/ropageoption/ropagealarm/robalarm.h \
    header/ropageoption/ropagealarm/alarmthread/alarmthread.h \
    header/DataManage/DataManage.h \
    header/DataManage/DataProcess.h \
    header/Common/Common.h \
    header/ropageoption/ropagealarm/ropagealarm.h \
    header/UI/InputOutput/InputOutput.h \
    header/UI/ResourceManage/ResourceManage.h \
    header/UI/SystemInfo/SystemInfo.h \
    header/UI/ControlPanel/ControlPanel.h \
    header/UI/ControlPanel/Appearance/Appearance.h \
    header/UI/ControlPanel/ProgKeys/ProgKeys.h \
    header/UI/ControlPanel/Configuration/Configuration.h \
    header/UI/ControlPanel/DateTime/DateTime.h \
    header/UI/ControlPanel/Diagnosis/Diagnosis.h \
    header/UI/ControlPanel/Language/Language.h \
    header/UI/ControlPanel/Monitoring/Monitoring.h \
    header/UI/ControlPanel/TouchScreen/TouchScreen.h \
    header/UI/ControlPanel/FlexPendant/FlexPendant.h \
    header/UI/ControlPanel/IO/IO.h \
    header/ropageoption/ropageprogramdata/ropageprogramdata.h \
    header/UI/ProgramData/ProgramData.h \
    header/UI/ProgramData/ProgramData_Alter.h \
    header/UI/ProgramData/ProgramData_ChooseAndExitDataType.h \
    header/UI/ProgramData/ProgramData_ChooseDataType.h \
    header/UI/BackupRecover/BackupRecover.h \
    header/UI/Program/ProgramShow/ProgramShow.h \
    header/UI/Program/ProgramChoose/ProgramChoose.h \
    header/FileAndDirOperate/FileAndDirOperate.h \
    header/ropageoption/roprogram/RoProgram.h \
    header/UI/rightWidget/rightWidget.h \
    header/UI/keyworld/vkeyworld/vkeyworld.h \
    header/UI/keyworld/skeyworld/skeyworld.h \
    header/ropageoption/AutoProduct/AutoProduct.h \
    header/UI/robResouceManage/robResouceManage.h \
    header/ropageoption/HMI_ParaSet/HMI_ParaSet.h \
    header/UI/Program/ProgramRoutinePro/ProgramRoutinePro.h \
    header/UI/Program/ProgramModule/ProgramModule.h \
    header/ropageoption/robmanual/common.h \
    header/ropageoption/robmanual/editbtn.h \
    header/ropageoption/robmanual/manualsubtemplatewidget.h \
    header/ropageoption/robmanual/newdatatemplatewidget.h \
    header/ropageoption/robmanual/robmanual.h \
    header/ropageoption/robmanual/settingwidget.h \
    header/ropageoption/robmanual/updateposedatathread.h

FORMS    += forms/mainwindow.ui \#界面文件
    forms/rostatebysys/rostatebysys.ui \
    forms/ropageoption/ropageoption.ui \
    forms/ropageoption/ropagehome/ropagehome.ui \
    forms/roimagesforsysstate/roimagesforsysstate.ui \    
    forms/romenu/romenu.ui \
    forms/roclose/roclose.ui \
    forms/rostatebar/rostatebar.ui \
    forms/ropageoption/roposition/roposition.ui \
    forms/ropageoption/roposition/roposset/roposset.ui \
    forms/ropageoption/ropagealarm/ropagealarm.ui \
    forms/ropageoption/ropageprogramdata/ropageprogramdata.ui \
    forms/ropageoption/roprogram/RoProgram.ui \
    forms/ropageoption/AutoProduct/AutoProduct.ui \
    forms/ropageoption/HMI_ParaSet/HMI_ParaSet.ui

#OTHER_FILES += \   #其他文件

OBJECTS_DIR += ./../../robhmi/hmi/obj   #指定目标文件(obj)的存放目

DESTDIR += ./../../robhmi/hmi/bin   #指定生成的应用程序放置的目录

#RCC_DIR += ./../../robhmi/hmi/project_file

UI_DIR += ./UI_H    #指定uic命令*.ui文件转化成ui_*.h文件的存放的目录

MOC_DIR += ./MOC    #指定moc命令将含Q_OBJECT的头文件转换成标MOC_*.h文件的存放目

RESOURCES += \  #资源文件
    resource.qrc
