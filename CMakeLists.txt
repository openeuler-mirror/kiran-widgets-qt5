cmake_minimum_required(VERSION 3.5)

enable_testing()

#是否安装examples选项
option(install-examples "install examples" ON)

#构建测试代码选项
option(build-tests "build tests" ON)

project(kiranwidgets-qt5)

include(GNUInstallDirs)

#VERSION　 so版本
#影响生成的二进制共享库文件名 eg:libxxxx.so.${VERSION}
#格式:     主版本号-次版本号-发行版本号
#主版本:   不同主版本不兼容，主版本升级应需同时升级SOVERSION
#次版本:   增量升级，向后兼容
#发行版本: 对次版本的升级，不影响兼容
set(KIRANWIDGETS_VERSION     2.1.1)

#SOVERSION API版本  影响安装做的软链接的名 eg:libxxx.so.${SOVERSION} -> libxxx.so.{VERSION}
#就是主版本号,程序链接的就是该符号
set(KIRANWIDGETS_API_VERSION 2)

find_package(PkgConfig REQUIRED)
pkg_search_module(GSETTINGS_QT REQUIRED gsettings-qt)
pkg_search_module(KIRAN_INTEGRATION_THEME REQUIRED kiran-integration-theme)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#公共部分代码
file(GLOB_RECURSE PUBLIC_CPP "src/public/*.cpp")
file(GLOB_RECURSE PUBLIC_H "src/public/*.h")

#widgets源码
file(GLOB_RECURSE WIDGET_CPP "src/widgets/*.cpp")
file(GLOB_RECURSE WIDGET_H "src/widgets/*.h")

#资源文件
file(GLOB_RECURSE RESOURCES "resources/*.qrc")

#翻译
file(GLOB TS_FILES "translations/kiranwidgets-qt5.*.ts")

#开发头文件,需提供到devel包的文件
set(DEVEL_HEADER
        "src/widgets/kiran-titlebar-window/kiran-titlebar-window.h"
        "src/widgets/kiran-message-box/kiran-message-box.h"
        "src/widgets/kiran-switch-button/kiran-switch-button.h"
        "src/widgets/kiran-application/kiran-application.h"
        "src/widgets/kiran-search-box/kiran-search-box.h"
        "src/widgets/kiran-single-application/kiran-single-application.h"
        "src/widgets/kiran-sidebar-widget/kiran-sidebar-widget.h"
        "src/widgets/kiran-sidebar-widget/kiran-sidebar-item.h"
        "src/widgets/kiran-icon-line-edit/kiran-icon-line-edit.h"
        "src/widgets/kiran-image-selector/kiran-image-selector.h"
        "src/widgets/kiran-push-button/kiran-push-button.h"
        "src/widgets/kiran-hover-tips/kiran-hover-tips.h"
        "src/widgets/kiran-color-block/kiran-color-block.h"
        "src/widgets/kiran-label/kiran-label.h"
        "src/widgets/kiran-passwd-edit/kiran-passwd-edit.h")

include_directories("${CMAKE_BINARY_DIR}")

find_package(Qt5 COMPONENTS Widgets Gui Svg Network X11Extras Concurrent LinguistTools)

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
        src/
        src/widgets/
        src/widgets/common/
        src/public/
        src/widgets/kiran-application/
        ${GSETTINGS_QT_INCLUDE_DIRS}
        ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
        ${KIRAN_INTEGRATION_THEME_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC
        src/widgets)

target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        Qt5::Svg
        Qt5::X11Extras
        Qt5::Network
        Qt5::Concurrent
        X11
        xcb
        xcb-util
        ${GSETTINGS_QT_LIBRARIES}
        ${KIRAN_INTEGRATION_THEME_LIBRARIES})

#安装SO
set(KIRANWIDGETS_LIB_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${PROJECT_NAME} DESTINATION ${KIRANWIDGETS_LIB_DIR})

#开发头文件
set(KIRANWIDGETS_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(FILES ${DEVEL_HEADER}
        DESTINATION ${KIRANWIDGETS_INCLUDE_DIR})

#pkgconfig
configure_file( kiranwidgets-qt5.pc.in kiranwidgets-qt5.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kiranwidgets-qt5.pc
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig/)

#翻译
install(FILES ${QM_FILES}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/translations )

#demo
if( install-examples )
    install(DIRECTORY examples
            DESTINATION  ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME} )
endif()

if( build-tests )
    add_subdirectory(test)
endif()
