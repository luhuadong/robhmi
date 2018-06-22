QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vkeyworld
TEMPLATE = lib
CONFIG += staticlib

SOURCES += vkeyworld.cpp \
    vkeyworld_Init.cpp \
    vkeyworld_Slot.cpp

HEADERS += vkeyworld.h

DESTDIR=./../../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    vkeyworld.ui
