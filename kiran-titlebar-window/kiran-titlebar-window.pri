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
    $$PWD/images.qrc \
    $$PWD/themes.qrc

OTHER_FILES += \
    $$PWD/examples/KiranTitlebarWindow_UI/* \
    $$PWD/examples/KiranTitlebarWindow_CPP/* \
    $$PWD/examples/KiranTitlebarWindow_Simple/*

LIBS += -lX11

contains(DEFINES,EXAMPLES){
    kiran_titlebar_window_examples.files = $$PWD/examples/*
    kiran_titlebar_window_examples.path =  $$DESTDIR/usr/share/kiranwidget-qt5/examples/
    INSTALLS += kiran_titlebar_window_examples
}

kiran_titlebar_window_include.files = $$PWD/kiran-titlebar-window.h
kiran_titlebar_window_include.path = $$DESTDIR/usr/include/kiranwidget-qt5/
INSTALLS += kiran_titlebar_window_include
