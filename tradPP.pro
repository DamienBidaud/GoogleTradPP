#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T16:44:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tradPP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    language.cpp \
    word.cpp \
    xmlparseur.cpp \
    xmlparseurfr.cpp

HEADERS  += mainwindow.h \
    language.h \
    word.h \
    xmlparseur.h \
    xmlparseurfr.h

FORMS    += mainwindow.ui
