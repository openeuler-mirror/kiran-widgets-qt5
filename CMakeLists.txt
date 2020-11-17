cmake_minimum_required(VERSION 3.5)

option(install-examples "install examples" ON)

project(kiranwidgets-qt5)

#VERSION　 so版本
#影响生成的二进制共享库文件名 eg:libxxxx.so.${VERSION}
#格式:     主版本号-次版本号-发行版本号
#主版本:   不同主版本不兼容，主版本升级应需同时升级SOVERSION
#次版本:   增量升级，向后兼容
#发行版本: 对次版本的升级，不影响兼容
set(KIRANWIDGETS_VERSION     2.0.0)

#SOVERSION API版本  影响安装做的软链接的名 eg:libxxx.so.${SOVERSION} -> libxxx.so.{VERSION}
#就是主版本号,程序链接的就是该符号
set(KIRANWIDGETS_API_VERSION 2)

find_package(PkgConfig REQUIRED)
pkg_search_module(GSETTINGS_QT REQUIRED gsettings-qt)

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
        "widgets/kiran-message-box/kiran-message-box.h"
        "widgets/kiran-application/kiran-application.h"
        "widgets/kiran-single-application/kiran-single-application.h" )

include_directories("${CMAKE_BINARY_DIR}")

find_package(Qt5 COMPONENTS Widgets Network X11Extras LinguistTools)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_library(${PROJECT_NAME} SHARED
        ${PUBLIC_CPP}
        ${PUBLIC_H}
        ${WIDGET_CPP}
        ${WIDGET_H}
        ${RESOURCES}
        ${QM_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION   ${KIRANWIDGETS_VERSION}
        SOVERSION ${KIRANWIDGETS_API_VERSION})

target_include_directories(${PROJECT_NAME} PRIVATE
        widgets/
        public/
        widgets/kiran-application/
        ${GSETTINGS_QT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        Qt5::X11Extras
        Qt5::Network
        X11
        xcb
        xcb-util
        ${GSETTINGS_QT_LIBRARIES})

#安装SO
install(TARGETS ${PROJECT_NAME} DESTINATION ${LIB_INSTALL_DIR}/)

#开发头文件
install(FILES ${DEVEL_HEADER} DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}/)

#pkgconig
configure_file( kiranwidgets-qt5.pc.in kiranwidgets-qt5.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kiranwidgets-qt5.pc
        DESTINATION ${LIB_INSTALL_DIR}/pkgconfig/)

#翻译
install(FILES ${QM_FILES} DESTINATION ${SHARE_INSTALL_PREFIX}/${PROJECT_NAME}/translations/)

#demo
if( install-examples )
    install(DIRECTORY examples DESTINATION ${SHARE_INSTALL_PREFIX}/${PROJECT_NAME}/ )
endif()