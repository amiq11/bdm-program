#-------------------------------------------------
#
# Project created by QtCreator 2013-01-30T20:26:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customView.cpp \
    commDevice.cpp \
    circle.cpp \
    commandManager.cpp

HEADERS  += mainwindow.h \
    paintCanvas.h \
    customView.h \
    commDevice.h \
    circle.h \
    commandManager.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
