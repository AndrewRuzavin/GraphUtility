TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
LIBS += -lgvc -lcgraph -lcdt

VPATH += ./src

SOURCES += \
    main.cpp \
    CreatorI.cpp \
    GraphCreator.cpp \
    Loader.cpp \
    LoaderI.cpp \
    ConverterI.cpp \
    Converter.cpp \
    src/FileException.cpp \
    src/SaverI.cpp \
    src/Saver.cpp

HEADERS += \
    CreatorI.hpp \
    GraphCreator.hpp \
    Loader.hpp \
    LoaderI.hpp \
    ConverterI.hpp \
    Converter.hpp \
    src/FileException.hpp \
    src/SaverI.hpp \
    src/Saver.hpp \
    src/InfoStructs.hpp

DISTFILES += \
    introduction/1.txt \
    introduction/2.txt \
    introduction/3.txt
