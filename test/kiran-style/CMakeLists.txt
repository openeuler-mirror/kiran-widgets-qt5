cmake_minimum_required(VERSION 3.5)

project(kiran-style-test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")

find_package(Qt5 COMPONENTS Widgets)
find_package(PkgConfig REQUIRED)
pkg_search_module(KIRAN_WIDGETS_QT5 REQUIRED kiranwidgets-qt5)

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${FORMS})

include_directories("${CMAKE_BINARY_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE
        ../../src/widgets/kiran-application/
        ../../src/widgets/kiran-single-application/
        ../../src/kiran-style/
        ../../src/widgets/kiran-switch-button
        ../../src/widgets/kiran-search-box
        ../../src/widgets/kiran-sidebar-widget
        ../../src/widgets/kiran-titlebar-window
        ../../src/widgets/kiran-icon-line-edit
        ../../src/widgets/kiran-message-box
        ../../src/widgets/kiran-image-selector)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets kiranwidgets-qt5)