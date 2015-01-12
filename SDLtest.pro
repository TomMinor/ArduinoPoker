#Specify the exe name
TARGET= SDLtest
#Where to put obj files
OBJECTS_DIR= obj
#Get Qt to cache stuff
cache()
#To add source files
SOURCES+= $$PWD/src/gui*.cpp #$$PWD/src/dealer/*.cpp
SOURCES-= $$PWD/src/gui_listmenu.cpp $$PWD/src/gui_task.cpp
#To add headers
HEADERS+= $$PWD/include/gui_*.h $$PWD/include/dealer/*.h
HEADERS-= $$PWD/include/gui_listmenu.h $$PWD/include/gui_task.h
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
