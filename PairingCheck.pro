QT += core
QT -= gui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


TARGET = PairingCheck
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
#    interface.cpp \
    client.cpp \
    server.cpp \
    workerrs.cpp \
    paramsrs.cpp \
    rsinterface.cpp \
    udpinterface.cpp \
    paramsudp.cpp

HEADERS += \
#    interface.h \
    client.h \
    server.h \
    const.h \
    workerrs.h \
    paramsrs.h \
    iparams.h \
    rsinterface.h \
    iworker.h \
    iinterface.h \
    udpinterface.h \
    paramsudp.h
