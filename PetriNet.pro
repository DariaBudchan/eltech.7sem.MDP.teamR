#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T22:27:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PetriNet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    conditionitem.cpp \
    processitem.cpp \
    arrowitem.cpp \
    diagramscene.cpp \
    textitem.cpp \
    petriemulator.cpp

HEADERS  += mainwindow.h \
    conditionitem.h \
    processitem.h \
    arrowitem.h \
    diagramscene.h \
    textitem.h \
    petriemulator.h
