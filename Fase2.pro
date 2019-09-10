QT += core
QT -= gui

CONFIG += c++11

TARGET = Fase1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    interprete.cpp \
    exec.cpp \
    fdisk.cpp \
    mkdisk.cpp \
    mount.cpp \
    rmdisk.cpp \
    structs.cpp \
    rep.cpp \
    mkfs.cpp \
    login.cpp \
    group.cpp \
    user.cpp \
    archivo.cpp \
    carpeta.cpp \
    change.cpp \
    ext3.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    interprete.h \
    exec.h \
    fdisk.h \
    mkdisk.h \
    mount.h \
    rmdisk.h \
    structs.h \
    rep.h \
    mkfs.h \
    login.h \
    group.h \
    user.h \
    archivo.h \
    carpeta.h \
    change.h \
    ext3.h
