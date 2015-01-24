TEMPLATE = app
QT -= gui
CONFIG += console
CONFIG += debug
CONFIG -= app_bundle

TARGET = comms

DESTDIR=./
SOURCES += src/dealer/playingcard.cpp \
    src/comms/packet.cpp \
    src/comms/comms_main.cpp \
    $$PWD/src/comms/SerialPort.cpp

HEADERS += include/card.h \
    include/dealer/playingcard.h \
    include/comms/packet.h \
    $$PWD/include/comms/PacketTypes.h \
    $$PWD/include/comms/PacketErrors.h \
    $$PWD/include/comms/SerialPort.h \
    $$PWD/include/shared/card.h
INCLUDEPATH += include/
OBJECTS_DIR = obj

LIBS += -lboost_system

QMAKE_CFLAGS = -std=c99
