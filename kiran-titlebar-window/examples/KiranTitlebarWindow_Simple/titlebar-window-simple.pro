QT += widgets

TEMPLATE = app

CONFIG += c++11

LIBS += -lkiranwidgets-qt5

FORMS += \
    titlebar-window-simple.ui

HEADERS += \
    titlebar-window-simple.h

SOURCES += \
    main.cpp \
    titlebar-window-simple.cpp
