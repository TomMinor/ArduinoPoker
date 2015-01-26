TEMPLATE = app
QT -= gui
CONFIG += console
CONFIG += debug
CONFIG -= app_bundle

TARGET = comms

DESTDIR=./
SOURCES += src/dealer/playingcard.cpp \
    src/dealer/player.cpp \
    src/dealer/cardStack.cpp \
    src/comms/comms_main.cpp \
    $$PWD/src/comms/SerialPort.cpp \
    $$PWD/src/comms/dealerIO.cpp

HEADERS += include/card.h \
    include/dealer/playingcard.h \
    $$PWD/include/comms/SerialPort.h \
    $$PWD/include/shared/card.h \
    $$PWD/include/comms/dealerIO.h

INCLUDEPATH += include/
OBJECTS_DIR = obj

LIBS += -lboost_system

QMAKE_CFLAGS = -std=c99
