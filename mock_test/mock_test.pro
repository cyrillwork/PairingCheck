QT += core
QT -= gui

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

TARGET = mock_test.e
CONFIG += console
CONFIG -= app_bundle

LIBS += -lpthread

LIBS += ../workerrs.o
LIBS += ../paramsrs.o
LIBS += ../rs_interface.o
LIBS += ../interface.o
LIBS += ../client.o
LIBS += ../server.o

LIBS += /usr/src/gtest/src/libgtest.a
LIBS += /usr/src/gtest/src/libgtest_main.a

LIBS += /usr/src/gmock/libgmock.a
LIBS += /usr/src/gmock/libgmock_main.a

TEMPLATE = app

SOURCES += main.cpp

