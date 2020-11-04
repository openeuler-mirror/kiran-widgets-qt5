cmake_minimum_required(VERSION 3.5)

option(install-examples "install examples" ON)

project(kiranwidgets-qt5)

set(KIRANWIDGETS_VERSION     1.0)
set(KIRANWIDGETS_API_VERSION 1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE PUBLIC_CPP "public/*.cpp")
file(GLOB_RECURSE PUBLIC_H "public/*.h")
file(GLOB_RECURSE WIDGET_CPP "widgets/*.cpp")
file(GLOB_RECURSE WIDGET_H "widgets/*.h")
file(GLOB_RECURSE RESOURCES "resources/*.qrc")
set(TS_FILES "translations/kiranwidgets-qt5.zh_CN.ts")
set(DEVEL_HEADER
        "widgets/kiran-titlebar-window/kiran-titlebar-window.h"
        "widgets/kiran-message-box/kiran-message-box.h")

include_directories("${CMAKE_BINARY_DIR}")

find_package(Qt5 COMPONENTS Widgets X11Extras LinguistTools)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_library(${PROJECT_NAME} SHARED
        ${PUBLIC_CPP}
        ${PUBLIC_H}
        ${WIDGET_CPP}
        ${WIDGET_H}
        ${RESOURCES}
        ${QM_FILES})
#VERSION　 so版本
#SOVERSION API版本
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION   ${KIRANWIDGETS_VERSION}
        SOVERSION ${KIRANWIDGETS_API_VERSION})

install(TARGETS ${PROJECT_NAME} DESTINATION ${LIB_INSTALL_DIR}/)
install(FILES ${DEVEL_HEADER} DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}/)
install(FILES ${QM_FILES} DESTINATION ${SHARE_INSTALL_PREFIX}/${PROJECT_NAME}/translations/)
if( install-examples )
    install(DIRECTORY examples DESTINATION ${SHARE_INSTALL_PREFIX}/${PROJECT_NAME}/ )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        widgets/
        public/)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::X11Extras X11 xcb xcb-util)