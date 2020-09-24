QT += widgets

TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    titlebar-window-ui.cpp

HEADERS += \
    titlebar-window-ui.h

FORMS += \
    titlebar-window-ui.ui

LIBS += -lkiranwidgets-qt5
