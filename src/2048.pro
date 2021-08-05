TEMPLATE = app
CONFIG -= console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS+= -LC:/dev/SDL/lib/ -llibSDL.dll -llibSDLmain -lSDL_image -lSDL_ttf
INCLUDEPATH += C:/dev/SDL/include/

SOURCES += main.cpp \
    ingame.cpp \
    deplacements.cpp \
    about.cpp \
    records.cpp

HEADERS += \
    main.h

DISTFILES += \
    ressource.rc
RC_FILE =ressource.rc
