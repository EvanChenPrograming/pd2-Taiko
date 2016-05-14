#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T09:34:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = taiko
TEMPLATE = app

QT += multimedia
QT += widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    file_control.cpp \
    notes.cpp

HEADERS  += mainwindow.h \
    scene.h \
    file_control.h \
    notes.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
CONFIG   -= x86_64
