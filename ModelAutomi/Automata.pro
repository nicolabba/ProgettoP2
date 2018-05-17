TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    transizione.cpp \
    stato.cpp \
    transizionepda.cpp \
    abstractautoma.cpp \
    dfa.cpp \
    nfa.cpp

HEADERS += \
    transizione.h \
    stato.h \
    transizionepda.h \
    abstractautoma.h \
    dfa.h \
    nfa.h
