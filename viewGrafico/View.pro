#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T15:11:14
#
#-------------------------------------------------

QT       += widgets
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = View
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grafico.cpp \
    punto.cpp

HEADERS  += mainwindow.h \
    grafico.h \
    punto.h

FORMS    += mainwindow.ui

DISTFILES +=
