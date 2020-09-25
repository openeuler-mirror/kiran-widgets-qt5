QT += x11extras

SOURCES += \
    $$PWD/kiran-titlebar-window.cpp \
    $$PWD/kiran-titlebar-window-private.cpp \
    $$PWD/xlib-helper.cpp

HEADERS += \
    $$PWD/global_define.h \
    $$PWD/kiran-titlebar-window.h \
    $$PWD/kiran-titlebar-window-private.h \
    $$PWD/xlib-helper.h

RESOURCES += \
    $$PWD/kiran-titlebar-window-images.qrc \
    $$PWD/kiran-titlebar-window-themes.qrc

OTHER_FILES += \
    $$PWD/examples/KiranTitlebarWindow_UI/* \
    $$PWD/examples/KiranTitlebarWindow_CPP/* \
    $$PWD/examples/KiranTitlebarWindow_Simple/*

LIBS += -lX11

target_examples.files += $$PWD/examples/*
target_includes.files += $$PWD/kiran-titlebar-window.h
