TARGET=dealerLib


SOURCES+= $$PWD/src/dealer/deck.cpp \
          $$PWD/src/dealer/playingcard.cpp \
          $$PWD/src/dealer/player.cpp \
          $$PWD/src/dealer/dealerLib.cpp \
          $$PWD/src/dealer/dealerLibMain.cpp \
          $$PWD/src/dealer/cardStack.cpp \
          $$PWD/src/dealer/comms.cpp \
          $$PWD/src/dealer/pokerHands.cpp \
          $$PWD/src/comms/SerialPort.cpp \
          $$PWD/src/gui/gui_card.cpp \
          $$PWD/src/gui/gui_dealergui.cpp \
          $$PWD/src/gui/gui_element.cpp \
          $$PWD/src/gui/gui_elementmaker.cpp \
          $$PWD/src/gui/gui_hand.cpp \
          $$PWD/src/gui/gui_label.cpp

HEADERS+= $$PWD/include/dealer/deck.h \
          $$PWD/include/dealer/playingcard.h \
          $$PWD/include/dealer/player.h \
          $$PWD/include/dealer/dealerLib.h \
          $$PWD/include/dealer/cardStack.h \
          $$PWD/include/dealer/comms.h \
          $$PWD/include/dealer/pokerHands.h \
          $$PWD/include/gui/gui_card.h \
          $$PWD/include/gui/gui_dealergui.h \
          $$PWD/include/gui/gui_element.h \
          $$PWD/include/gui/gui_elementmaker.h \
          $$PWD/include/gui/gui_hand.h \
          $$PWD/include/gui/gui_label.h

INCLUDEPATH +=./include

LIBS += -lboost_system

LIBS+= -L$(HOME)/NGL/lib -lSDL2_ttf -lSDL2_image
DEFINES+= QT5BUILD

# this demo uses SDL so add the paths using the sdl2-config tool
QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)
