#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T17:14:04
#
#-------------------------------------------------

QT       -= gui

TARGET = RobAlarm
TEMPLATE = lib
CONFIG += staticlib

SOURCES += robalarm.cpp

HEADERS += robalarm.h

DESTDIR=./../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
    target.path = /usr/lib
    INSTALLS += target
}
