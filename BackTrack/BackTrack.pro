#-------------------------------------------------
#
# Project created by QtCreator 2020-12-17T15:08:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BackTrack
TEMPLATE = app


SOURCES += main.cpp\
        backtrack.cpp \
    calculater.cpp \
    paintwidget.cpp

HEADERS  += backtrack.h \
    calculater.h \
    paintwidget.h

FORMS    += backtrack.ui

RESOURCES += \
    resource.qrc
