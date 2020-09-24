QT += widgets

TEMPLATE = lib
#测试用
#TEMPLATE = app
DEFINES += EXAMPLES

CONFIG += c++11

#测试用
equals(TEMPLATE,app){
    SOURCES += main.cpp
}

OTHER_FILES += \
    README.md

target.path = /usr/lib
INSTALLS +=  target

include(kiran-titlebar-window/kiran-titlebar-window.pri)
