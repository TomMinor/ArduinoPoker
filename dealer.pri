TARGET=winner

SOURCES+=$$PWD/src/dealer/dealer_main.cpp \
         $$PWD/src/dealer/deck.cpp \
         $$PWD/src/dealer/playingcard.cpp \
         $$PWD/src/dealer/player.cpp \
         $$PWD/src/dealer/pokerHands.cpp \
         $$PWD/src/dealer/cardStack.cpp

HEADERS+=$$PWD/include/dealer/deck.h \
         $$PWD/include/dealer/playingcard.h \
         $$PWD/include/dealer/player.h \
         $$PWD/include/dealer/pokerHands.h \
         $$PWD/include/dealer/cardStack.h

INCLUDEPATH +=./include

