TEMPLATE = app
QT -= gui
CONFIG += console
CONFIG += debug
CONFIG -= app_bundle

TARGET = bin/CardExample

DESTDIR=./
SOURCES += src/examples/cardUsage.cpp \
    src/dealer/playingcard.cpp
HEADERS += include/card.h \
    include/dealer/playingcard.h
INCLUDEPATH += include/
OBJECTS_DIR = obj

cache()

QMAKE_CFLAGS = -std=c99
