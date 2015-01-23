TARGET=dealerLib

SOURCES+=$$PWD/src/dealer/deck.cpp \
         $$PWD/src/dealer/playingcard.cpp \
         $$PWD/src/dealer/player.cpp \
         $$PWD/src/dealer/dealerLib.cpp \
         $$PWD/src/dealer/dealerLibMain.cpp \
         $$PWD/src/dealer/cardStack.cpp \
    $$PWD/src/dealer/comms.cpp


HEADERS+=$$PWD/include/dealer/deck.h \
         $$PWD/include/dealer/playingcard.h \
         $$PWD/include/dealer/player.h \
         $$PWD/include/dealer/dealerLib.h \
         $$PWD/include/dealer/cardStack.h \
    $$PWD/include/dealer/comms.h

INCLUDEPATH +=./include
