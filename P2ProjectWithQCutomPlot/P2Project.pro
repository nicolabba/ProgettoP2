#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T18:54:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = P2Project
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
    Automaton/abstractautomaton.cpp \
    Automaton/arrowhead.cpp \
    Automaton/automatongraphicsview.cpp \
    Automaton/dfa.cpp \
    Automaton/fa.cpp \
    Automaton/nfa.cpp \
    Automaton/pda.cpp \
    Automaton/settingsdialog.cpp \
    Automaton/state.cpp \
    Automaton/statedialog.cpp \
    Automaton/statefa.cpp \
    Automaton/stategraphicsitem.cpp \
    Automaton/statepda.cpp \
    Automaton/transition.cpp \
    Automaton/transitiondialog.cpp \
    Automaton/transitiongraphicsitem.cpp \
    Automaton/transitionpda.cpp \
    Automaton/automatonmain.cpp \
    mainwidget.cpp \
    String/inputline.cpp \
    String/inputs.cpp \
    String/mycheckbox.cpp \
    String/stringmain.cpp \
    String/mystring.cpp \
    Graph/grafico.cpp \
    Graph/punto.cpp \
    Graph/graphmain.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS += \
    Automaton/abstractautomaton.h \
    Automaton/arrowhead.h \
    Automaton/automatongraphicsview.h \
    Automaton/dfa.h \
    Automaton/fa.h \
    Automaton/nfa.h \
    Automaton/pda.h \
    Automaton/settingsdialog.h \
    Automaton/state.h \
    Automaton/statedialog.h \
    Automaton/statefa.h \
    Automaton/stategraphicsitem.h \
    Automaton/statepda.h \
    Automaton/transition.h \
    Automaton/transitiondialog.h \
    Automaton/transitiongraphicsitem.h \
    Automaton/transitionpda.h \
    Automaton/automatonmain.h \
    mainwidget.h \
    String/inputline.h \
    String/inputs.h \
    String/mycheckbox.h \
    String/stringmain.h \
    String/mystring.h \
    Graph/grafico.h \
    Graph/punto.h \
    Graph/graphmain.h \
    qcustomplot/qcustomplot.h
