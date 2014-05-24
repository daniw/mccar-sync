#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T09:45:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = carsteuerung
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    controller.cpp \
    InvokeInEventLoop.cpp \
    DoAtScopeExit.cpp \
    ResourceStatusDisplayWidget.cpp \
    CommonStatusDisplayWidget.cpp

HEADERS  += MainWindow.h \
    controller.h \
    InvokeInEventLoop.h \
    DoAtScopeExit.h \
    Payload.h \
    ResourceStatusDisplayWidget.h \
    CommonStatusDisplayWidget.h

FORMS    += MainWindow.ui \
    ResourceStatusDisplayWidget.ui \
    CommonStatusDisplayWidget.ui

LIBS += -lserial -lboost_thread -lboost_system
QMAKE_CXXFLAGS += -std=c++11
