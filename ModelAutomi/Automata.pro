TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    abstractautoma.cpp \
    dfa.cpp \
    nfa.cpp \
    stato.cpp \
    transizione.cpp \
    transizionepda.cpp

HEADERS += \
    abstractautoma.h \
    dfa.h \
    nfa.h \
    stato.h \
    transizione.h \
    transizionepda.h

DISTFILES += \
    Memo
