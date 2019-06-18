QT += core gui widgets xml

CONFIG += c++17
#CONFIG += console

TEMPLATE = app

HEADERS += \
        include/log.h \
        include/aliases.h \
        include/structures/hashfunc.h \
        include/structures/hashtable.h \
        include/name_generator.h \
        include/form.h


SOURCES += \
        src/main.cpp \
        src/name_generator.cpp \
        src/form.cpp


FORMS += \
        form.ui


RESOURCES += \
        res.qrc
