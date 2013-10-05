#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T20:59:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = V2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filecrypto.cpp \
    v2.cpp \
    sha2.cpp \
    key.cpp

HEADERS  += mainwindow.h \
    filecrypto.h \
    v2.h \
    sha2.h \
    key.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
