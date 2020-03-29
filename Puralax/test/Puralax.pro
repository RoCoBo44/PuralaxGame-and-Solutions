#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T14:59:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puralax
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += static
INCLUDEPATH += $$PWD

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    bloque.cpp \
    tablero.cpp \
    paleta.cpp \
    panell.cpp \
    marchivo.cpp \
    secondarywindow.cpp \
    pilatableros.cpp \
    priorityqueue.cpp \
    estado.cpp \
    camino.cpp \
    randomizer.cpp

HEADERS  += mainwindow.h \
    bloque.h \
    tablero.h \
    paleta.h \
    panell.h \
    marchivo.h \
    secondarywindow.h \
    pilatableros.h \
    priorityqueue.h \
    estado.h \
    camino.h \
    randomizer.h

FORMS    += mainwindow.ui \
    panell.ui \
    secondarywindow.ui
