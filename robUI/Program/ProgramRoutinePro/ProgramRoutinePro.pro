#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T09:03:46
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgramRoutinePro
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    ProgramRoutinePro.cpp

HEADERS += \
    ProgramRoutinePro.h

FORMS += \
    ProgramRoutinePro.ui

DESTDIR=./../../../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径




win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES +=


