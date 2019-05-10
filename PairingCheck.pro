QT += core
QT -= gui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


TARGET = PairingCheck
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    interface.cpp \
    rs_interface.cpp \
    client.cpp \
    server.cpp \
    workerrs.cpp \
    paramsrs.cpp

HEADERS += \
    abstract-interface.h \
    interface.h \
    rs_interface.h \
    client.h \
    server.h \
    const.h \
    workerrs.h \
    paramsrs.h
