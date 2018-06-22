#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T09:03:46
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ControlPanel
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ControlPanel.cpp \
    Appearance/Appearance.cpp \
    ProgKeys/ProgKeys.cpp \
    Configuration/Configuration.cpp \
    DateTime/DateTime.cpp \
    Diagnosis/Diagnosis.cpp \
    Language/Language.cpp \
    Monitoring/Monitoring.cpp \
    TouchScreen/TouchScreen.cpp \
    FlexPendant/FlexPendant.cpp \
    IO/IO.cpp

HEADERS += ControlPanel.h \
    Appearance/Appearance.h \
    ProgKeys/ProgKeys.h \
    Configuration/Configuration.h \
    DateTime/DateTime.h \
    Diagnosis/Diagnosis.h \
    Language/Language.h \
    Monitoring/Monitoring.h \
    TouchScreen/TouchScreen.h \
    FlexPendant/FlexPendant.h \
    IO/IO.h

FORMS += ControlPanel.ui \
    Appearance/Appearance.ui \
    ProgKeys/ProgKeys.ui \
    Configuration/Configuration.ui \
    DateTime/DateTime.ui \
    Diagnosis/Diagnosis.ui \
    Language/Language.ui \
    Monitoring/Monitoring.ui \
    TouchScreen/TouchScreen.ui \
    FlexPendant/FlexPendant.ui \
    IO/IO.ui

DESTDIR=./../../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES +=


