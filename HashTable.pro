QT += core xml

TEMPLATE = app
CONFIG += console c++17

HEADERS += \
        include/log.h \
        include/aliases.h \
        include/structures/hashfunc.h \
        include/structures/hashtable.h \
        include/name_generator.h

SOURCES += \
        src/main.cpp \
        src/name_generator.cpp



INCLUDEPATH += C:/boost_1_70_0/boost_mingw_730_64/include/boost-1_70
LIBS += -LC:/boost_1_70_0/boost_mingw_730_64/lib

RESOURCES += \
        res.qrc


