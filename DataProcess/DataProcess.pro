#-------------------------------------------------
#
# Project created by QtCreator 2015-09-14T16:20:03
#
#-------------------------------------------------

QT       -= gui

TARGET = DataProcess
TEMPLATE = lib
CONFIG += staticlib

SOURCES += DataProcess.cpp

HEADERS += DataProcess.h \
    ITP_Interface.h

DESTDIR=./../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报�?

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报�?
    target.path = /usr/lib
    INSTALLS += target
}
