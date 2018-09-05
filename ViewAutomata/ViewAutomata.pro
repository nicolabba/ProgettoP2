#-------------------------------------------------
#
# Project created by QtCreator 2018-06-27T11:17:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewAutomata
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    abstractautoma.cpp \
    dfa.cpp \
    fa.cpp \
    pda.cpp \
    stato.cpp \
    statofa.cpp \
    statopda.cpp \
    transizione.cpp \
    transizionepda.cpp \
    statographicsitem.cpp \
    transizionegraphicsitem.cpp \
    arrowhead.cpp \
    automagraphicsview.cpp \
    nfa.cpp \
    statodialog.cpp \
    transizionedialog.cpp \
    settingsdialog.cpp

HEADERS += \
        mainwindow.h \
    abstractautoma.h \
    dfa.h \
    fa.h \
    nfa.h \
    pda.h \
    stato.h \
    statofa.h \
    statopda.h \
    transizione.h \
    transizionepda.h \
    statographicsitem.h \
    transizionegraphicsitem.h \
    arrowhead.h \
    automagraphicsview.h \
    statodialog.h \
    transizionedialog.h \
    settingsdialog.h

FORMS +=

SUBDIRS += \
    ViewAutomata.pro

DISTFILES += \
    ViewAutomata.pro.user \
    Memo
