#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T14:52:13
#
#-------------------------------------------------

QT       += core gui xml

TARGET = robDecodePrg
TEMPLATE = lib
CONFIG += staticlib

DEFINES += ROBDECODEPRG_LIBRARY

INCLUDEPATH += \
    header/decode_core \
    header/decode_prg \

SOURCES += \
    source/decode_core/decode_instructions.c \
    source/decode_core/decode_lexical_analysis.c \
    source/decode_core/decode_parse_file.c \
    source/decode_core/decode_proc_task.c \
    source/decode_core/decode_typestructs.c \
    source/decode_prg/decode_public.cpp \
    source/decode_prg/robotdecodepublic.cpp \
    source/decode_prg/robotpgfxmlparser.cpp \
    source/decode_prg/robotprgfilestruct.cpp \
    source/decode_prg/robotvariablestruct.cpp \

HEADERS += \
    header/decode_core/basic_data_type.h \
    header/decode_core/decode_datatype.h \
    header/decode_core/decode_instructions.h \
    header/decode_core/decode_lexical_analysis.h \
    header/decode_core/decode_parse_file.h \
    header/decode_core/decode_proc_task.h \
    header/decode_core/decode_shmem.h \
    header/decode_core/decode_typestructs.h \
    header/decode_core/ITP_Interface.h \
    header/decode_prg/decode_public.h \
    header/decode_prg/robotdecodepublic.h \
    header/decode_prg/robotpgfxmlparser.h \
    header/decode_prg/robotprgfilestruct.h \
    header/decode_prg/robotvariablestruct.h \
#robdecodeprg.h\
#        robdecodeprg_global.h

DESTDIR=./../../robhmi/hmi/lib#定义项目编译之后生成的结果文件的存放路径

win32{#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错

}

unix {#表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
    target.path = /usr/lib
    INSTALLS += target
}
