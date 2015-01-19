#Specify the exe name
TARGET= PokerGUI
#Where to put obj files
OBJECTS_DIR= obj
#Get Qt to cache stuff
cache()
#To add source files
SOURCES+= $$PWD/src/gui/gui_card.cpp \
          $$PWD/src/gui/gui_dealergui.cpp \
          $$PWD/src/gui/gui_element.cpp \
          $$PWD/src/gui/gui_elementmaker.cpp \
          $$PWD/src/gui/gui_hand.cpp \
          $$PWD/src/gui/gui_label.cpp \
          $$PWD/src/gui/gui_listmenu.cpp \
          $$PWD/src/gui/gui_task.cpp \
          $$PWD/src/gui/gui_mainExample.cpp \
          $$PWD/src/dealer/playingcard.cpp \
          $$PWD/src/dealer/cardStack.cpp \
          $$PWD/src/dealer/deck.cpp \
          $$PWD/src/dealer/player.cpp \

#To add headers
HEADERS+= $$PWD/include/gui/gui_card.h \
          $$PWD/include/gui/gui_dealergui.h \
          $$PWD/include/gui/gui_element.h \
          $$PWD/include/gui/gui_elementmaker.h \
          $$PWD/include/gui/gui_hand.h \
          $$PWD/include/gui/gui_label.h \
          $$PWD/include/gui/gui_listmenu.h \
          $$PWD/include/gui/gui_task.h \
          $$PWD/include/dealer/playingcard.h \
          $$PWD/include/dealer/cardStack.h \
          $$PWD/include/dealer/deck.h \
          $$PWD/include/dealer/player.h \


INCLUDEPATH+= include
INCLUDEPATH+= $$(HOME)/NGL/include
#Tell Qt to include OpenGL
#QT+= gui opengl core
#Tell where libs are
LIBS+= -L$(HOME)/NGL/lib -lSDL2_ttf -lSDL2_image
DEFINES+= QT5BUILD

# this demo uses SDL so add the paths using the sdl2-config tool
QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)
