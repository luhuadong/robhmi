QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skeyworld
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    skeyWorld.cpp

HEADERS += \
    skeyWorld.h

DESTDIR=./../../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报�?

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报�?
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    skeyWorld.ui
