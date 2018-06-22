#-------------------------------------------------
#
# Project created by QtCreator 2015-09-23T16:20:03
#
#-------------------------------------------------

QT       -= gui

TARGET = FileAndDirOperate
TEMPLATE = lib
CONFIG += staticlib

SOURCES += FileAndDirOperate.c

HEADERS += FileAndDirOperate.h

DESTDIR=./../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
    target.path = /usr/lib
    INSTALLS += target
}
