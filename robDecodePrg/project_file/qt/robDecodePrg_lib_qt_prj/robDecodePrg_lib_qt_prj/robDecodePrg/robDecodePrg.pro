#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T14:52:13
#
#-------------------------------------------------

QT       -= gui

TARGET = robDecodePrg
TEMPLATE = lib
CONFIG += staticlib

DEFINES += ROBDECODEPRG_LIBRARY

SOURCES += robdecodeprg.cpp

HEADERS += robdecodeprg.h\
        robdecodeprg_global.h

DESTDIR=./

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错

}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
