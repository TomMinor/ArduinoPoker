TEMPLATE = app
QT -= gui
CONFIG += console
CONFIG += debug
CONFIG -= app_bundle

TARGET = comms

DESTDIR=./
SOURCES += src/dealer/playingcard.cpp \
    src/comms/packet.cpp \
    src/comms/comms_main.cpp

HEADERS += include/card.h \
    include/dealer/playingcard.h \
    include/comms/packet.h \
    $$PWD/include/comms/PacketTypes.h \
    $$PWD/include/comms/PacketErrors.h
INCLUDEPATH += include/
OBJECTS_DIR = obj

QMAKE_CFLAGS = -std=c99
