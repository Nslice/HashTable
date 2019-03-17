TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        src/main.cpp \

HEADERS += \
    include/log.h \
    include/aliases.h \
    include/structures/hashfunc.h \
    include/structures/hashtable.h \

INCLUDEPATH += C:/boost_1_69_0/boost_mingw_730_64/include/boost-1_69
LIBS += -LC:/boost_1_69_0/boost_mingw_730_64/lib


